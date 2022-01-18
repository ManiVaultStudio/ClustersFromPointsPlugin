#pragma once

#include "Extractor.h"
#include "IntervalsExtractorSettingsAction.h"

/**
 * Intervals extractor class
 *
 * Extractor class for extracting clusters at custom intervals
 *
 * @author Thomas Kroes
 */
class IntervalsExtractor : public Extractor
{
public:

    /**
     * Constructor
     * @param algorithmAction Reference to algorithm action
     */
    IntervalsExtractor(AlgorithmAction& algorithmAction);

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
     * Get candidate cluster (will be added to the clusters dataset when the add cluster action is triggered)
     * @return Reference to candidate cluster
     */
    Cluster& getCandidateCluster();

protected:
    IntervalsExtractorSettingsAction    _settingsAction;        /** Settings action */
    Cluster                             _candidateCluster;      /** Candidate cluster */
};
