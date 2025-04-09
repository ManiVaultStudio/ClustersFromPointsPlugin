#include "ClustersFromPointsPlugin.h"

#include "Extractor.h"

#include <actions/PluginTriggerAction.h>
#include <ClusterData/ClusterData.h>
#include <PointData/PointData.h>

#include <algorithm>

using namespace mv;

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
    setOutputDataset(mv::data().createDataset("Cluster", "Clusters", getInputDataset()));

    // Add the settings action to the output clusters dataset
    getOutputDataset()->addAction(_settingsAction);

    // Select the dataset in the data hierarchy
    getOutputDataset()->getDataHierarchyItem().select();

    // Initialize the algorithm and clusters action
    _settingsAction.getAlgorithmAction().init();
    _settingsAction.getClustersAction().setClustersDataset(getOutputDataset());

    connect(&_settingsAction.getStartAction(), &TriggerAction::triggered, this, [this]() {
        if (_settingsAction.getAlgorithmAction().getExtractor().isNull())
            return;

        _settingsAction.getAlgorithmAction().getExtractor()->requestExtraction();
        });
}

ClustersFromPointsPluginFactory::ClustersFromPointsPluginFactory()
{
    setIconByName("braille");
}

AnalysisPlugin* ClustersFromPointsPluginFactory::produce()
{
    return new ClustersFromPointsPlugin(this);
}

mv::DataTypes ClustersFromPointsPluginFactory::supportedDataTypes() const
{
    return DataTypes({ PointType, ClusterType });
}

mv::gui::PluginTriggerActions ClustersFromPointsPluginFactory::getPluginTriggerActions(const mv::Datasets& datasets) const
{
    PluginTriggerActions pluginTriggerActions;

    const auto numberOfDatasets = datasets.count();

    if (numberOfDatasets < 1) {
        return pluginTriggerActions;
    }

    if (PluginFactory::areAllDatasetsOfTheSameType(datasets, PointType)) {

        const auto getPluginInstance = [this](const Dataset<Points>& dataset) -> ClustersFromPointsPlugin* {
            return dynamic_cast<ClustersFromPointsPlugin*>(plugins().requestPlugin(getKind(), { dataset }));
            };

        auto pluginTriggerAction = new PluginTriggerAction(const_cast<ClustersFromPointsPluginFactory*>(this), this, "Extract clusters", "Extract clusters from points", icon(), [this, getPluginInstance, datasets](PluginTriggerAction& pluginTriggerAction) -> void {
            for (const auto& dataset : datasets) {
                getPluginInstance(dataset);
            }
            });

        pluginTriggerActions << pluginTriggerAction;

    } // PointType

    if (PluginFactory::areAllDatasetsOfTheSameType(datasets, ClusterType)) {

        const bool allHaveClustersFromPoints = std::all_of(datasets.begin(), datasets.end(), [](const Dataset<DatasetImpl>& dataset) -> bool {
            return dataset->findChildByPath("Clusters from points");
            });

        if (allHaveClustersFromPoints) {
            auto pluginTriggerAction = new PluginTriggerAction(const_cast<ClustersFromPointsPluginFactory*>(this), this, "Start clustering...", "Start clustering if dataset has Extract Clusters Analysis", icon(), [this, datasets](PluginTriggerAction& pluginTriggerAction) -> void {
                for (const auto& dataset : datasets) {
                    auto startAction = dataset->findChildByPath("Clusters from points/Start");
                    if (!startAction)
                        continue;
                    TriggerAction* startTriggerAction = dynamic_cast<TriggerAction*>(startAction);
                    if (!startTriggerAction)
                        continue;
                    startTriggerAction->trigger();
                }
                });

            pluginTriggerActions << pluginTriggerAction;
        }

    } // ClusterType

    return pluginTriggerActions;
}
