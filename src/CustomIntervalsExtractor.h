#pragma once

#include "Extractor.h"
#include "CustomIntervalsExtractorSettingsAction.h"

/**
 * Custom intervals extractor class
 *
 * Extractor class for extracting clusters at custom intervals
 *
 * @author Thomas Kroes
 */
class CustomIntervalsExtractor : public Extractor
{
public:

    /**
     * Constructor
     * @param algorithmAction Reference to algorithm action
     * @param input Smart pointer to input points
     */
    CustomIntervalsExtractor(AlgorithmAction& algorithmAction, hdps::Dataset<Points> input);

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
    CustomIntervalsExtractorSettingsAction    _settingsAction;   /** Settings action */
};
