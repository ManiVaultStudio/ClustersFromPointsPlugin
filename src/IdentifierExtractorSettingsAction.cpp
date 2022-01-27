#include "IdentifierExtractorSettingsAction.h"
#include "IdentifierExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

IdentifierExtractorSettingsAction::IdentifierExtractorSettingsAction(IdentifierExtractor& identifierExtractor) :
    WidgetAction(&identifierExtractor),
    _dimensionAction(this, "Dimension"),
    _identifierExtractor(identifierExtractor)
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    // Request extraction when the current dimension changes
    connect(&_dimensionAction, &DimensionPickerAction::currentDimensionIndexChanged, this, [this](const std::int32_t& currentDimensionIndex) {
        _identifierExtractor.requestExtraction();
    });
}

IdentifierExtractorSettingsAction::Widget::Widget(QWidget* parent, IdentifierExtractorSettingsAction* identifierExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, identifierExtractorSettingsAction, widgetFlags)
{
    auto layout = new QHBoxLayout();

    layout->addWidget(identifierExtractorSettingsAction->getDimensionAction().createLabelWidget(this));
    layout->addWidget(identifierExtractorSettingsAction->getDimensionAction().createWidget(this));

    setPopupLayout(layout);
}
