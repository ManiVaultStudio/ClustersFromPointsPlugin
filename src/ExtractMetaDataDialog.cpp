#include "ExtractMetaDataDialog.h"
#include "ExtractMetaDataPlugin.h"
#include "Application.h"

#include <QDialogButtonBox>

ExtractMetaDataDialog::ExtractMetaDataDialog(QWidget* parent, const Dataset<Points>& input) :
    QDialog(parent),
    _extractorAction(this, input)
{
    setWindowTitle("Extract meta data from " + input->getGuiName());
    setWindowIcon(Application::getIconFont("FontAwesome").getIcon("random"));
    setModal(true);

    auto layout = new QVBoxLayout();

    auto groupWidget = _extractorAction.createWidget(this);

    // Configure group widget
    groupWidget->layout()->setMargin(0);
    groupWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding));

    // Add to the layout
    layout->addWidget(groupWidget);

    setLayout(layout);

    // Create dialog button box so that the user can proceed or cancel with the conversion
    auto dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    dialogButtonBox->button(QDialogButtonBox::Ok)->setText("Extract");
    dialogButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");

    // Add buttons to the layout
    layout->addWidget(dialogButtonBox);

    // Handle when accepted
    connect(dialogButtonBox, &QDialogButtonBox::accepted, this, [this]() {
    });

    // Handle when rejected
    connect(dialogButtonBox, &QDialogButtonBox::rejected, this, &ExtractMetaDataDialog::reject);
    /*
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
    

    // Invoked when the target dataset name changed
    const auto targetDatasetNameChanged = [this, dialogButtonBox]() -> void {
        dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(!_outputNameAction.getString().isEmpty());
    };

    // Update target dataset name and target dataset action when the existing dataset action is toggled
    connect(&_outputNameAction, &StringAction::stringChanged, this, targetDatasetNameChanged);

    // Initial update
    targetDatasetNameChanged();

    // Only enable the existing dataset action when there are one or more cluster datasets in the data hierarchy
    _existingDatasetAction.setEnabled(!Application::core()->requestAllDataSets(QVector<hdps::DataType>({ ClusterType })).isEmpty());

    // Update dimensions action with dimension from the input
    _dimensionAction.setPointsDataset(_input);
    */
}
