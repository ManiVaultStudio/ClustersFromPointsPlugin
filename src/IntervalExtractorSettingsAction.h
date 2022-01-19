#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/DecimalRangeAction.h>
#include <actions/IntegralAction.h>
#include <actions/StringAction.h>
#include <actions/TriggerAction.h>

#include <ClusterData.h>

using namespace hdps::gui;

class IntervalExtractor;

/**
 * Interval extractor settings action class
 *
 * Action class for configuring interval extractor settings
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
     * Get widget representation of the interval extractor settings action
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
    IntervalExtractorSettingsAction(IntervalExtractor& intervalExtractor);

public: // Action getters

    DecimalRangeAction& getRangeAction() { return _intervalAction; }
    IntegralAction& getNumberOfPointsAction() { return _numberOfPointsAction; }

protected:
    IntervalExtractor&      _intervalsExtractor;        /** Reference to interval extractor */
    DecimalRangeAction      _intervalAction;            /** Point value interval action */
    IntegralAction          _numberOfPointsAction;      /** Number of clusters in point value range action */

    friend class StratificationExtractor;
};