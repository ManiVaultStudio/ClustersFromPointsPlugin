#include "CustomIntervalsExtractor.h"
#include "AlgorithmAction.h"

#include <vector>
#include <numeric>

CustomIntervalsExtractor::CustomIntervalsExtractor(AlgorithmAction& algorithmAction, hdps::Dataset<Points> input) :
    Extractor(algorithmAction, input),
    _settingsAction(*this)
{
}

void CustomIntervalsExtractor::extract()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    {
        // Points within the range
        QVector<std::uint32_t> indicesInRange;

        indicesInRange.reserve(_input->getNumPoints());

        _input->visitData([this, &indicesInRange](auto pointData) {

            // Put each point in the corresponding stratum
            for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(_input->getNumPoints()); pointIndex++) {

                // Get point value and determine stratum index
                const auto pointValue   = pointData[pointIndex][_dimensionIndex];

                if (pointValue >= _settingsAction.getRangeAction().getMinimum() && pointValue <= _settingsAction.getRangeAction().getMinimum())
                    indicesInRange.push_back(pointIndex);
            }

            if (indicesInRange.isEmpty())
                return;

            // Get cluster name
            const auto clusterName = "[" + QString::number(_settingsAction.getRangeAction().getMinimum()) + " - " + QString::number(_settingsAction.getRangeAction().getMaximum()) + "]";

            // Add cluster
            _clusters.append(Cluster(clusterName, Qt::gray, std::vector<std::uint32_t>(indicesInRange.begin(), indicesInRange.end())));
        });
    }
    QApplication::restoreOverrideCursor();
}

void CustomIntervalsExtractor::postExtract()
{
}

WidgetAction& CustomIntervalsExtractor::getSettingsAction()
{
    return _settingsAction;
}
