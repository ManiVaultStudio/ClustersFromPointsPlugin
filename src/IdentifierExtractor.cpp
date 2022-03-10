#include "IdentifierExtractor.h"
#include "AlgorithmAction.h"
#include "SettingsAction.h"

#include <ClustersAction.h>

IdentifierExtractor::IdentifierExtractor(AlgorithmAction& algorithmAction) :
    Extractor(algorithmAction),
    _settingsAction(*this)
{
    // Update dimension picker action
    _settingsAction.getDimensionAction().setPointsDataset(getInputDataset());
}

void IdentifierExtractor::extract()
{
    // Only extract clusters from valid points dataset
    if (!getInputDataset().isValid())
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        // Maps point value to cluster index
        QMap<std::uint32_t, std::uint32_t> clustersMap;

        // Resulting clusters
        QVector<Cluster> clusters;

        getInputDataset()->visitData([this, &clusters, &clustersMap](auto pointData) {

            // Get the index of the current dimension
            const auto currentDimensionIndex = _settingsAction.getDimensionAction().getCurrentDimensionIndex();

            // Only proceed if we have a valid current dimension
            if (currentDimensionIndex < 0)
                return;

            // Get cluster name prefix
            const auto prefix = _algorithmAction.getSettingsAction().getClustersAction().getPrefixClustersAction().getPrefixAction().getString();

            //#pragma omp parallel for schedule(dynamic,1)
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {
                const auto clusterIndex = static_cast<std::uint32_t>(pointData[pointIndex][currentDimensionIndex]);

                if (!clustersMap.contains(clusterIndex)) {
                    clusters.append(Cluster(prefix + QString::number(clusterIndex)));
                    clustersMap[clusterIndex] = static_cast<std::uint32_t>(clusters.size()) - 1;
                }

                // Add point index to the corresponding cluster
                clusters[clustersMap[clusterIndex]].getIndices().push_back(pointIndex);
            }
        });

        // Assign clusters to the clusters dataset
        setClusters(clusters);
    }
    QApplication::restoreOverrideCursor();
}

void IdentifierExtractor::postExtract()
{
    Extractor::postExtract();
}

WidgetAction& IdentifierExtractor::getSettingsAction()
{
    return _settingsAction;
}
