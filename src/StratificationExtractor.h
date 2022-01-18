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
     */
    StratificationExtractor(AlgorithmAction& algorithmAction);

    /** Extract clusters from points dataset and assign them to the clusters dataset */
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
