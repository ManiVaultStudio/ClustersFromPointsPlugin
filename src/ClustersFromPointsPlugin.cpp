#include "ClustersFromPointsPlugin.h"

#include <PointData.h>

using namespace hdps;

Q_PLUGIN_METADATA(IID "nl.biovault.ClustersFromPointsPlugin")

ClustersFromPointsPlugin::ClustersFromPointsPlugin(const PluginFactory* factory) :
    AnalysisPlugin(factory),
    _settingsAction(this)
{
}

void ClustersFromPointsPlugin::init()
{
    // Create output dataset and assign to analysis
    setOutputDataset(_core->addDataset("Cluster", "Clusters", getInputDataset()));

    // Add the settings action to the output clusters dataset
    getOutputDataset()->addAction(_settingsAction);

    // Update the dimension picker
    _settingsAction.getDimensionAction().setPointsDataset(getInputDataset<Points>());
}

QIcon ClustersFromPointsPluginFactory::getIcon() const
{
    return Application::getIconFont("FontAwesome").getIcon("braille");
}

AnalysisPlugin* ClustersFromPointsPluginFactory::produce()
{
    return new ClustersFromPointsPlugin(this);
}

hdps::DataTypes ClustersFromPointsPluginFactory::supportedDataTypes() const
{
    return DataTypes({ PointType });
}
