#include "IdentifierExtractor.h"
#include "AlgorithmAction.h"
#include "ExtractorAction.h"

#include <ClustersAction.h>

IdentifierExtractor::IdentifierExtractor(AlgorithmAction& algorithmAction, hdps::Dataset<Points> input) :
    Extractor(algorithmAction, input),
    _settingsAction(*this)
{
}

void IdentifierExtractor::extract()
{
    if (!_input.isValid())
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        // Remove previous clusters
        _clusters.clear();

        // Maps point value to cluster index
        QMap<std::uint32_t, std::uint32_t> clustersMap;

        _input->visitData([this, &clustersMap](auto pointData) {
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(_input->getNumPoints()); pointIndex++) {
                const auto clusterIndex = static_cast<std::uint32_t>(pointData[pointIndex][_dimensionIndex]);

                if (!clustersMap.contains(clusterIndex)) {
                    _clusters.append(Cluster());
                    clustersMap[clusterIndex] = static_cast<std::uint32_t>(_clusters.size()) - 1;
                }

                _clusters[clustersMap[clusterIndex]].getIndices().push_back(pointIndex);
            }
        });
    }
    QApplication::restoreOverrideCursor();
}

void IdentifierExtractor::postExtract()
{
    _algorithmAction.getExtractorAction().getClustersAction().getPrefixClustersAction().getApplyAction().trigger();
}

WidgetAction& IdentifierExtractor::getSettingsAction()
{
    return _settingsAction;
}
