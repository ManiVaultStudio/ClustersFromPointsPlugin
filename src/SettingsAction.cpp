#include "SettingsAction.h"
#include "ClustersFromPointsPlugin.h"

#include <ClusterData.h>

using namespace hdps;

SettingsAction::SettingsAction(ClustersFromPointsPlugin* clustersFromPointsPlugin) :
    GroupAction(nullptr, "Settings", true),
    _clustersFromPointsPlugin(clustersFromPointsPlugin),
    _clustersAction(this),
    _algorithmAction(*this)
{
    setText("Clusters from points");

    _clustersAction.setVisible(false);

    addAction(&_algorithmAction);
    addAction(&_clustersAction);

    _clustersAction.setDefaultWidgetFlags(ClustersAction::Filter | ClustersAction::Select | ClustersAction::Remove | ClustersAction::Merge | ClustersAction::Subset | ClustersAction::Colorize | ClustersAction::Prefix);
}

Dataset<Points> SettingsAction::getInputDataset()
{
    return _clustersFromPointsPlugin->getInputDataset();
}

Dataset<Clusters> SettingsAction::getClustersDataset()
{
    return _clustersFromPointsPlugin->getOutputDataset();
}

ClustersFromPointsPlugin& SettingsAction::getClustersFromPointsPlugin()
{
    return *_clustersFromPointsPlugin;
}
