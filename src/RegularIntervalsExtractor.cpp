#include "RegularIntervalsExtractor.h"

RegularIntervalsExtractor::RegularIntervalsExtractor(QObject* parent, hdps::Dataset<Points> input) :
    Extractor(parent, input),
    _settingsAction(*this)
{
}

void RegularIntervalsExtractor::extract()
{
    auto minimum = std::numeric_limits<float>::max();
    auto maximum = std::numeric_limits<float>::lowest();

    // Histogram bins
    QVector<QVector<std::uint32_t>> bins;

    _input->visitData([this, &minimum, &maximum, &bins](auto pointData) {

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

        // Resize to the number of histogram bins
        bins.resize(_settingsAction.getNumberOfBinsAction().getValue());

        // Compute bin length
        const auto binLength = pointValueRangeLength / static_cast<float>(bins.count());

        // Perform the histogram binning
        for (std::int32_t pointIndex = 0; pointIndex < static_cast<std::int32_t>(_input->getNumPoints()); pointIndex++) {

            // Get point value and determine bin index
            const auto pointValue   = pointData[pointIndex][_dimensionIndex];
            const auto binIndex     = std::min(bins.count() - 1, static_cast<std::int32_t>(floorf(pointValue / binLength)));
                
            // Add index to bin
            bins[binIndex].append(pointIndex);
        }

        // Convert bins to clusters
        for (auto& bin : bins)
            _clusters.append(Cluster("", Qt::gray, std::vector<std::uint32_t>(bin.begin(), bin.end())));
    });
}

WidgetAction& RegularIntervalsExtractor::getSettingsAction()
{
    return _settingsAction;
}
