#include "ClustersFromPointsPlugin.h"

#include "Extractor.h"

#include <actions/PluginTriggerAction.h>
#include <PointData/PointData.h>

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

QIcon ClustersFromPointsPluginFactory::getIcon(const QColor& color /*= Qt::black*/) const
{
    return Application::getIconFont("FontAwesome").getIcon("braille", color);
}

AnalysisPlugin* ClustersFromPointsPluginFactory::produce()
{
    return new ClustersFromPointsPlugin(this);
}

mv::DataTypes ClustersFromPointsPluginFactory::supportedDataTypes() const
{
    return DataTypes({ PointType });
}

mv::gui::PluginTriggerActions ClustersFromPointsPluginFactory::getPluginTriggerActions(const mv::Datasets& datasets) const
{
    PluginTriggerActions pluginTriggerActions;

    const auto getPluginInstance = [this](const Dataset<Points>& dataset) -> ClustersFromPointsPlugin* {
        return dynamic_cast<ClustersFromPointsPlugin*>(plugins().requestPlugin(getKind(), { dataset }));
    };

    const auto numberOfDatasets = datasets.count();

    if (PluginFactory::areAllDatasetsOfTheSameType(datasets, PointType)) {
        if (numberOfDatasets >= 1) {
            auto pluginTriggerAction = new PluginTriggerAction(const_cast<ClustersFromPointsPluginFactory*>(this), this, "Extract clusters", "Extract clusters from points", getIcon(), [this, getPluginInstance, datasets](PluginTriggerAction& pluginTriggerAction) -> void {
                for (auto dataset : datasets)
                    getPluginInstance(dataset);

        });

            pluginTriggerActions << pluginTriggerAction;
        }
    }

    return pluginTriggerActions;
}
