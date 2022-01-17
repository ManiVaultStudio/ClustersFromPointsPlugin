#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/DecimalRangeAction.h>
#include <actions/IntegralAction.h>
#include <actions/TriggerAction.h>

using namespace hdps::gui;

class CustomIntervalsExtractor;

/**
 * Interval extractor settings action class
 *
 * Action class for configuring interval extractor parameters
 *
 * @author Thomas Kroes
 */
class IntervalExtractorSettingsAction : public WidgetAction
{
    Q_OBJECT

public:

    /** Widget class for interval extractor settings action */
    class Widget : public WidgetActionWidget
    {
    protected:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param intervalExtractorSettingsAction Pointer to interval extractor settings action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, IntervalExtractorSettingsAction* intervalExtractorSettingsAction, const std::int32_t& widgetFlags);

    protected:

        friend class IntervalExtractorSettingsAction;
    };

protected:

    /**
     * Get widget representation of the stratification interval settings action
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
     * @param intervalExtractor Reference to interval extractor
     */
    IntervalExtractorSettingsAction(CustomIntervalsExtractor& intervalExtractor);

protected: // Action getters

    DecimalRangeAction& getRangeAction() { return _rangeAction; }
    IntegralAction& getNumberOfClustersInRangeAction() { return _numberOfClustersInRangeAction; }
    TriggerAction& getAddClusterAction() { return _addClusterAction; }

protected:
    CustomIntervalsExtractor&      _stratificationExtractor;           /** Reference to interval extractor */
    DecimalRangeAction      _rangeAction;                       /** Point value range action */
    IntegralAction          _numberOfClustersInRangeAction;     /** Number of clusters in point value range action */
    TriggerAction           _addClusterAction;                  /** Add clusters action */

    friend class StratificationExtractor;
};
