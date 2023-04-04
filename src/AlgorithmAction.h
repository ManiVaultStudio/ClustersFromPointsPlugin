#pragma once

#include "Extractor.h"

#include <actions/WidgetAction.h>
#include <actions/OptionAction.h>

#include <PointData/PointData.h>

#include <QWidget>

using namespace hdps::gui;

class SettingsAction;

/**
 * Algorithm action class
 *
 * Action class for choosing and configuring extractor settings
 *
 * @author Thomas Kroes
 */
class AlgorithmAction : public WidgetAction
{
    Q_OBJECT

public:

    /** Widget class for algorithm action */
    class Widget : public QWidget
    {
    protected:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param algorithmAction Pointer to algorithm action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, AlgorithmAction* algorithmAction, const std::int32_t& widgetFlags);

    protected:

        friend class AlgorithmAction;
    };

protected:

    /**
     * Get widget representation of the algorithm action
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
     * @param settingsAction Reference to settings action
     */
    AlgorithmAction(SettingsAction& settingsAction);

    /** Extract the clusters from the input points */
    void extractClusters();

    /**
     * Get current extractor
     * @return Shared pointer to current extractor
     */
    SharedExtractor getExtractor();

    /** Initializes the algorithm action */
    void init();

signals:

    /**
     * Signals that the current extractor changed
     * @param extractor Pointer to extractor
     */
    void extractorChanged(Extractor* extractor);

public: // Action getters

    SettingsAction& getSettingsAction() { return _settingsAction; };
    OptionAction& getCurrentAction() { return _currentAction; };

protected:
    SettingsAction&     _settingsAction;    /** Reference to settings action */
    SharedExtractor     _extractor;         /** Shared pointer to extractor */
    OptionAction        _currentAction;     /** Current algorithm action */
};
