#pragma once

#include "Extractor.h"
#include "StratificationExtractorSettingsAction.h"

/**
 * Stratification extractor class
 *
 * Extractor class for extracting cluster at regular intervals
 *
 * @author Thomas Kroes
 */
class StratificationExtractor : public Extractor
{
public:

    /**
     * Constructor
     * @param algorithmAction Reference to algorithm action
     * @param input Smart pointer to input points
     */
    StratificationExtractor(AlgorithmAction& algorithmAction, hdps::Dataset<Points> input);

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
    StratificationExtractorSettingsAction    _settingsAction;   /** Settings action */
};
