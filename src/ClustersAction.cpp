#include "ClustersAction.h"

#include <DataHierarchyItem.h>
#include <ClusterData.h>
#include <PointData.h>
#include <event/Event.h>

#include <QTreeView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
#include <QFile>
#include <QFileDialog>

using namespace hdps;
using namespace hdps::gui;

ClustersAction::ClustersAction(QObject* parent) :
    WidgetAction(parent),
    _clusters(),
    _clustersModel()
{
    setText("Meta data");
}

ClustersModel& ClustersAction::getClustersModel()
{
    return _clustersModel;
}

ClustersAction::Widget::Widget(QWidget* parent, ClustersAction* clustersAction) :
    WidgetActionWidget(parent, clustersAction),
    _filterModel(),
    _selectionModel(&_filterModel)
{
    auto clustersTreeView = new QTreeView();

    // Configure tree view
    clustersTreeView->setModel(&_filterModel);
    clustersTreeView->setSelectionModel(&_selectionModel);
    //clustersTreeView->setFixedHeight(300);
    clustersTreeView->setRootIsDecorated(false);
    clustersTreeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    clustersTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    clustersTreeView->setSortingEnabled(true);
    clustersTreeView->sortByColumn(static_cast<std::int32_t>(ClustersModel::Column::Name), Qt::SortOrder::AscendingOrder);
    clustersTreeView->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    /*
    // Configure header view
    auto header = clustersTreeView->header();

    header->setStretchLastSection(false);
    header->hideSection(static_cast<std::int32_t>(ClustersModel::Column::ID));

    header->setMinimumSectionSize(20);

    header->resizeSection(static_cast<std::int32_t>(ClustersModel::Column::Color), 20);
    header->resizeSection(static_cast<std::int32_t>(ClustersModel::Column::Name), 200);
    header->resizeSection(static_cast<std::int32_t>(ClustersModel::Column::NumberOfIndices), 100);

    header->setSectionResizeMode(static_cast<std::int32_t>(ClustersModel::Column::Color), QHeaderView::Fixed);
    header->setSectionResizeMode(static_cast<std::int32_t>(ClustersModel::Column::Name), QHeaderView::Stretch);
    header->setSectionResizeMode(static_cast<std::int32_t>(ClustersModel::Column::NumberOfIndices), QHeaderView::Fixed);
    */

    auto mainLayout = new QVBoxLayout();

    mainLayout->setMargin(0);
    mainLayout->addWidget(clustersTreeView);

    setLayout(mainLayout);

    /*
    const auto selectionChangedHandler = [this, clustersAction, clustersTreeView]() -> void {

        // Get selected row
        const auto selectedRows = clustersTreeView->selectionModel()->selectedRows();

        // Indices of the selected clusters
        std::vector<std::uint32_t> currentClusterSelectionIndices;

        // Clear and reserve the selection indices
        currentClusterSelectionIndices.reserve(clustersAction->getClusters()->size());

        // Gather point indices for selection
        for (auto selectedIndex : selectedRows) {
            auto cluster = static_cast<Cluster*>(_filterModel.mapToSource(selectedIndex).internalPointer());

            // Add selected index
            currentClusterSelectionIndices.push_back(selectedIndex.row());
        }

        // Select points
        clustersAction->getClustersDataset()->setSelectionIndices(currentClusterSelectionIndices);

        // Update state of the remove action
        _removeAction.setEnabled(!selectedRows.isEmpty());
        _mergeAction.setEnabled(selectedRows.count() >= 2);

        // Notify others that the cluster selection has changed
        Application::core()->notifyDataSelectionChanged(clustersAction->getClustersDataset());
    };

    connect(clustersTreeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this, selectionChangedHandler](const QItemSelection& selected, const QItemSelection& deselected) {
        selectionChangedHandler();
    });
    
    // Clear the selection when the layout of the model changes
    connect(clustersTreeView->model(), &QAbstractItemModel::layoutChanged, this, [this, clustersTreeView](const QList<QPersistentModelIndex> &parents = QList<QPersistentModelIndex>(), QAbstractItemModel::LayoutChangeHint hint = QAbstractItemModel::NoLayoutChangeHint) {
        clustersTreeView->selectionModel()->reset();
    });

    connect(clustersTreeView, &QTreeView::doubleClicked, this, [this, clustersAction, clustersTreeView](const QModelIndex& index) {
        const auto colorColumn = static_cast<std::int32_t>(ClustersModel::Column::Color);

        if (index.column() != colorColumn)
            return;

        // Get sibling color model index and the current cluster color
        const auto colorIndex   = _filterModel.mapToSource(index).siblingAtColumn(colorColumn);
        const auto currentColor = colorIndex.data(Qt::EditRole).value<QColor>();
        
        // Update the clusters model with the new color
        clustersAction->getClustersModel().setData(colorIndex, QColorDialog::getColor(currentColor));
    });

    auto toolbarLayout = new QHBoxLayout();

    toolbarLayout->addWidget(_removeAction.createWidget(this), 1);
    toolbarLayout->addWidget(_mergeAction.createWidget(this), 1);
    toolbarLayout->addWidget(clustersAction->getImportAction().createWidget(this), 1);
    toolbarLayout->addWidget(clustersAction->getExportAction().createWidget(this), 1);

    auto mainLayout = new QVBoxLayout();

    mainLayout->setMargin(0);
    mainLayout->addWidget(clustersTreeView);

    mainLayout->addWidget(_filterAndSelectAction.createWidget(this));
    mainLayout->addLayout(toolbarLayout);
    mainLayout->addWidget(_subsetAction.createWidget(this));

    setLayout(mainLayout);

    connect(&_removeAction, &TriggerAction::triggered, this, [this, clustersAction, clustersTreeView]() {
        const auto selectedRows = clustersTreeView->selectionModel()->selectedRows();

        QStringList clusterIds;

        for (auto selectedIndex : selectedRows)
            clusterIds << _filterModel.mapToSource(selectedIndex).siblingAtColumn(static_cast<std::int32_t>(ClustersModel::Column::ID)).data(Qt::DisplayRole).toString();

        clustersAction->removeClustersById(clusterIds);
    });

    connect(&_mergeAction, &TriggerAction::triggered, this, [this, clustersAction, clustersTreeView]() {
        const auto selectedRows = clustersTreeView->selectionModel()->selectedRows();

        QStringList clusterIdsToRemove;

        auto mergeCluster = static_cast<Cluster*>(_filterModel.mapToSource(selectedRows.first()).internalPointer());

        mergeCluster->setName(QString("%1*").arg(mergeCluster->getName()));

        for (auto selectedIndex : selectedRows) {
            auto cluster = static_cast<Cluster*>(_filterModel.mapToSource(selectedIndex).internalPointer());

            if (selectedIndex == selectedRows.first())
                continue;

            clusterIdsToRemove << cluster->getId();

            mergeCluster->getIndices().insert(mergeCluster->getIndices().end(), cluster->getIndices().begin(), cluster->getIndices().end());
        }

        clustersAction->removeClustersById(clusterIdsToRemove);
    });
    */
}
