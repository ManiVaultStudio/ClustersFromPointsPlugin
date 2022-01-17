#pragma once

#include "Extractor.h"
#include "IntervalsExtractorSettingsAction.h"

/**
 * Custom intervals extractor class
 *
 * Extractor class for extracting cluster at custom intervals
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
    IntervalExtractorSettingsAction    _settingsAction;   /** Settings action */
};
