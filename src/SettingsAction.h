#pragma once

#include "AlgorithmAction.h"

#include <actions/GroupAction.h>
#include <actions/StringAction.h>
#include <actions/ToggleAction.h>
#include <actions/IntegralAction.h>

#include <PointsDimensionPickerAction.h>
#include <ClusterData.h>
#include <ClustersAction.h>

using namespace hdps::util;

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

public: // Action getters

    PointsDimensionPickerAction& getDimensionAction() { return _dimensionAction; }
    AlgorithmAction& getAlgorithmAction() { return _algorithmAction; }
    ClustersAction& getClustersAction() { return _clustersAction; }
    IntegralAction& getNumberOfClustersAction() { return _numberOfClustersAction; }

protected:
    ClustersFromPointsPlugin*       _clustersFromPointsPlugin;      /** Pointer to the clusters from points plugin */
    PointsDimensionPickerAction     _dimensionAction;               /** Current dimension action */
    ClustersAction                  _clustersAction;                /** Clusters action */
    AlgorithmAction                 _algorithmAction;               /** Algorithm action */
    IntegralAction                  _numberOfClustersAction;        /** Number of clusters action */
};
