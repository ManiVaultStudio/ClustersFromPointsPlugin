#include "IdentifierExtractorSettingsAction.h"
#include "IdentifierExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

IdentifierExtractorSettingsAction::IdentifierExtractorSettingsAction(IdentifierExtractor& identifierExtractor) :
    VerticalGroupAction(&identifierExtractor, "IdentifierExtractorSettingsAction"),
    _dimensionAction(this, "Dimension"),
    _externalDatasetAction(this, "External dataset"),
    _identifierExtractor(identifierExtractor)
{
    setIconByName("gear");
    setText("Settings");

    _externalDatasetAction.setDefaultWidgetFlag(DatasetPickerAction::WidgetFlag::Clearable);
    
    addAction(&_dimensionAction);
    addAction(&_externalDatasetAction);
}
