#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/IntegralAction.h>

#include <PointData/DimensionPickerAction.h>

using namespace mv::gui;

class StratificationExtractor;

/**
 * Stratification extractor settings action class
 *
 * Action class for configuring stratification extractor settings
 *
 * @author Thomas Kroes
 */
class StratificationExtractorSettingsAction : public WidgetAction
{
    Q_OBJECT

public:

    /** Widget class for stratification extractor settings action */
    class Widget : public WidgetActionWidget
    {
    protected:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param stratificationExtractorSettingsAction Pointer to stratification extractor settings action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, StratificationExtractorSettingsAction* stratificationExtractorSettingsAction, const std::int32_t& widgetFlags);

    protected:

        friend class StratificationExtractorSettingsAction;
    };

protected:

    /**
     * Get widget representation of the stratification extractor settings action
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
     * @param stratificationExtractor Reference to stratification extractor
     */
    StratificationExtractorSettingsAction(StratificationExtractor& stratificationExtractor);

protected: // Action getters

    DimensionPickerAction& getDimensionAction() { return _dimensionAction; }
    IntegralAction& getNumberOfStrataAction() { return _numberOfStrataAction; }

protected:
    StratificationExtractor&    _stratificationExtractor;   /** Reference to stratification extractor */
    DimensionPickerAction       _dimensionAction;           /** Current dimension action */
    IntegralAction              _numberOfStrataAction;      /** Number of bins action */

    friend class StratificationExtractor;
};
