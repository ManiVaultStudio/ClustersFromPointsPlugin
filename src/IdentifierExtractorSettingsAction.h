#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/StringAction.h>
#include <actions/TriggerAction.h>

#include <PointData/DimensionPickerAction.h>

using namespace mv::gui;

class IdentifierExtractor;

/**
 * Identifier extractor settings action class
 *
 * Action class for configuring identifier extractor settings
 *
 * @author Thomas Kroes
 */
class IdentifierExtractorSettingsAction : public WidgetAction
{
    Q_OBJECT

public:

    /** Widget class for identifier extractor settings action */
    class Widget : public WidgetActionWidget
    {
    protected:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param identifierExtractorSettingsAction Pointer to identifier extractor settings action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, IdentifierExtractorSettingsAction* identifierExtractorSettingsAction, const std::int32_t& widgetFlags);

    protected:

        friend class IdentifierExtractorSettingsAction;
    };

protected:

    /**
     * Get widget representation of the identifier extractor settings action
     * @param parent Pointer to parent widget
     * @param widgetFlags Widget flags for the configuration of the widget
     */
    QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override
    {
        return new Widget(parent, this, widgetFlags);
    }

public:

    /**
     * Constructor
     * @param identifierExtractor Reference to identifier extractor
     */
    IdentifierExtractorSettingsAction(IdentifierExtractor& identifierExtractor);

protected: // Action getters

    DimensionPickerAction& getDimensionAction() { return _dimensionAction; }

protected:
    IdentifierExtractor&    _identifierExtractor;       /** Reference to identifier extractor */
    DimensionPickerAction   _dimensionAction;           /** Current dimension action */
    
    friend class IdentifierExtractor;
};
