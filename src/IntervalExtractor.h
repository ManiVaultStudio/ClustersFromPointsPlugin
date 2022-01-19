#pragma once

#include "Extractor.h"
#include "IntervalExtractorSettingsAction.h"

/**
 * Interval extractor class
 *
 * Extractor class for extracting a cluster at a user specified interval
 *
 * @author Thomas Kroes
 */
class IntervalExtractor : public Extractor
{
public:

    /**
     * Constructor
     * @param algorithmAction Reference to algorithm action
     */
    IntervalExtractor(AlgorithmAction& algorithmAction);

    /** Extract clusters from points dataset and assign them to the clusters dataset */
    void extract() override;

    /** Performs post extraction operations */
    void postExtract() override;

    /**
     * Get settings action (available through tool button next to algorithm selection)
     * @return Reference to settings widget action
     */
    WidgetAction& getSettingsAction() override;

    /**
     * Get candidate cluster
     * @return Copy of the extracted cluster (copy is required for identifier uniqueness)
     */
    Cluster getCluster();

protected:
    IntervalExtractorSettingsAction     _settingsAction;        /** Settings action */
    Cluster                             _extractedCluster;      /** Extracted cluster */
};
