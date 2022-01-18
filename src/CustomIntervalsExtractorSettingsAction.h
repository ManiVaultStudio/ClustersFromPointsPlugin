#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/DecimalRangeAction.h>
#include <actions/IntegralAction.h>
#include <actions/StringAction.h>
#include <actions/TriggerAction.h>

#include <ClusterData.h>

using namespace hdps::gui;

class CustomIntervalsExtractor;

/**
 * Custom intervals extractor settings action class
 *
 * Action class for configuring custom intervals extractor parameters
 *
 * @author Thomas Kroes
 */
class CustomIntervalsExtractorSettingsAction : public WidgetAction
{
    Q_OBJECT

public:

    /** Widget class for custom intervals extractor settings action */
    class Widget : public WidgetActionWidget
    {
    protected:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param customIntervalsExtractorSettingsAction Pointer to custom intervals extractor settings action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, CustomIntervalsExtractorSettingsAction* customIntervalsExtractorSettingsAction, const std::int32_t& widgetFlags);

    protected:

        friend class CustomIntervalsExtractorSettingsAction;
    };

protected:

    /**
     * Get widget representation of the custom intervals settings action
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
     * @param customIntervalsExtractor Reference to custom intervals extractor
     */
    CustomIntervalsExtractorSettingsAction(CustomIntervalsExtractor& customIntervalsExtractor);

public: // Action getters

    DecimalRangeAction& getRangeAction() { return _intervalAction; }
    IntegralAction& getNumberOfClustersInRangeAction() { return _numberOfPointsAction; }
    StringAction& getClusterNameAction() { return _clusterNameAction; }
    TriggerAction& getAddClusterAction() { return _addClusterAction; }

protected:
    CustomIntervalsExtractor&   _customIntervalsExtractor;      /** Reference to custom intervals extractor */
    DecimalRangeAction          _intervalAction;                /** Point value interval action */
    IntegralAction              _numberOfPointsAction;          /** Number of clusters in point value range action */
    StringAction                _clusterNameAction;             /** Cluster name action */
    TriggerAction               _addClusterAction;              /** Add clusters action */

    friend class StratificationExtractor;
};
