#pragma once

#include "ClustersAction.h"
#include "AlgorithmAction.h"

#include <actions/GroupAction.h>
#include <actions/StringAction.h>
#include <actions/ToggleAction.h>

#include <PointsDimensionPickerAction.h>
#include <ClusterData.h>

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
    Q_OBJECT

public:

    /**
     * Constructor
     * @param parent Pointer to parent object
     * @param input Smart pointer to input points
     */
    ExtractorAction(QObject* parent, const Dataset<Points>& input);

signals:

    /**
     * Signals that the clusters changed
     * @param clusters Clusters
     */
    void clustersChanged(const std::vector<Cluster>& clusters);

protected:
    Dataset<Points>                 _input;                     /** Smart pointer to input points */
    StringAction                    _inputNameAction;           /** Input dataset name action */
    StringAction                    _outputNameAction;          /** Output dataset name action */
    ToggleAction                    _existingDatasetAction;     /** Existing dataset action */
    PointsDimensionPickerAction     _dimensionAction;           /** Current dimension action */
    DatasetPickerAction             _targetDatasetAction;       /** Target dataset action */
    AlgorithmAction                 _algorithmAction;           /** Algorithm action */
    ClustersAction                  _clustersAction;            /** Clusters action */
};
