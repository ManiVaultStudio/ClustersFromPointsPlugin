#include "ClustersFromPointsPlugin.h"

#include <actions/PluginTriggerAction.h>

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

    // Select the dataset in the data hierarchy
    getOutputDataset()->getDataHierarchyItem().select();

    // Initialize the algorithm and clusters action
    _settingsAction.getAlgorithmAction().init();
    _settingsAction.getClustersAction().setClustersDataset(getOutputDataset());
}

QIcon ClustersFromPointsPluginFactory::getIcon(const QColor& color /*= Qt::black*/) const
{
    return Application::getIconFont("FontAwesome").getIcon("braille", color);
}

AnalysisPlugin* ClustersFromPointsPluginFactory::produce()
{
    return new ClustersFromPointsPlugin(this);
}

hdps::DataTypes ClustersFromPointsPluginFactory::supportedDataTypes() const
{
    return DataTypes({ PointType });
}

hdps::gui::PluginTriggerActions ClustersFromPointsPluginFactory::getPluginTriggerActions(const hdps::Datasets& datasets) const
{
    PluginTriggerActions pluginTriggerActions;

    const auto getPluginInstance = [this](const Dataset<Points>& dataset) -> ClustersFromPointsPlugin* {
        return dynamic_cast<ClustersFromPointsPlugin*>(Application::core()->requestPlugin(getKind(), { dataset }));
    };

    const auto numberOfDatasets = datasets.count();

    if (PluginFactory::areAllDatasetsOfTheSameType(datasets, PointType)) {
        if (numberOfDatasets >= 1) {
            auto pluginTriggerAction = createPluginTriggerAction("Extract clusters", "Extract clusters from points", datasets, "braille");

            connect(pluginTriggerAction, &QAction::triggered, [this, getPluginInstance, datasets]() -> void {
                for (auto dataset : datasets)
                    getPluginInstance(dataset);
            });

            pluginTriggerActions << pluginTriggerAction;
        }
    }

    return pluginTriggerActions;
}
