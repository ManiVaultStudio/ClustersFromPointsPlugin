#include "IdentifierExtractor.h"
#include "AlgorithmAction.h"
#include "SettingsAction.h"

#include <ClustersAction.h>

IdentifierExtractor::IdentifierExtractor(AlgorithmAction& algorithmAction) :
    Extractor(algorithmAction),
    _settingsAction(*this)
{
    // Request an extraction when the current dimension index changes
    connect(this, &Extractor::dimensionIndexChanged, this, &Extractor::requestExtraction);

    // Request an initial extraction
    requestExtraction();
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
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {
                const auto clusterIndex = static_cast<std::uint32_t>(pointData[pointIndex][_dimensionIndex]);

                if (!clustersMap.contains(clusterIndex)) {
                    clusters.append(Cluster());
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

    // Provide each cluster with a prefix
    _algorithmAction.getSettingsAction().getClustersAction().getPrefixClustersAction().getApplyAction().trigger();
}

WidgetAction& IdentifierExtractor::getSettingsAction()
{
    return _settingsAction;
}
