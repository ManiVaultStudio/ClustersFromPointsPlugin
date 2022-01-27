#include "StratificationExtractor.h"
#include "AlgorithmAction.h"

#include <vector>
#include <numeric>

StratificationExtractor::StratificationExtractor(AlgorithmAction& algorithmAction) :
    Extractor(algorithmAction),
    _settingsAction(*this)
{
    // Update dimension picker action
    _settingsAction.getDimensionAction().setPointsDataset(getInputDataset());

    // Request extraction when the current dimension changes
    connect(&_settingsAction.getDimensionAction(), &DimensionPickerAction::currentDimensionIndexChanged, this, [this](const std::int32_t& currentDimensionIndex) {
        updateDataRange();
        requestExtraction();
    });

    updateDataRange();
    requestExtraction();
}

void StratificationExtractor::extract()
{
    // Only extract clusters from valid points dataset
    if (!getInputDataset().isValid())
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        auto minimum = std::numeric_limits<float>::max();
        auto maximum = std::numeric_limits<float>::lowest();

        // Resulting strata
        QVector<QVector<std::uint32_t>> strata;

        // Resulting clusters
        QVector<Cluster> clusters;

        getInputDataset()->visitData([this, &clusters, &minimum, &maximum, &strata](auto pointData) {

            // Get current dimension index
            const auto currentDimensionIndex = _settingsAction.getDimensionAction().getCurrentDimensionIndex();

            // Compute point value range
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {

                // Get point value for the dimension
                const auto pointValue = pointData[pointIndex][currentDimensionIndex];

                // Compute minimum
                if (pointValue < minimum)
                    minimum = pointValue;

                // Compute maximum
                if (pointValue > maximum)
                    maximum = pointValue;
            }

            // Remove previous clusters
            clusters.clear();

            // Compute the length of the point value range
            const auto pointValueRangeLength = maximum - minimum;

            if (pointValueRangeLength < 0.0f)
                return;

            // Resize to the number of strata
            strata.resize(_settingsAction.getNumberOfStrataAction().getValue());

            // Compute strata length
            const auto stratumLength = pointValueRangeLength / static_cast<float>(strata.count());

            // Put each point in the corresponding stratum
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(getInputDataset()->getNumPoints()); pointIndex++) {

                // Get point value and determine stratum index
                const auto pointValue = pointData[pointIndex][currentDimensionIndex];
                const auto binIndex = std::min(strata.count() - 1, static_cast<std::int32_t>(floorf(pointValue / stratumLength)));

                // Add index to stratum
                strata[binIndex].append(pointIndex);
            }

            // Get stratum cluster name
            const auto getClusterName = [&strata, stratumLength](const QVector<std::uint32_t>& stratum) -> QString {

                // Get the stratum index
                const auto stratumIndex = strata.indexOf(stratum);

                return "[" + QString::number(stratumIndex * stratumLength, 'f', 2) + " - " + QString::number((stratumIndex + 1) * stratumLength, 'f', 2) + "]";
            };

            // Remove empty strata
            strata.erase(std::remove_if(strata.begin(), strata.end(), [](const QVector<std::uint32_t>& stratum) {
                return stratum.count() == 0;
            }), strata.end());

            // Convert strata to clusters
            for (auto& stratum : strata)
                clusters.append(Cluster(getClusterName(stratum), Qt::gray, std::vector<std::uint32_t>(stratum.begin(), stratum.end())));
        });

        // Assign clusters to the clusters dataset
        setClusters(clusters);
    }
    QApplication::restoreOverrideCursor();
}

void StratificationExtractor::postExtract()
{
    Extractor::postExtract();
}

WidgetAction& StratificationExtractor::getSettingsAction()
{
    return _settingsAction;
}

void StratificationExtractor::updateDataRange()
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

    // Notify other that the data range changed
    emit dataRangeChanged(_dataRange);
}
