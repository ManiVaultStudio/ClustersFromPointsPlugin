#pragma once

#include "Extractor.h"
#include "IdentifierExtractorSettingsAction.h"

/**
 * TODO
 *
 * @author Thomas Kroes
 */
class IdentifierExtractor : public Extractor
{
public:

    /**
     * Constructor
     * @param parent Pointer to parent object
     * @param input Smart pointer to input points
     */
    IdentifierExtractor(QObject* parent, hdps::Dataset<Points> input);

    /** Performs the meta data extraction */
    void extract() override;

    /**
     * Get settings action (available through tool button next to algorithm selection)
     * @return Settings widget action
     */
    WidgetAction& getSettingsAction() override;

protected:
    IdentifierExtractorSettingsAction    _settingsAction;    /** Settings action */
};
