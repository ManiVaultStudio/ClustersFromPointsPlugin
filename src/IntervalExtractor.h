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
class IntervalExtractor final : public Extractor
{
    Q_OBJECT

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

    /**
     * Get data range of points for the current dimension\
     * @return Data range as pair
     */
    QPair<float, float> getDataRange() const;

    /** Update the data range for the current dimension */
    void updateDataRange();

signals:

    /**
     * Signals that the data range changed
     * @param dataRange Range of the data
     */
    void dataRangeChanged(const QPair<float, float>& dataRange);

protected:
    IntervalExtractorSettingsAction     _settingsAction;        /** Settings action */
    Cluster                             _extractedCluster;      /** Extracted cluster */
    QPair<float, float>                 _dataRange;             /** Data range for the current dimension */
};
