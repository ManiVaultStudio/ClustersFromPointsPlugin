#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/DecimalRangeAction.h>
#include <actions/IntegralAction.h>
#include <actions/StringAction.h>
#include <actions/TriggerAction.h>

#include <ClusterData.h>

using namespace hdps::gui;

class IntervalsExtractor;

/**
 * Intervals extractor settings action class
 *
 * Action class for configuring custom intervals extractor settings
 *
 * @author Thomas Kroes
 */
class IntervalsExtractorSettingsAction : public WidgetAction
{
    Q_OBJECT

public:

    /** Widget class for intervals extractor settings action */
    class Widget : public WidgetActionWidget
    {
    protected:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param intervalsExtractorSettingsAction Pointer to intervals extractor settings action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, IntervalsExtractorSettingsAction* intervalsExtractorSettingsAction, const std::int32_t& widgetFlags);

    protected:

        friend class IntervalsExtractorSettingsAction;
    };

protected:

    /**
     * Get widget representation of the intervals settings action
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
     * @param intervalsExtractor Reference to intervals extractor
     */
    IntervalsExtractorSettingsAction(IntervalsExtractor& intervalsExtractor);

public: // Action getters

    DecimalRangeAction& getRangeAction() { return _intervalAction; }
    IntegralAction& getNumberOfPointsAction() { return _numberOfPointsAction; }

protected:
    IntervalsExtractor&     _intervalsExtractor;        /** Reference to intervals extractor */
    DecimalRangeAction      _intervalAction;            /** Point value interval action */
    IntegralAction          _numberOfPointsAction;      /** Number of clusters in point value range action */

    friend class StratificationExtractor;
};
