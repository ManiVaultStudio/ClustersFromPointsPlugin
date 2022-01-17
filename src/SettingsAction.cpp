#include "SettingsAction.h"
#include "ClustersFromPointsPlugin.h"

#include <ClusterData.h>

using namespace hdps;

SettingsAction::SettingsAction(ClustersFromPointsPlugin* clustersFromPointsPlugin) :
    GroupAction(nullptr, true),
    _clustersFromPointsPlugin(clustersFromPointsPlugin),
    _dimensionAction(this, "Dimension"),
    _algorithmAction(*this),
    _clustersAction(this, clustersFromPointsPlugin->getInputDataset()),
    _numberOfClustersAction(this, "Number of clusters", 0, 1000000)
{
    setText("Clusters from points");

    _algorithmAction.setMayReset(false);
    _clustersAction.setMayReset(false);
    _numberOfClustersAction.setMayReset(false);

    // Set widget layout for clusters action
    _clustersAction.setDefaultWidgetFlags(ClustersAction::Filter | ClustersAction::Select | ClustersAction::Remove | ClustersAction::Merge | ClustersAction::Colorize | ClustersAction::Prefix);

    // Disable number of clusters action and set widget type to line edit
    _numberOfClustersAction.setEnabled(false);
    _numberOfClustersAction.setDefaultWidgetFlags(IntegralAction::LineEdit);

    /*
    // Request extraction when the current dimension changes
    connect(&_dimensionAction, &PointsDimensionPickerAction::currentDimensionIndexChanged, this, [this](const std::int32_t& currentDimensionIndex) {
        _algorithmAction.getExtractor()->setDimensionIndex(currentDimensionIndex);
    });

    // Update the clusters model when the algorithm produces new clusters
    connect(&_algorithmAction, &AlgorithmAction::clustersChanged, this, [this](const QVector<Cluster>& clusters) {

        // Set the clusters in the clusters model
        _clustersAction.getClustersModel().setClusters(clusters);

        // Colorize the clusters
        _clustersAction.getColorizeClustersAction().getColorizeAction().trigger();
    });

    // Update the read only status of actions when the clusters model layout changes
    connect(&getClustersAction().getClustersModel(), &QAbstractItemModel::layoutChanged, this, [this]() {
        _numberOfClustersAction.setValue(_clustersAction.getClustersModel().rowCount());
    });
    */
}

Dataset<Points> SettingsAction::getInputDataset()
{
    return _clustersFromPointsPlugin->getInputDataset();
}
