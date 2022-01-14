#pragma once

#include <TransformationPlugin.h>

using namespace hdps::plugin;
using namespace hdps::util;

/**
 * TODO
 *
 * @author Thomas Kroes
 */
class ExtractMetaDataPlugin : public TransformationPlugin
{
public:

    /** Data points are grouped into clusters based on */
    enum Algorithm {
        Identifier,     /** ...their numerical (integral) value */
        RegularIntervals       /** ...in which histogram bin they belong */
    };

public:

    /**
     * Constructors
     * @param factory Pointer to factory
     */
    ExtractMetaDataPlugin(const PluginFactory* factory);

    /** Destructor */
    ~ExtractMetaDataPlugin() override = default;

    /** Initializes the plugin */
    void init() override;

    /**
     * The method which handles the data transformation
     * @param datasets Input datasets
     */
    void transform(const hdps::Datasets& datasets);

protected:

};

class ExtractMetaDataPluginFactory : public TransformationPluginFactory
{
    Q_INTERFACES(hdps::plugin::TransformationPluginFactory hdps::plugin::PluginFactory)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "nl.biovault.ExtractMetaDataPlugin" FILE "ExtractMetaDataPlugin.json")

public:

    /** Default constructor */
    ExtractMetaDataPluginFactory() = default;

    /** Destructor */
    ~ExtractMetaDataPluginFactory() = default;

    /** Returns the plugin icon */
    QIcon getIcon() const override;

    /** Produces an instance of a transformation plugin */
    TransformationPlugin* produce() override;

    hdps::DataTypes supportedDataTypes() const override;
};
