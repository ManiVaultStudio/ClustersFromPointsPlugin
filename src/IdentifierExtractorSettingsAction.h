#pragma once

#include <actions/VerticalGroupAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/StringAction.h>
#include <actions/TriggerAction.h>
#include <actions/DatasetPickerAction.h>

#include <PointData/DimensionPickerAction.h>

using namespace mv::gui;

class IdentifierExtractor;

/**
 * Identifier extractor settings action class
 *
 * For configuring identifier extractor settings
 *
 * @author Thomas Kroes
 */
class IdentifierExtractorSettingsAction : public VerticalGroupAction
{
    Q_OBJECT

public:

    /**
     * Constructor
     * @param identifierExtractor Reference to identifier extractor
     */
    IdentifierExtractorSettingsAction(IdentifierExtractor& identifierExtractor);

protected: // Action getters

    DimensionPickerAction& getDimensionAction() { return _dimensionAction; }
    DatasetPickerAction& getExternalDatasetAction() { return _externalDatasetAction; }

protected:
    IdentifierExtractor&    _identifierExtractor;       /** Reference to identifier extractor */
    DimensionPickerAction   _dimensionAction;           /** Current dimension action */
    DatasetPickerAction     _externalDatasetAction;     /** Dataset picker action for picking an external dataset */
    
    friend class IdentifierExtractor;
};
