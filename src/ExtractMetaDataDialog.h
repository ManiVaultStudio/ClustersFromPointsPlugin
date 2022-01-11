#pragma once

#include "ClustersAction.h"
#include "ExtractorAction.h"

using namespace hdps::util;

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
     * @param input Smart pointer to input points
     */
    ExtractMetaDataDialog(QWidget* parent, const Dataset<Points>& input);

    /** Get preferred size */
    QSize sizeHint() const override {
        return QSize(600, 500);
    }

    /** Get minimum size hint*/
    QSize minimumSizeHint() const override {
        return sizeHint();
    }

protected:
    ExtractorAction     _extractorAction;       /** Extractor action */
};
