#include "SettingsAction.h"
#include "ClustersFromPointsPlugin.h"

#include <ClusterData.h>

using namespace hdps;

SettingsAction::SettingsAction(ClustersFromPointsPlugin* clustersFromPointsPlugin) :
    GroupAction(nullptr, true),
    _clustersFromPointsPlugin(clustersFromPointsPlugin),
    _dimensionAction(this, "Dimension"),
    _clustersAction(this),
    _algorithmAction(*this),
    _numberOfClustersAction(this, "Number of clusters", 0, 1000000)
{
    setText("Clusters from points");

    _algorithmAction.setMayReset(false);
    _clustersAction.setMayReset(false);
    _numberOfClustersAction.setMayReset(false);

    // Sort actions
    _dimensionAction.setSortIndex(0);
    _algorithmAction.setSortIndex(1);
    _clustersAction.setSortIndex(2);
    _numberOfClustersAction.setSortIndex(3);

    // Set widget layout for clusters action
    _clustersAction.setDefaultWidgetFlags(ClustersAction::Filter | ClustersAction::Select | ClustersAction::Remove | ClustersAction::Merge | ClustersAction::Colorize | ClustersAction::Prefix);

    // Disable number of clusters action and set widget type to line edit
    _numberOfClustersAction.setEnabled(false);
    _numberOfClustersAction.setDefaultWidgetFlags(IntegralAction::LineEdit);

    // Request extraction when the current dimension changes
    connect(&_dimensionAction, &PointsDimensionPickerAction::currentDimensionIndexChanged, this, [this](const std::int32_t& currentDimensionIndex) {
        _algorithmAction.getExtractor()->setDimensionIndex(currentDimensionIndex);
    });

    // Update the read only status of actions when the clusters model layout changes
    connect(&getClustersAction().getClustersModel(), &QAbstractItemModel::layoutChanged, this, [this]() {
        _numberOfClustersAction.setValue(_clustersAction.getClustersModel().rowCount());
    });
}

Dataset<Points> SettingsAction::getInputDataset()
{
    return _clustersFromPointsPlugin->getInputDataset();
}

Dataset<Clusters> SettingsAction::getClustersDataset()
{
    return _clustersFromPointsPlugin->getOutputDataset();
}