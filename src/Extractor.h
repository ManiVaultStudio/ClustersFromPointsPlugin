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

protected:
    AlgorithmAction&    _algorithmAction;   /** Reference to algorithm action */
    QTimer              _extractTimer;      /** Timer to prevent unnecessary updates */
};

using SharedExtractor = QSharedPointer<Extractor>;
