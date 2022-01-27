#include "StratificationExtractorSettingsAction.h"
#include "StratificationExtractor.h"

#include <Application.h>

#include <QGridLayout>

using namespace hdps;

StratificationExtractorSettingsAction::StratificationExtractorSettingsAction(StratificationExtractor& stratificationExtractor) :
    WidgetAction(&stratificationExtractor),
    _stratificationExtractor(stratificationExtractor),
    _dimensionAction(this, "Dimension"),
    _numberOfStrataAction(this, "Number of strata", 1, 100, 10, 10)
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    _numberOfStrataAction.setUpdateDuringDrag(false);

    // Request extraction when the number of strata changes
    connect(&_numberOfStrataAction, &IntegralAction::valueChanged, &_stratificationExtractor, &StratificationExtractor::requestExtraction);
}

StratificationExtractorSettingsAction::Widget::Widget(QWidget* parent, StratificationExtractorSettingsAction* stratificationExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, stratificationExtractorSettingsAction, widgetFlags)
{
    auto layout = new QGridLayout();

    layout->addWidget(stratificationExtractorSettingsAction->getDimensionAction().createLabelWidget(this), 0, 0);
    layout->addWidget(stratificationExtractorSettingsAction->getDimensionAction().createWidget(this), 0, 1);
    layout->addWidget(stratificationExtractorSettingsAction->getNumberOfStrataAction().createLabelWidget(this), 1, 0);
    layout->addWidget(stratificationExtractorSettingsAction->getNumberOfStrataAction().createWidget(this), 1, 1);

    setPopupLayout(layout);
}
