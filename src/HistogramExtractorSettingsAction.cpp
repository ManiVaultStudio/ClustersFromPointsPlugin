#include "HistogramExtractorSettingsAction.h"
#include "HistogramExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

using namespace hdps;

HistogramExtractorSettingsAction::HistogramExtractorSettingsAction(HistogramExtractor& histogramExtractor) :
    WidgetAction(&histogramExtractor),
    _histogramExtractor(histogramExtractor),
    _numberOfBinsAction(this, "Number of bins")
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    // Request extraction when the number of histogram bins changes
    connect(&_numberOfBinsAction, &IntegralAction::valueChanged, this, [&histogramExtractor]() {
        histogramExtractor.requestExtraction();
    });
}

HistogramExtractorSettingsAction::Widget::Widget(QWidget* parent, HistogramExtractorSettingsAction* histogramExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, histogramExtractorSettingsAction, widgetFlags)
{
    auto layout = new QHBoxLayout();

    layout->addWidget(histogramExtractorSettingsAction->getNumberOfBinsAction().createLabelWidget(this));
    layout->addWidget(histogramExtractorSettingsAction->getNumberOfBinsAction().createWidget(this));

    setPopupLayout(layout);
}
