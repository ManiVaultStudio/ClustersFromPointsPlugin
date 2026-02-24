#include "IdentifierExtractor.h"
#include "AlgorithmAction.h"
#include "SettingsAction.h"

#include <ClusterData/ClustersAction.h>
#include <DataType.h>

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <omp.h>

IdentifierExtractor::IdentifierExtractor(AlgorithmAction& algorithmAction) :
    Extractor(algorithmAction),
    _settingsAction(*this)
{
    // Update dimension picker action
    _settingsAction.getDimensionAction().setPointsDataset(getInputDataset());

    _settingsAction.getExternalDatasetAction().setFilterFunction([this](const mv::Dataset<Points>& dataset) {
        if (dataset->getDataType() != PointType)
            return false;

        const auto pointsDataset = Dataset<Points>(dataset);

        if (pointsDataset->getNumPoints() != _algorithmAction.getSettingsAction().getInputDataset()->getNumPoints())
            return false;

        return dataset.isValid();
	});

    connect(&_settingsAction.getExternalDatasetAction(), &DatasetPickerAction::datasetPicked, this, [this]() {
        _settingsAction.getDimensionAction().setPointsDataset(getInputDataset());
	});
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

    	getInputDataset()->visitData([this, &clusters](auto pointData) {
			const auto currentDimensionIndex =
				_settingsAction.getDimensionAction().getCurrentDimensionIndex();
			if (currentDimensionIndex < 0) return;

			const auto prefix = _algorithmAction.getSettingsAction().getClustersAction().getPrefixClustersAction().getPrefixAction().getString();

			const std::int32_t n = static_cast<std::int32_t>(getInputDataset()->getNumPoints());

			const int T = omp_get_max_threads();

			// Per-thread: map clusterID -> vector of point indices
			std::vector<std::unordered_map<std::uint32_t, std::vector<std::int32_t>>> local(T);
			
			for (auto& m : local) m.reserve(1024);

#pragma omp parallel
			{
				const int tid = omp_get_thread_num();
				auto& m = local[tid];

#pragma omp for schedule(static)
				for (std::int32_t pointIndex = 0; pointIndex < n; ++pointIndex) {
					const auto clusterId = static_cast<std::uint32_t>(pointData[pointIndex][currentDimensionIndex]);
					m[clusterId].push_back(pointIndex);
				}
			}

			std::unordered_map<std::uint32_t, std::vector<std::int32_t>> merged;
			
			merged.reserve(4096);

			for (auto& m : local) {
				for (auto& kv : m) {
					auto& dst = merged[kv.first];
					
					dst.insert(dst.end(), kv.second.begin(), kv.second.end());
					std::vector<std::int32_t>().swap(kv.second);
				}
				m.clear();
			}

			std::vector<std::uint32_t> keys;
			keys.reserve(merged.size());

			for (auto& kv : merged)
                keys.push_back(kv.first);

    		std::sort(keys.begin(), keys.end());

			clusters.clear();
			clusters.reserve(static_cast<int>(keys.size()));

			for (auto clusterId : keys) {
				Cluster c(prefix + QString::number(clusterId));

				auto& idx = merged[clusterId];
				auto& out = c.getIndices();

				out.reserve(idx.size());

				for (auto pi : idx)
                    out.push_back(pi);

				clusters.append(std::move(c));
			}
			});
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

mv::Dataset<Points> IdentifierExtractor::getInputDataset()
{
    if (_settingsAction.getExternalDatasetAction().getCurrentDataset().isValid())
        return _settingsAction.getExternalDatasetAction().getCurrentDataset();

	return Extractor::getInputDataset();
}
