#include "ExtractMetaDataDialog.h"
#include "Application.h"

#include <ClusterData.h>

#include <QMenu>
#include <QDialogButtonBox>

namespace hdps {

using namespace gui;

ExtractMetaDataDialog::ExtractMetaDataDialog(QWidget* parent, const Dataset<DatasetImpl>& sourceDataset) :
    QDialog(parent),
    _dataset(sourceDataset),
    _groupAction(this),
    _sourceDatasetNameAction(this, "Source dataset"),
    _targetDatasetNameAction(this, "Target dataset"),
    _existingDatasetAction(this, "Existing dataset"),
    _targetDatasetAction(this, "Target dataset"),
    _groupByAction(this, "Group by", { "Identifier" }, "Identifier", "Identifier"),
    _clustersAction(this)
{
    // Exit if no dataset is present
    if (!_dataset.isValid())
        return;

    setWindowTitle("Extract meta data from " + _dataset->getGuiName());
    setWindowIcon(Application::getIconFont("FontAwesome").getIcon("random"));
    setModal(true);

    _sourceDatasetNameAction.setMayReset(false);
    _targetDatasetNameAction.setMayReset(false);
    _existingDatasetAction.setMayReset(false);
    _targetDatasetAction.setMayReset(false);
    _groupByAction.setMayReset(false);
    _clustersAction.setMayReset(false);

    _sourceDatasetNameAction.setString(sourceDataset->getGuiName());
    _sourceDatasetNameAction.setEnabled(false);

    // Add informative place holder string
    _targetDatasetNameAction.setPlaceHolderString("Enter name of the target dataset here...");

    // Currently, only group by identifier is supported
    _groupByAction.setEnabled(false);

    _groupAction << _sourceDatasetNameAction;
    _groupAction << _targetDatasetNameAction;
    _groupAction << _existingDatasetAction;
    _groupAction << _targetDatasetAction;
    _groupAction << _groupByAction;
    _groupAction << _clustersAction;

    auto layout = new QVBoxLayout();

    auto groupWidget = _groupAction.createWidget(this);

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

    // Invoked when the existing dataset action is toggled
    const auto existingDatasetChanged = [this]() -> void {

        // Establish whether to use existing dataset or not
        const auto useExisting = _existingDatasetAction.isChecked();

        // Disable target dataset name action when existing dataset action is not checked
        _targetDatasetNameAction.setEnabled(!useExisting);

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
        dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(!_targetDatasetNameAction.getString().isEmpty());
    };

    // Update target dataset name and target dataset action when the existing dataset action is toggled
    connect(&_targetDatasetNameAction, &StringAction::stringChanged, this, targetDatasetNameChanged);

    // Initial update
    targetDatasetNameChanged();

    // Only enable the existing dataset action when there are one or more cluster datasets in the data hierarchy
    _existingDatasetAction.setEnabled(!Application::core()->requestAllDataSets(QVector<hdps::DataType>({ ClusterType })).isEmpty());
}

}
