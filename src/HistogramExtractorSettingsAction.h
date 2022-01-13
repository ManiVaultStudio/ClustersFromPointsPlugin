#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/IntegralAction.h>

using namespace hdps::gui;

class HistogramExtractor;

/**
 * Histogram extractor settings action class
 *
 * Action class for configuring histogram extractor parameters
 *
 * @author Thomas Kroes
 */
class HistogramExtractorSettingsAction : public WidgetAction
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
         * @param histogramExtractorSettingsAction Pointer to histogram extractor settings action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, HistogramExtractorSettingsAction* histogramExtractorSettingsAction, const std::int32_t& widgetFlags);

    protected:

        friend class HistogramExtractorSettingsAction;
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
     * @param histogramExtractor Reference to histogram extractor
     */
    HistogramExtractorSettingsAction(HistogramExtractor& histogramExtractor);

protected: // Action getters

    IntegralAction& getNumberOfBinsAction() { return _numberOfBinsAction; }

protected:
    HistogramExtractor&     _histogramExtractor;        /** Reference to histogram extractor */
    IntegralAction          _numberOfBinsAction;        /** Number of bins action */

    friend class HistogramExtractor;
};
