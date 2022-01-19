#pragma once

#include "SettingsAction.h"

#include <AnalysisPlugin.h>

using namespace hdps::plugin;

/**
 * Extract clusters from points plugin class
 *
 * Data analysis plugin class for extracting clusters from points
 *
 * @author Thomas Kroes
 */
class ClustersFromPointsPlugin : public AnalysisPlugin
{
public:

    /** Data points are grouped into clusters based on */
    enum Algorithm {
        Identifier,         /** ...their numerical (integral) value */
        Stratification,     /** ...in which stratum they belong */
        Interval            /** ...in which user specified interval(s) they belong */
    };

public:

    /**
     * Constructors
     * @param factory Pointer to plugin factory
     */
    ClustersFromPointsPlugin(const PluginFactory* factory);

    /** Destructor */
    ~ClustersFromPointsPlugin() override = default;

    /** Initializes the plugin */
    void init() override;

protected:
    SettingsAction     _settingsAction;        /** Settings action */
};

class ClustersFromPointsPluginFactory : public AnalysisPluginFactory
{
    Q_INTERFACES(hdps::plugin::AnalysisPluginFactory hdps::plugin::PluginFactory)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "nl.biovault.ClustersFromPointsPlugin" FILE "ClustersFromPointsPlugin.json")

public:

    /** Default constructor */
    ClustersFromPointsPluginFactory() = default;

    /** Destructor */
    ~ClustersFromPointsPluginFactory() = default;

    /** Returns the plugin icon */
    QIcon getIcon() const override;

    /** Produces an instance of a transformation plugin */
    AnalysisPlugin* produce() override;

    hdps::DataTypes supportedDataTypes() const override;
};
