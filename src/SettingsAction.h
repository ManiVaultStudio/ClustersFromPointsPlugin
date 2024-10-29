#pragma once

#include "AlgorithmAction.h"

#include <actions/GroupAction.h>

#include <ClusterData/ClusterData.h>
#include <ClusterData/ClustersAction.h>
#include <actions/TriggerAction.h>

using namespace mv::util;

class ClustersFromPointsPlugin;

/**
 * Settings action class
 *
 * Primary action class for plugin settings
 *
 * @author Thomas Kroes
 */
class SettingsAction : public GroupAction
{
public:

    /**
     * Constructor
     * @param clustersFromPointsPlugin Pointer to the clusters from points plugin
     */
    SettingsAction(ClustersFromPointsPlugin* clustersFromPointsPlugin);

    /**
     * Get smart pointer to input points dataset
     * @return Smart pointer to input points dataset
     */
    Dataset<Points> getInputDataset();

    /**
     * Get smart pointer to clusters dataset
     * @return Smart pointer to clusters dataset
     */
    Dataset<Clusters> getClustersDataset();

    /**
     * Get clusters from points plugin
     * @return Reference to clusters from points plugin
     */
    ClustersFromPointsPlugin& getClustersFromPointsPlugin();

public: // Action getters

    AlgorithmAction& getAlgorithmAction() { return _algorithmAction; }
    ClustersAction& getClustersAction() { return _clustersAction; }
    TriggerAction& getStartAction() { return _startAction; }

protected:
    ClustersFromPointsPlugin*   _clustersFromPointsPlugin;      /** Pointer to the clusters from points plugin */
    ClustersAction              _clustersAction;                /** Clusters action */
    AlgorithmAction             _algorithmAction;               /** Algorithm action */
    TriggerAction               _startAction;                   /** Start action */
};
