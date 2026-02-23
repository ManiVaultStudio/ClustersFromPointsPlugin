#include "SettingsAction.h"
#include "ClustersFromPointsPlugin.h"

#include <ClusterData/ClusterData.h>

using namespace mv;

SettingsAction::SettingsAction(ClustersFromPointsPlugin* clustersFromPointsPlugin) :
    GroupAction(nullptr, "ClustersFromPointsSettings", true),
    _clustersFromPointsPlugin(clustersFromPointsPlugin),
    _clustersAction(this),
    _externalDatasetAction(this, "External dataset"),
    _dimensionAction(this, "Dimension"),
    _algorithmAction(*this),
    _startAction(this, "Start")
{
    setText("Clusters from points");

    _clustersAction.setVisible(false);

    // Sort actions
    _algorithmAction.setSortIndex(1);
    _clustersAction.setSortIndex(2);

    // Set widget layout for clusters action
    _clustersAction.setDefaultWidgetFlags(ClustersAction::Filter | ClustersAction::Select | ClustersAction::Remove | ClustersAction::Merge | ClustersAction::Subset | ClustersAction::Colorize | ClustersAction::Prefix);

    _externalDatasetAction.setDefaultWidgetFlag(DatasetPickerAction::WidgetFlag::Clearable);

    // Add actions to layout
    addAction(&_clustersAction);
    addAction(&_externalDatasetAction);
    addAction(&_dimensionAction);
	addAction(&_algorithmAction);
    addAction(&_startAction);
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
