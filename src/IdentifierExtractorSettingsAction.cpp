#include "IdentifierExtractorSettingsAction.h"
#include "IdentifierExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

IdentifierExtractorSettingsAction::IdentifierExtractorSettingsAction(IdentifierExtractor& identifierExtractor) :
    WidgetAction(&identifierExtractor),
    _identifierExtractor(identifierExtractor),
    _prefixAction(this, "Name prefix", "id_", "id_"),
    _applyAction(this, "Apply")
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    // Update read only status of apply action
    const auto updateApplyReadOnly = [this]() -> void {
        _applyAction.setEnabled(_prefixAction.isResettable());
    };

    // Update read only status of apply action when the prefix string changes
    connect(&_prefixAction, &StringAction::stringChanged, this, updateApplyReadOnly);

    // Apply the prefix when the apply action is triggered
    connect(&_applyAction, &TriggerAction::triggered, this, [this, updateApplyReadOnly]() {

        // Get cluster name prefix
        const auto clusterNamePrefix = _prefixAction.getString();

        // Set cluster name prefix in extractor
        _identifierExtractor.setClusterNamePrefix(clusterNamePrefix);

        // Change prefix default string
        _prefixAction.setDefaultString(clusterNamePrefix);

        // Update read only status
        updateApplyReadOnly();
    });

    // Perform initial update of the read only status
    updateApplyReadOnly();
}

IdentifierExtractorSettingsAction::Widget::Widget(QWidget* parent, IdentifierExtractorSettingsAction* identifierExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, identifierExtractorSettingsAction, widgetFlags)
{
    auto layout = new QHBoxLayout();

    layout->addWidget(identifierExtractorSettingsAction->getClusterNamePrefixAction().createLabelWidget(this));
    layout->addWidget(identifierExtractorSettingsAction->getClusterNamePrefixAction().createWidget(this));
    layout->addWidget(identifierExtractorSettingsAction->getApplyAction().createWidget(this));

    setPopupLayout(layout);
}
