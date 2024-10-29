#include "IdentifierExtractorSettingsAction.h"
#include "IdentifierExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

IdentifierExtractorSettingsAction::IdentifierExtractorSettingsAction(IdentifierExtractor& identifierExtractor) :
    WidgetAction(&identifierExtractor, "IdentifierExtractorSettingsAction"),
    _dimensionAction(this, "Dimension"),
    _identifierExtractor(identifierExtractor)
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");
}

IdentifierExtractorSettingsAction::Widget::Widget(QWidget* parent, IdentifierExtractorSettingsAction* identifierExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, identifierExtractorSettingsAction, widgetFlags)
{
    auto layout = new QHBoxLayout();

    layout->addWidget(identifierExtractorSettingsAction->getDimensionAction().createLabelWidget(this));
    layout->addWidget(identifierExtractorSettingsAction->getDimensionAction().createWidget(this));

    setLayout(layout);
}
