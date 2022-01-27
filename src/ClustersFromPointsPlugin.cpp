#include "ClustersFromPointsPlugin.h"

#include <PointData.h>

using namespace hdps;

Q_PLUGIN_METADATA(IID "nl.biovault.ClustersFromPointsPlugin")

const QMap<ClustersFromPointsPlugin::Algorithm, QString> ClustersFromPointsPlugin::algorithmNames = QMap<ClustersFromPointsPlugin::Algorithm, QString>({
    { ClustersFromPointsPlugin::Identifier, "Rounded numerical value" },
    { ClustersFromPointsPlugin::Index, "Point index" },
    { ClustersFromPointsPlugin::Stratification, "Regular intervals" },
    { ClustersFromPointsPlugin::Interval, "Interval" }
});

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

    // Initialize the algorithm and clusters action
    _settingsAction.getAlgorithmAction().init();
    _settingsAction.getClustersAction().setClustersDataset(getOutputDataset());
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
