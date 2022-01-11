#pragma once

#include "Extractor.h"
#include "HistogramExtractorSettingsAction.h"

/**
 * TODO
 *
 * @author Thomas Kroes
 */
class HistogramExtractor : public Extractor
{
public:

    /**
     * Constructor
     * @param parent Pointer to parent object
     * @param input Smart pointer to input points
     */
    HistogramExtractor(QObject* parent, hdps::Dataset<Points> input);

    /** Performs the meta data extraction */
    void extract() override;

    /**
     * Get settings action (available through tool button next to algorithm selection)
     * @return Settings widget action
     */
    WidgetAction& getSettingsAction() override;

protected:
    HistogramExtractorSettingsAction    _settingsAction;    /** Settings action */
};
