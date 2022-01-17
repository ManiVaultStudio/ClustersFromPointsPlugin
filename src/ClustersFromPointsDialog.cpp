/*
#include "ExtractMetaDataDialog.h"
#include "ExtractMetaDataPlugin.h"

#include <Application.h>

#include <QDialogButtonBox>

ExtractMetaDataDialog::ExtractMetaDataDialog(QWidget* parent, const Dataset<Points>& input) :
    QDialog(parent),
    _extractorAction(this, input)
{
    setWindowTitle("Extract meta data from " + input->getGuiName());
    setWindowIcon(Application::getIconFont("FontAwesome").getIcon("random"));
    setModal(true);

    auto layout = new QVBoxLayout();

    // Create widget for extractor action
    auto groupWidget = _extractorAction.createWidget(this);

    // Configure group widget
    groupWidget->layout()->setMargin(0);
    groupWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding));

    // Add to the layout
    layout->addWidget(groupWidget);

    // Make left column fit to content
    dynamic_cast<QGridLayout*>(groupWidget->layout())->setColumnStretch(0, 0);

    // Apply layout
    setLayout(layout);

    // Create dialog button box so that the user can proceed or cancel with the conversion
    auto dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    // Set button titles
    dialogButtonBox->button(QDialogButtonBox::Ok)->setText("Extract");
    dialogButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");

    // Add buttons to the layout
    layout->addWidget(dialogButtonBox);

    // Extract when accepted
    connect(dialogButtonBox, &QDialogButtonBox::accepted, this, [this]() {

        // Create output dataset
        auto outputDataset = Application::core()->addDataset<Clusters>("Cluster", _extractorAction.getOutputDatasetNameAction().getString(), _extractorAction.getInputDataset());

        // Copy clusters from clusters model to output clusters dataset
        outputDataset->getClusters() = _extractorAction.getClustersAction().getClustersModel().getClusters();

        // Notify others that the clusters changed
        Application::core()->notifyDataChanged(outputDataset);

        // Close the dialog
        accept();
    });

    // Close when rejected
    connect(dialogButtonBox, &QDialogButtonBox::rejected, this, &ExtractMetaDataDialog::reject);

    // Update the read only status of the extract button
    const auto updateExtractButtonReadOnly = [this, dialogButtonBox]() -> void {
        dialogButtonBox->button(QDialogButtonBox::Ok)->setEnabled(_extractorAction.canExtract());
    };

    // Update the read only status of the extract button when the number of clusters or the output dataset name changes
    connect(&_extractorAction.getClustersAction().getClustersModel(), &QAbstractItemModel::layoutChanged, this, updateExtractButtonReadOnly);
    connect(&_extractorAction.getOutputDatasetNameAction(), &StringAction::stringChanged, this, updateExtractButtonReadOnly);

    // Perform initial update
    updateExtractButtonReadOnly();
}
*/
