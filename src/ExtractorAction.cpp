#include "ExtractorAction.h"
#include "ExtractMetaDataPlugin.h"

ExtractorAction::ExtractorAction(QObject* parent, const Dataset<Points>& input) :
    GroupAction(parent),
    _input(input),
    _outputNameAction(this, "Output"),
    _inputNameAction(this, "Input"),
    _existingDatasetAction(this, "Existing dataset"),
    _dimensionAction(this, "Dimension"),
    _targetDatasetAction(this, "Target dataset"),
    _algorithmAction(this, _input),
    _clustersAction(this)
{
    // Exit if no dataset is present
    if (!_input.isValid())
        return;

    _inputNameAction.setMayReset(false);
    _outputNameAction.setMayReset(false);
    _existingDatasetAction.setMayReset(false);
    _targetDatasetAction.setMayReset(false);
    _algorithmAction.setMayReset(false);
    _clustersAction.setMayReset(false);

    _inputNameAction.setString(_input->getGuiName());
    _inputNameAction.setEnabled(false);

    // Add informative place holder string
    _outputNameAction.setPlaceHolderString("Enter name of the target dataset here...");

    // Invoked when the existing dataset action is toggled
    const auto existingDatasetChanged = [this]() -> void {

        // Establish whether to use existing dataset or not
        const auto useExisting = _existingDatasetAction.isChecked();

        // Disable target dataset name action when existing dataset action is not checked
        _outputNameAction.setEnabled(!useExisting);

        // Enable target dataset action when existing dataset action is checked
        _targetDatasetAction.setEnabled(useExisting);

        // Update target dataset action datasets, depending on the whether to use an existing dataset
        _targetDatasetAction.setDatasets(useExisting ? Application::core()->requestAllDataSets(QVector<hdps::DataType>({ ClusterType })) : Datasets());
    };

    // Update target dataset name and target dataset action when the existing dataset action is toggled
    connect(&_existingDatasetAction, &ToggleAction::toggled, this, existingDatasetChanged);

    // Initial update
    existingDatasetChanged();

    // Only enable the existing dataset action when there are one or more cluster datasets in the data hierarchy
    _existingDatasetAction.setEnabled(!Application::core()->requestAllDataSets(QVector<hdps::DataType>({ ClusterType })).isEmpty());

    // Update dimensions action with dimension from the input
    _dimensionAction.setPointsDataset(_input);

    // Request extraction when the current dimension changes
    connect(&_dimensionAction, &PointsDimensionPickerAction::currentDimensionIndexChanged, this, [this]() {
        _algorithmAction.getExtractor()->requestExtraction();
    });
}
