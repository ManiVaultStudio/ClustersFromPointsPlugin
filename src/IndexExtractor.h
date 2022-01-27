#pragma once

#include "Extractor.h"
#include "IndexExtractorSettingsAction.h"

/**
 * Index extractor class
 *
 * Extractor class for grouping points based on their point index
 *
 * @author Thomas Kroes
 */
class IndexExtractor final : public Extractor
{
public:

    /**
     * Constructor
     * @param algorithmAction Reference to algorithm action
     */
    IndexExtractor(AlgorithmAction& algorithmAction);

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
    IndexExtractorSettingsAction   _settingsAction;    /** Settings action */
};
