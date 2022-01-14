#pragma once

#include "Extractor.h"
#include "RegularIntervalsExtractorSettingsAction.h"

/**
 * Regular intervals extractor class
 *
 * Extractor class for extracting cluster at regular intervals
 *
 * @author Thomas Kroes
 */
class RegularIntervalsExtractor : public Extractor
{
public:

    /**
     * Constructor
     * @param parent Pointer to parent object
     * @param input Smart pointer to input points
     */
    RegularIntervalsExtractor(QObject* parent, hdps::Dataset<Points> input);

    /** Performs the meta data extraction */
    void extract() override;

    /**
     * Get settings action (available through tool button next to algorithm selection)
     * @return Settings widget action
     */
    WidgetAction& getSettingsAction() override;

protected:
    RegularIntervalsExtractorSettingsAction    _settingsAction;    /** Settings action */
};
