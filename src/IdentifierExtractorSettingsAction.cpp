#include "IdentifierExtractorSettingsAction.h"
#include "IdentifierExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

IdentifierExtractorSettingsAction::IdentifierExtractorSettingsAction(IdentifierExtractor& identifierExtractor) :
    WidgetAction(&identifierExtractor),
    _identifierExtractor(identifierExtractor)
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");
}

IdentifierExtractorSettingsAction::Widget::Widget(QWidget* parent, IdentifierExtractorSettingsAction* identifierExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, identifierExtractorSettingsAction, widgetFlags)
{
    auto layout = new QHBoxLayout();

    setPopupLayout(layout);
}
