#pragma once

#include "Extractor.h"

#include <actions/WidgetAction.h>
#include <actions/OptionAction.h>

#include <PointData.h>

#include <QWidget>

using namespace hdps::gui;

class ExtractorAction;

/**
 * Algorithm action class
 *
 * Action class for choosing and configuring an extractor
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
     * @param extractorAction Reference to extractor action
     * @param input Smart pointer to input points
     */
    AlgorithmAction(ExtractorAction& extractorAction, const hdps::Dataset<Points>& input);

    /** Determines whether the action can be reset */
    bool isResettable() const override;

    /** Reset to default */
    void reset() override;

    /** Extract the clusters from the input points */
    void extractClusters();

    /**
     * Get current extractor
     * @return Shared pointer to current extractor
     */
    SharedExtractor getExtractor();

public: // Action getters

    ExtractorAction& getExtractorAction() { return _extractorAction; };
    OptionAction& getCurrentAction() { return _currentAction; };

signals:

    /**
     * Signals that the clusters changed
     * @param clusters Clusters
     */
    void clustersChanged(const QVector<Cluster>& clusters);

protected:
    ExtractorAction&        _extractorAction;   /** Reference to extractor action */
    hdps::Dataset<Points>   _input;             /** Smart pointer to input points */
    SharedExtractor         _extractor;         /** Shared pointer to extractor */
    OptionAction            _currentAction;     /** Current algorithm action */
};
