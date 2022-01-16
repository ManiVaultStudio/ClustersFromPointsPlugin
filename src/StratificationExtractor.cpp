#include "StratificationExtractor.h"
#include "AlgorithmAction.h"

#include <vector>
#include <numeric>

StratificationExtractor::StratificationExtractor(AlgorithmAction& algorithmAction, hdps::Dataset<Points> input) :
    Extractor(algorithmAction, input),
    _settingsAction(*this)
{
}

void StratificationExtractor::extract()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        auto minimum = std::numeric_limits<float>::max();
        auto maximum = std::numeric_limits<float>::lowest();

        // Resulting strata
        QVector<QVector<std::uint32_t>> strata;

        _input->visitData([this, &minimum, &maximum, &strata](auto pointData) {

            // Compute point value range
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(_input->getNumPoints()); pointIndex++) {

                // Get point value for the dimension
                const auto pointValue = pointData[pointIndex][_dimensionIndex];

                // Compute minimum
                if (pointValue < minimum)
                    minimum = pointValue;

                // Compute maximum
                if (pointValue > maximum)
                    maximum = pointValue;
            }

            // Remove previous clusters
            _clusters.clear();

            // Compute the length of the point value range
            const auto pointValueRangeLength = maximum - minimum;

            if (pointValueRangeLength < 0.0f)
                return;

            // Resize to the number of strata
            strata.resize(_settingsAction.getNumberOfStrataAction().getValue());

            // Compute strata length
            const auto stratumLength = pointValueRangeLength / static_cast<float>(strata.count());

            // Put each point in the corresponding stratum
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(_input->getNumPoints()); pointIndex++) {

                // Get point value and determine stratum index
                const auto pointValue = pointData[pointIndex][_dimensionIndex];
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
                _clusters.append(Cluster(getClusterName(stratum), Qt::gray, std::vector<std::uint32_t>(stratum.begin(), stratum.end())));
        });
    }
    QApplication::restoreOverrideCursor();
}

void StratificationExtractor::postExtract()
{
}

WidgetAction& StratificationExtractor::getSettingsAction()
{
    return _settingsAction;
}
