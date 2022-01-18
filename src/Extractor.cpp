#include "Extractor.h"
#include "AlgorithmAction.h"
#include "SettingsAction.h"

using namespace hdps;

Extractor::Extractor(AlgorithmAction& algorithmAction) :
    QObject(&algorithmAction),
    _algorithmAction(algorithmAction),
    _dimensionIndex(0),
    _extractTimer(),
    _dataRange(0.0f, 0.0f)
{
    // Configure extraction timer
    _extractTimer.setSingleShot(true);
    _extractTimer.setInterval(100);

    // Perform the extract process when the timer times out
    connect(&_extractTimer, &QTimer::timeout, [this]() {

        // Perform the extraction and execute post extraction operations
        extract();
        postExtract();

        // Inform others that the extraction process finished
        emit extracted();
    });

    // Update the clusters when the clusters model layout changes
    //connect(&getClustersModel(), &QAbstractItemModel::layoutChanged, this, [this]() {
    //    setClusters(getClustersModel().getClusters());
    //});
}

void Extractor::requestExtraction()
{
    // Do not extract when the timers is active
    if (_extractTimer.isActive())
        return;

    // Postpone extraction
    _extractTimer.start();
}

QVector<Cluster> Extractor::getClusters()
{
    return _algorithmAction.getSettingsAction().getClustersDataset()->getClusters();
}

void Extractor::setClusters(const QVector<Cluster>& clusters)
{
    // Get smart pointer to the clusters dataset
    auto clustersDataset = _algorithmAction.getSettingsAction().getClustersDataset();

    // Transfer extracted clusters to the clusters dataset
    clustersDataset->getClusters() = clusters;

    // Notify others that the clusters changed
    Application::core()->notifyDataChanged(clustersDataset);
}

void Extractor::addCluster(const Cluster& cluster)
{
    // Get smart pointer to the clusters dataset
    auto clustersDataset = _algorithmAction.getSettingsAction().getClustersDataset();

    // Add cluster to the clusters dataset
    clustersDataset->getClusters() << cluster;

    // Notify others that the clusters changed
    Application::core()->notifyDataChanged(clustersDataset);
}

void Extractor::resetClusters()
{
    // Get smart pointer to the clusters dataset
    auto clustersDataset = _algorithmAction.getSettingsAction().getClustersDataset();

    // Remove all clusters from the clusters dataset
    clustersDataset->getClusters().clear();

    // Notify others that the clusters changed
    Application::core()->notifyDataChanged(clustersDataset);
}

void Extractor::setDimensionIndex(std::int32_t dimensionIndex)
{
    _dimensionIndex = dimensionIndex;

    // Dimension change invalidates the clusters
    resetClusters();

    // Update the data range
    updateDataRange();

    // Notify others that the current dimension index changed
    emit dimensionIndexChanged(_dimensionIndex);
}

void Extractor::updateDataRange()
{
    // Only extract clusters from valid points dataset
    if (!getInputDataset().isValid())
        return;

    // Minimum and maximum for the current dimension
    _dataRange.first = std::numeric_limits<float>::max();
    _dataRange.second = std::numeric_limits<float>::lowest();

    getInputDataset()->visitData([this](auto pointData) {

        // Compute point value range
        for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {

            // Get point value for the dimension
            const auto pointValue = pointData[pointIndex][_dimensionIndex];

            // Compute minimum
            if (pointValue < _dataRange.first)
                _dataRange.first = pointValue;

            // Compute maximum
            if (pointValue > _dataRange.second)
                _dataRange.second = pointValue;
        }
    });

    // Notify others that the data range changed
    emit dataRangeChanged(_dataRange);
}

QPair<float, float> Extractor::getDataRange() const
{
    return _dataRange;
}

Dataset<Points> Extractor::getInputDataset()
{
    return _algorithmAction.getSettingsAction().getInputDataset();
}

Dataset<Points> Extractor::getInputDataset() const
{
    return const_cast<Extractor*>(this)->getInputDataset();
}

Dataset<Clusters> Extractor::getClustersDataset()
{
    return _algorithmAction.getSettingsAction().getClustersDataset();
}

Dataset<Clusters> Extractor::getClustersDataset() const
{
    return const_cast<Extractor*>(this)->getClustersDataset();
}

void Extractor::postExtract()
{
    // Colorize the clusters
    _algorithmAction.getSettingsAction().getClustersAction().getColorizeClustersAction().getColorizeAction().trigger();
}

ClustersModel& Extractor::getClustersModel()
{
    return _algorithmAction.getSettingsAction().getClustersAction().getClustersModel();
}
