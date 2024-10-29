#pragma once

#include <PointData/PointData.h>
#include <ClusterData/ClusterData.h>

#include <QTimer>
#include <QPair>

using namespace mv::plugin;
using namespace mv::gui;

class ClustersFromPointsPlugin;
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
    mv::Dataset<Points> getInputDataset();

    /**
     * Get input dataset
     * @return Smart pointer to input points dataset
     */
    mv::Dataset<Points> getInputDataset() const;

    /**
     * Get clusters dataset
     * @return Smart pointer to clusters dataset
     */
    mv::Dataset<Clusters> getClustersDataset();

    /**
     * Get clusters dataset
     * @return Smart pointer to clusters dataset
     */
    mv::Dataset<Clusters> getClustersDataset() const;

    /**
     * Get clusters from points plugin
     * @return Reference to clusters from points plugin
     */
    ClustersFromPointsPlugin& getClustersFromPointsPlugin();

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

public slots:
    void requestExtraction();

protected:
    AlgorithmAction&    _algorithmAction;   /** Reference to algorithm action */
};

using SharedExtractor = QSharedPointer<Extractor>;
