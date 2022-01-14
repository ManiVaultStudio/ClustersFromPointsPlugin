#include "IdentifierExtractor.h"

#include <PointData.h>

IdentifierExtractor::IdentifierExtractor(QObject* parent, hdps::Dataset<Points> input) :
    Extractor(parent, input),
    _settingsAction(*this)
{
}

void IdentifierExtractor::extract()
{
    if (!_input.isValid())
        return;

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

WidgetAction& IdentifierExtractor::getSettingsAction()
{
    return _settingsAction;
}
