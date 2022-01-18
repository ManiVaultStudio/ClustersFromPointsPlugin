#include "CustomIntervalsExtractor.h"
#include "AlgorithmAction.h"

#include <vector>
#include <numeric>

CustomIntervalsExtractor::CustomIntervalsExtractor(AlgorithmAction& algorithmAction) :
    Extractor(algorithmAction),
    _settingsAction(*this),
    _candidateCluster()
{
}

void CustomIntervalsExtractor::extract()
{
    // Only extract clusters from valid points dataset
    if (!getInputDataset().isValid())
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        // Points within the range
        QVector<std::uint32_t> indicesInRange;

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
            if (indicesInRange.isEmpty())
                return;

            // Establish cluster name
            const auto clusterName = "[" + QString::number(_settingsAction.getRangeAction().getMinimum()) + " - " + QString::number(_settingsAction.getRangeAction().getMaximum()) + "]";

            // Update candidate cluster
            _candidateCluster = Cluster(clusterName, Qt::gray, std::vector<std::uint32_t>(indicesInRange.begin(), indicesInRange.end()));
        });
    }
    QApplication::restoreOverrideCursor();
}

void CustomIntervalsExtractor::postExtract()
{
    Extractor::postExtract();
}

WidgetAction& CustomIntervalsExtractor::getSettingsAction()
{
    return _settingsAction;
}

Cluster& CustomIntervalsExtractor::getCandidateCluster()
{
    return _candidateCluster;
}
