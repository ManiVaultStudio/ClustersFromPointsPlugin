#pragma once

#include <TransformationPlugin.h>

using namespace hdps::plugin;

/**
 * Extract meta data plugin class
 *
 * Data transformation plugin class for extracting meta data (clusters) from points
 *
 * @author Thomas Kroes
 */
class ExtractMetaDataPlugin : public TransformationPlugin
{
public:

    /** Data points are grouped into clusters based on */
    enum Algorithm {
        Identifier,         /** ...their numerical (integral) value */
        Stratification,      /** ...in which stratum they belong */
        Interval            /** ...in which interval(s) they belong */
    };

public:

    /**
     * Constructors
     * @param factory Pointer to plugin factory
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
