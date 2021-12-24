#include "ExtractMetaDataPlugin.h"
#include "ExtractMetaDataDialog.h"

#include <PointData.h>

Q_PLUGIN_METADATA(IID "nl.biovault.ExtractMetaDataPlugin")

using namespace hdps;
using namespace hdps::util;

ExtractMetaDataPlugin::ExtractMetaDataPlugin(const PluginFactory* factory) :
    TransformationPlugin(factory)
{
}

void ExtractMetaDataPlugin::init()
{
}

void ExtractMetaDataPlugin::transform(const Datasets& datasets)
{
    // Loop over all datasets and run the extraction dialog for each dataset
    for (auto dataset : datasets) {

        // Create dialog
        ExtractMetaDataDialog extractMetaDataDialog(nullptr, dataset);

        // And show it
        extractMetaDataDialog.exec();
    }
}

QIcon ExtractMetaDataPluginFactory::getIcon() const
{
    return Application::getIconFont("FontAwesome").getIcon("braille");
}

TransformationPlugin* ExtractMetaDataPluginFactory::produce()
{
    return new ExtractMetaDataPlugin(this);
}

hdps::DataTypes ExtractMetaDataPluginFactory::supportedDataTypes() const
{
    return DataTypes({ PointType });
}
