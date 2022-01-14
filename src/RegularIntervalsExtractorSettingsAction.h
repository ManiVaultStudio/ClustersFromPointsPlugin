#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/IntegralAction.h>

using namespace hdps::gui;

class RegularIntervalsExtractor;

/**
 * Regular intervals extractor settings action class
 *
 * Action class for configuring regular intervals extractor parameters
 *
 * @author Thomas Kroes
 */
class RegularIntervalsExtractorSettingsAction : public WidgetAction
{
    Q_OBJECT

public:

    /** Widget class for histogram settings action */
    class Widget : public WidgetActionWidget
    {
    protected:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param regularIntervalsExtractorSettingsAction Pointer to regular intervals extractor settings action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, RegularIntervalsExtractorSettingsAction* regularIntervalsExtractorSettingsAction, const std::int32_t& widgetFlags);

    protected:

        friend class RegularIntervalsExtractorSettingsAction;
    };

protected:

    /**
     * Get widget representation of the histogram extractor settings action
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
     * @param RegularIntervalsExtractor Reference to regular intervals extractor
     */
    RegularIntervalsExtractorSettingsAction(RegularIntervalsExtractor& regularIntervalsExtractor);

protected: // Action getters

    IntegralAction& getNumberOfBinsAction() { return _numberOfBinsAction; }

protected:
    RegularIntervalsExtractor&      _regularIntervalsExtractor;     /** Reference to regular intervals extractor */
    IntegralAction                  _numberOfBinsAction;            /** Number of bins action */

    friend class RegularIntervalsExtractor;
};
