#include "StratificationExtractorSettingsAction.h"
#include "StratificationExtractor.h"

#include <Application.h>

#include <QGridLayout>

using namespace mv;

StratificationExtractorSettingsAction::StratificationExtractorSettingsAction(StratificationExtractor& stratificationExtractor) :
    WidgetAction(&stratificationExtractor, "StratificationExtractorSettingsAction"),
    _stratificationExtractor(stratificationExtractor),
    _dimensionAction(this, "Dimension"),
    _numberOfStrataAction(this, "Number of strata", 1, 100, 10)
{
    setIconByName("gear");
    setText("Settings");

    _numberOfStrataAction.setUpdateDuringDrag(false);
}

StratificationExtractorSettingsAction::Widget::Widget(QWidget* parent, StratificationExtractorSettingsAction* stratificationExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, stratificationExtractorSettingsAction, widgetFlags)
{
    auto layout = new QGridLayout();

    layout->addWidget(stratificationExtractorSettingsAction->getDimensionAction().createLabelWidget(this), 0, 0);
    layout->addWidget(stratificationExtractorSettingsAction->getDimensionAction().createWidget(this), 0, 1);
    layout->addWidget(stratificationExtractorSettingsAction->getNumberOfStrataAction().createLabelWidget(this), 1, 0);
    layout->addWidget(stratificationExtractorSettingsAction->getNumberOfStrataAction().createWidget(this), 1, 1);

    setLayout(layout);
}
