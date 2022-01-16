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

/**
 * Extractor action class
 *
 * Action class for extractor configuration
 *
 * @author Thomas Kroes
 */
class ExtractorAction : public GroupAction
{
public:

    /**
     * Constructor
     * @param parent Pointer to parent object
     * @param pointsDataset Smart pointer to points dataset
     */
    ExtractorAction(QObject* parent, Dataset<Points> pointsDataset);

    /**
     * Get smart pointer to input points dataset
     * @return Smart pointer to input points dataset
     */
    Dataset<Points> getInputDataset();

    /**
     * Get whether clusters can be extracted
     * @return Whether clusters can be extracted
     */
    bool canExtract();

public: // Action getters

    StringAction& getInputDatasetNameAction() { return _inputDatasetNameAction; }
    StringAction& getOutputDatasetNameAction() { return _outputDatasetNameAction; }
    PointsDimensionPickerAction& getDimensionAction() { return _dimensionAction; }
    AlgorithmAction& getAlgorithmAction() { return _algorithmAction; }
    ClustersAction& getClustersAction() { return _clustersAction; }
    IntegralAction& getNumberOfClustersAction() { return _numberOfClustersAction; }

protected:
    Dataset<Points>                 _inputDataset;              /** Smart pointer to points dataset */
    StringAction                    _inputDatasetNameAction;    /** Input dataset name action */
    StringAction                    _outputDatasetNameAction;   /** Output dataset name action */
    PointsDimensionPickerAction     _dimensionAction;           /** Current dimension action */
    AlgorithmAction                 _algorithmAction;           /** Algorithm action */
    ClustersAction                  _clustersAction;            /** Clusters action */
    IntegralAction                  _numberOfClustersAction;    /** Number of clusters action */

    friend class ExtractMetaDataDialog;
};
