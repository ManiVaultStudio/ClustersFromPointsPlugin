#include "RegularIntervalsExtractorSettingsAction.h"
#include "RegularIntervalsExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

using namespace hdps;

RegularIntervalsExtractorSettingsAction::RegularIntervalsExtractorSettingsAction(RegularIntervalsExtractor& regularIntervalsExtractor) :
    WidgetAction(&regularIntervalsExtractor),
    _regularIntervalsExtractor(regularIntervalsExtractor),
    _numberOfBinsAction(this, "Number of bins", 1, 100, 10, 10)
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    _numberOfBinsAction.setUpdateDuringDrag(false);

    // Request extraction when the number of histogram bins changes
    connect(&_numberOfBinsAction, &IntegralAction::valueChanged, &_regularIntervalsExtractor, &RegularIntervalsExtractor::requestExtraction);
}

RegularIntervalsExtractorSettingsAction::Widget::Widget(QWidget* parent, RegularIntervalsExtractorSettingsAction* regularIntervalsExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, regularIntervalsExtractorSettingsAction, widgetFlags)
{
    auto layout = new QHBoxLayout();

    layout->addWidget(regularIntervalsExtractorSettingsAction->getNumberOfBinsAction().createLabelWidget(this));
    layout->addWidget(regularIntervalsExtractorSettingsAction->getNumberOfBinsAction().createWidget(this));

    setPopupLayout(layout);
}
