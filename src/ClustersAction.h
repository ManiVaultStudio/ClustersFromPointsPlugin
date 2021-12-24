#pragma once

#include <actions/Actions.h>

#include "ClustersModel.h"
#include "ClustersFilterModel.h"

#include <QItemSelectionModel>

namespace hdps {
    class CoreInterface;
    class DataHierarchyItem;
}

class Cluster;
class Clusters;

using namespace hdps::gui;
using namespace hdps::util;

/**
 * Clusters action class
 *
 * Action class for display and interaction with clusters
 *
 * @author Thomas Kroes
 */
class ClustersAction : public WidgetAction
{
protected:

    /** Widget class for clusters action */
    class Widget : public WidgetActionWidget {
    public:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param clustersAction Pointer to clusters action
         */
        Widget(QWidget* parent, ClustersAction* clustersAction);

    protected:
        ClustersFilterModel     _filterModel;       /** Clusters filter model */
        QItemSelectionModel     _selectionModel;    /** Clusters selection model */
    };

    /**
     * Get widget representation of the color action
     * @param parent Pointer to parent widget
     * @param widgetFlags Widget flags for the configuration of the widget (type)
     */
    QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override {
        return new Widget(parent, this);
    };

public:

    /**
     * Constructor
     * @param parent Pointer to parent object
     */
    ClustersAction(QObject* parent);

    /** Get the clusters model */
    ClustersModel& getClustersModel();

protected:
    Dataset<Clusters>   _clusters;          /** Cluster dataset reference */
    ClustersModel       _clustersModel;     /** Clusters model */
};
