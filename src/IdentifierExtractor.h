#pragma once

#include "Extractor.h"
#include "IdentifierExtractorSettingsAction.h"

/**
 * Identifier extractor class
 *
 * Extractor class for grouping points based on their integral point value
 *
 * @author Thomas Kroes
 */
class IdentifierExtractor : public Extractor
{
public:

    /**
     * Constructor
     * @param algorithmAction Reference to algorithm action
     * @param input Smart pointer to input points
     */
    IdentifierExtractor(AlgorithmAction& algorithmAction, hdps::Dataset<Points> input);

    /** Performs the meta data extraction */
    void extract() override;

    /** Performs post extraction operations */
    void postExtract() override;

    /**
     * Get settings action (available through tool button next to algorithm selection)
     * @return Reference to settings widget action
     */
    WidgetAction& getSettingsAction() override;

protected:
    IdentifierExtractorSettingsAction   _settingsAction;    /** Settings action */
};
