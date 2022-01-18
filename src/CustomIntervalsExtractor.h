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
     */
    CustomIntervalsExtractor(AlgorithmAction& algorithmAction);

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
    CustomIntervalsExtractorSettingsAction  _settingsAction;            /** Settings action */
    Cluster                                 _candidateCluster;          /** Candidate cluster */
};
