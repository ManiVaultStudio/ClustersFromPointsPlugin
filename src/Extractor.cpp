#include "Extractor.h"
#include "AlgorithmAction.h"
#include "SettingsAction.h"

using namespace hdps;

Extractor::Extractor(AlgorithmAction& algorithmAction) :
    QObject(&algorithmAction),
    _algorithmAction(algorithmAction),
    _extractTimer()
{
    // Configure extraction timer
    _extractTimer.setSingleShot(true);
    _extractTimer.setInterval(250);

    // Perform the extract process when the timer times out
    connect(&_extractTimer, &QTimer::timeout, [this]() {

        // Perform the extraction and execute post extraction operations
        extract();
        postExtract();

        // Inform others that the extraction process finished
        emit extracted();
    });
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

    _algorithmAction.getSettingsAction().getClustersAction().getColorizeClustersAction().getColorizeAction().trigger();
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
    _algorithmAction.getSettingsAction().getClustersAction().getColorizeClustersAction().getColorizeAction().trigger();
}

ClustersModel& Extractor::getClustersModel()
{
    return _algorithmAction.getSettingsAction().getClustersAction().getClustersModel();
}
