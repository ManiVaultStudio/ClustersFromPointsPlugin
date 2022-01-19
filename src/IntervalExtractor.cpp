#include "IntervalExtractor.h"
#include "AlgorithmAction.h"

IntervalExtractor::IntervalExtractor(AlgorithmAction& algorithmAction) :
    Extractor(algorithmAction),
    _settingsAction(*this),
    _extractedCluster()
{
}

void IntervalExtractor::extract()
{
    // Only extract clusters from valid points dataset
    if (!getInputDataset().isValid())
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        // Points within the range
        std::vector<std::uint32_t> indicesInRange;

        // Reserve space for the cluster indices
        indicesInRange.reserve(getInputDataset()->getNumPoints());

        getInputDataset()->visitData([this, &indicesInRange](auto pointData) {

            // Add each point when it is in the current interval
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {

                // Get point value
                const auto pointValue = pointData[pointIndex][_dimensionIndex];

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
        Application::core()->notifyDataChanged(getClustersDataset());

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
