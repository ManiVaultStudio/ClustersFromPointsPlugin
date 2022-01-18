#pragma once

#include <PointData.h>
#include <ClusterData.h>

#include <QTimer>
#include <QPair>

using namespace hdps::plugin;
using namespace hdps::gui;

class AlgorithmAction;
class ClustersModel;

/**
 * Base extractor class
 *
 * @author Thomas Kroes
 */
class Extractor : public QObject
{
    Q_OBJECT

public:

    /**
     * Constructor
     * @param algorithmAction Reference to algorithm action
     */
    Extractor(AlgorithmAction& algorithmAction);

    /** Destructor */
    ~Extractor() override = default;

    /**
     * Get settings action (available through tool button next to algorithm selection)
     * @return Reference to settings widget action
     */
    virtual WidgetAction& getSettingsAction() = 0;

    /** Request for an extraction (when not doing so already) */
    void requestExtraction();

    /**
     * Get clusters
     * @return Clusters
     */
    QVector<Cluster> getClusters();

    /**
     * Set clusters
     * @param clusters Clusters
     */
    void setClusters(const QVector<Cluster>& clusters);

    /**
     * Add a single cluster to the clusters dataset
     * @param cluster Cluster to add
     */
    void addCluster(const Cluster& cluster);

    /** Reset clusters */
    void resetClusters();

    /**
     * Set the dimension index
     * @param dimensionIndex Index of the dimension to extract the meta data from
     */
    void setDimensionIndex(std::int32_t dimensionIndex);

    /** Update the data range for the current dimension */
    void updateDataRange();

    /**
     * Get data range of points for the current dimension\
     * @return Data range as pair
     */
    QPair<float, float> getDataRange() const;

    /**
     * Get input dataset
     * @return Smart pointer to input points dataset
     */
    hdps::Dataset<Points> getInputDataset();

    /**
     * Get input dataset
     * @return Smart pointer to input points dataset
     */
    hdps::Dataset<Points> getInputDataset() const;

    /**
     * Get clusters dataset
     * @return Smart pointer to clusters dataset
     */
    hdps::Dataset<Clusters> getClustersDataset();

    /**
     * Get clusters dataset
     * @return Smart pointer to clusters dataset
     */
    hdps::Dataset<Clusters> getClustersDataset() const;

protected:

    /** Extract clusters from points dataset and assign them to the clusters dataset */
    virtual void extract() = 0;

    /** Performs post extraction operations */
    virtual void postExtract();

    /**
     * Get clusters model
     * @param Reference to clusters model
     */
    ClustersModel& getClustersModel();

signals:

    /** Signals that the extraction process finished */
    void extracted();

    /**
     * Signals that the current dimension index changed
     * @param dimensionIndex Current dimension index
     */
    void dimensionIndexChanged(std::int32_t dimensionIndex);

    /**
     * Signals that the data range changed
     * @param clusters Clusters
     */
    void dataRangeChanged(const QPair<float, float>& dataRange);

protected:
    AlgorithmAction&        _algorithmAction;   /** Reference to algorithm action */
    std::int32_t            _dimensionIndex;    /** Index of the dimension to extract the meta data from */
    QTimer                  _extractTimer;      /** Timer to prevent unnecessary updates */
    QPair<float, float>     _dataRange;         /** Data range for the dimension */
};

using SharedExtractor = QSharedPointer<Extractor>;
