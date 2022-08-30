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
        Index,              /** ...their point index */
        Stratification,     /** ...in which stratum they belong */
        Interval            /** ...in which user specified interval(s) they belong */
    };

    /** Maps algorithm enum to name string */
    static const QMap<Algorithm, QString> algorithmNames;

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

    /**
     * Get plugin icon
     * @param color Icon color for flat (font) icons
     * @return Icon
     */
    QIcon getIcon(const QColor& color = Qt::black) const override;

    /**
     * Produces the plugin
     * @return Pointer to the produced plugin
     */
    AnalysisPlugin* produce() override;

    /**
     * Get the data types that the plugin supports
     * @return Supported data types
     */
    hdps::DataTypes supportedDataTypes() const override;

    /**
     * Get plugin trigger actions given \p datasets
     * @param datasets Vector of input datasets
     * @return Vector of plugin trigger actions
     */
    PluginTriggerActions getPluginTriggerActions(const hdps::Datasets& datasets) const override;
};
