#include "ExtractMetaDataPlugin.h"

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
    for (auto dataset : datasets)
        qDebug() << "Transform" << dataset->getGuiName();
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
