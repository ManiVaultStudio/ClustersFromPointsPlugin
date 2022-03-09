#include "IntervalExtractor.h"
#include "AlgorithmAction.h"

IntervalExtractor::IntervalExtractor(AlgorithmAction& algorithmAction) :
    Extractor(algorithmAction),
    _settingsAction(*this),
    _extractedCluster()
{
    // Update dimension picker action
    _settingsAction.getDimensionAction().setPointsDataset(getInputDataset());
}

void IntervalExtractor::extract()
{
    // Only extract clusters from valid points dataset
    if (!getInputDataset().isValid())
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        // Remove existing clusters
        resetClusters();

        // Points within the range
        std::vector<std::uint32_t> indicesInRange;

        // Reserve space for the cluster indices
        indicesInRange.reserve(getInputDataset()->getNumPoints());

        getInputDataset()->visitData([this, &indicesInRange](auto pointData) {

            // Get current dimension index
            const auto currentDimensionIndex = _settingsAction.getDimensionAction().getCurrentDimensionIndex();

            // Add each point when it is in the current interval
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {

                // Get point value
                const auto pointValue = pointData[pointIndex][currentDimensionIndex];

                // And add it to the indices when it resides in the interval
                if (pointValue >= _settingsAction.getRangeAction().getMinimum() && pointValue <= _settingsAction.getRangeAction().getMaximum())
                    indicesInRange.push_back(pointIndex);
            }

            // Only add cluster when there are one or more cluster indices
            if (indicesInRange.empty())
                return;
        });

        // Update candidate cluster
        _extractedCluster.setName("[" + QString::number(_settingsAction.getRangeAction().getMinimum()) + " - " + QString::number(_settingsAction.getRangeAction().getMaximum()) + "]");
        _extractedCluster.setIndices(indicesInRange);

        // Ensure that the cluster exists in the clusters dataset
        if (getClustersDataset()->getClusters().isEmpty())
            addCluster(_extractedCluster);

        // Transfer extracted cluster to clusters dataset
        getClustersDataset()->getClusters().first() = _extractedCluster;

        // Notify others that the clusters changed
        Application::core()->notifyDatasetChanged(getClustersDataset());

        // Select points in the cluster
        getClustersDataset()->setSelectionIndices({ 0 });
    }
    QApplication::restoreOverrideCursor();
}

void IntervalExtractor::postExtract()
{
    Extractor::postExtract();
}

WidgetAction& IntervalExtractor::getSettingsAction()
{
    return _settingsAction;
}

Cluster IntervalExtractor::getCluster()
{
    return _extractedCluster.copy();
}

QPair<float, float> IntervalExtractor::getDataRange() const
{
    return _dataRange;
}

void IntervalExtractor::updateDataRange()
{
    // Only extract clusters from valid points dataset
    if (!getInputDataset().isValid())
        return;

    // Minimum and maximum for the current dimension
    _dataRange.first    = std::numeric_limits<float>::max();
    _dataRange.second   = std::numeric_limits<float>::lowest();

    getInputDataset()->visitData([this](auto pointData) {

        // Compute point value range
        for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {

            // Get point value for the dimension
            const auto pointValue = pointData[pointIndex][_settingsAction.getDimensionAction().getCurrentDimensionIndex()];

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
