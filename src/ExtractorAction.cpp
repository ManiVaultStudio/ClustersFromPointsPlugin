#include "ExtractorAction.h"
#include "ExtractMetaDataPlugin.h"

#include <ClusterData.h>

using namespace hdps;

ExtractorAction::ExtractorAction(QObject* parent, Dataset<Points> pointsDataset) :
    GroupAction(parent),
    _inputDataset(pointsDataset),
    _inputDatasetNameAction(this, "Input dataset name"),
    _outputDatasetNameAction(this, "Output dataset name"),
    _dimensionAction(this, "Dimension"),
    _algorithmAction(*this, _inputDataset),
    _clustersAction(this, Dataset<Clusters>(), pointsDataset),
    _numberOfClustersAction(this, "Number of clusters", 0, 1000000)
{
    // Exit if no dataset is present
    if (!_inputDataset.isValid())
        return;

    _inputDatasetNameAction.setMayReset(false);
    _outputDatasetNameAction.setMayReset(false);
    _algorithmAction.setMayReset(false);
    _clustersAction.setMayReset(false);
    _numberOfClustersAction.setMayReset(false);

    // Configure input name action
    _inputDatasetNameAction.setString(_inputDataset->getGuiName());
    _inputDatasetNameAction.setEnabled(false);

    // Add informative place holder string
    _outputDatasetNameAction.setPlaceHolderString("Enter name of the target dataset here...");

    // Set widget layout for clusters action
    _clustersAction.setDefaultWidgetFlags(ClustersAction::Filter | ClustersAction::Select | ClustersAction::Remove | ClustersAction::Merge | ClustersAction::Colorize | ClustersAction::Prefix);

    // Disable number of clusters action and set widget type to line edit
    _numberOfClustersAction.setEnabled(false);
    _numberOfClustersAction.setDefaultWidgetFlags(IntegralAction::LineEdit);

    // Update dimensions action with dimension from the input
    _dimensionAction.setPointsDataset(_inputDataset);

    // Request extraction when the current dimension changes
    connect(&_dimensionAction, &PointsDimensionPickerAction::currentDimensionIndexChanged, this, [this](const std::int32_t& currentDimensionIndex) {
        _algorithmAction.getExtractor()->setDimensionIndex(currentDimensionIndex);
    });

    // Update the clusters model when the algorithm produces new clusters
    connect(&_algorithmAction, &AlgorithmAction::clustersChanged, this, [this](const QVector<Cluster>& clusters) {

        // Set the clusters in the clusters model
        _clustersAction.getClustersModel().setClusters(clusters);

        // Colorize the clusters
        _clustersAction.getColorizeClustersAction().getColorizeAction().trigger();
    });

    // Update the read only status of actions when the clusters model layout changes
    connect(&getClustersAction().getClustersModel(), &QAbstractItemModel::layoutChanged, this, [this]() {
        _numberOfClustersAction.setValue(_clustersAction.getClustersModel().rowCount());
    });
}

Dataset<Points> ExtractorAction::getInputDataset()
{
    return _inputDataset;
}

bool ExtractorAction::canExtract()
{
    return _clustersAction.getClustersModel().rowCount() >= 1 && !_outputDatasetNameAction.getString().isEmpty();
}
