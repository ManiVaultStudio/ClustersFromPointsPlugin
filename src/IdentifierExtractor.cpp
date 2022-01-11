#include "IdentifierExtractor.h"

#include <PointData.h>

using namespace hdps;
using namespace hdps::gui;

IdentifierExtractor::IdentifierExtractor(QObject* parent, hdps::Dataset<Points> input) :
    Extractor(parent, input),
    _settingsAction(*this)
{
}

void IdentifierExtractor::extract()
{
    qDebug() << __FUNCTION__;

    if (!_input.isValid())
        return;

    _clusters.clear();
    _clusters.reserve(_input->getNumPoints());

    _input->visitData([this](auto pointData) {
        //for (std::int32_t pointIndex = 0; pointIndex < _input->getNumPoints(); pointIndex++) {
        //    clusters[pointIndex] = pointData[pointIndex][dimensionIndex];
        //}
    });
}

WidgetAction& IdentifierExtractor::getSettingsAction()
{
    return _settingsAction;
}
