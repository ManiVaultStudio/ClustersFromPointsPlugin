#pragma once

#include "actions/Actions.h"

#include "ClustersAction.h"

using namespace hdps::util;

namespace hdps {

/**
 * Extract meta data dialog class
 *
 * Dialog for extracting meta data from a source dataset
 *
 * @author Thomas Kroes
 */
class ExtractMetaDataDialog : public QDialog
{
public:

    /**
     * Constructor
     * @param parent Pointer to parent widget
     * @param sourceDataset Source dataset to extract meta data from
     */
    ExtractMetaDataDialog(QWidget* parent, const Dataset<DatasetImpl>& sourceDataset);

    /** Get preferred size */
    QSize sizeHint() const override {
        return QSize(600, 500);
    }

    /** Get minimum size hint*/
    QSize minimumSizeHint() const override {
        return sizeHint();
    }

protected:

protected:
    Dataset<DatasetImpl>    _dataset;                   /** Smart pointer to the source dataset */
    GroupAction             _groupAction;               /** Group action */
    StringAction            _sourceDatasetNameAction;   /** Source dataset name action */
    StringAction            _targetDatasetNameAction;   /** Target dataset name action */
    ToggleAction            _existingDatasetAction;     /** Existing dataset action */
    DatasetPickerAction     _targetDatasetAction;       /** Target dataset action */
    OptionAction            _groupByAction;             /** Group by action */
    ClustersAction          _clustersAction;            /** Clusters action */
};

}
