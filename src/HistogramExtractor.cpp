#include "HistogramExtractor.h"

using namespace hdps;
using namespace hdps::gui;

HistogramExtractor::HistogramExtractor(QObject* parent, hdps::Dataset<Points> input) :
    Extractor(parent, input),
    _settingsAction(*this)
{
}

void HistogramExtractor::extract()
{
    qDebug() << __FUNCTION__;
}

WidgetAction& HistogramExtractor::getSettingsAction()
{
    return _settingsAction;
}
