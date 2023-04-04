#include "IndexExtractor.h"
#include "AlgorithmAction.h"
#include "SettingsAction.h"

#include <ClusterData/ClustersAction.h>

#include <util/Timer.h>

IndexExtractor::IndexExtractor(AlgorithmAction& algorithmAction) :
    Extractor(algorithmAction),
    _settingsAction(*this)
{
}

void IndexExtractor::extract()
{
    // Only extract clusters from valid points dataset
    if (!getInputDataset().isValid())
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        // Remove existing clusters
        resetClusters();

        Timer timer;

        // Maps point value to cluster index
        QMap<std::uint32_t, std::uint32_t> clustersMap;

        // Resulting clusters
        QVector<Cluster> clusters;

        // Allocate room for clusters
        clusters.resize(getInputDataset()->getNumPoints());

        // Get cluster name prefix
        const auto prefix = _algorithmAction.getSettingsAction().getClustersAction().getPrefixClustersAction().getPrefixAction().getString();

        getInputDataset()->visitData([this, &clusters, &clustersMap, prefix](auto pointData) {
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {

                // Get point index with possible offset
                const auto offsetPointIndex = static_cast<std::uint32_t>(pointIndex) + _settingsAction.getStartIndexAction().getValue();

                // Add cluster for the point
                clusters[pointIndex] = Cluster(prefix + QString::number(offsetPointIndex), Qt::gray, { offsetPointIndex });
            }
        });

        // Assign clusters to the clusters dataset
        setClusters(clusters);

        // Print debug message
        timer.printElapsedTime("Index extraction");
    }
    QApplication::restoreOverrideCursor();
}

void IndexExtractor::postExtract()
{
    Extractor::postExtract();

    // Provide each cluster with a prefix
    //_algorithmAction.getSettingsAction().getClustersAction().getPrefixClustersAction().getApplyAction().trigger();
}

WidgetAction& IndexExtractor::getSettingsAction()
{
    return _settingsAction;
}
