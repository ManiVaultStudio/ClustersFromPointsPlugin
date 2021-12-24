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
    _groupByAction(this, "Group by", { "Identifier" }, "Identifier", "Identifier")
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

    _sourceDatasetNameAction.setString(sourceDataset->getGuiName());
    _sourceDatasetNameAction.setEnabled(false);

    _targetDatasetNameAction.setPlaceHolderString("Enter name of the target dataset here...");

    _groupAction << _sourceDatasetNameAction;
    _groupAction << _targetDatasetNameAction;
    _groupAction << _existingDatasetAction;
    _groupAction << _targetDatasetAction;
    _groupAction << _groupByAction;

    auto layout = new QVBoxLayout();

    auto groupWidget = _groupAction.createWidget(this);

    groupWidget->layout()->setMargin(0);

    layout->addWidget(groupWidget);
    layout->addStretch(1);

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

    existingDatasetChanged();
}

}
