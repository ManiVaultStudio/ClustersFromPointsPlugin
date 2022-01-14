#pragma once

#include <PointData.h>
#include <ClusterData.h>

#include <QObject>
#include <QTimer>

using namespace hdps::plugin;
using namespace hdps::util;
using namespace hdps::gui;

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
     * @param parent Pointer to parent object
     * @param input Smart pointer to input points
     */
    Extractor(QObject* parent, hdps::Dataset<Points> input);

    /** Destructor */
    ~Extractor() override = default;

    /**
     * Get settings action (available through tool button next to algorithm selection)
     * @return Settings widget action
     */
    virtual WidgetAction& getSettingsAction() = 0;

    /** Request for an extraction (when not doing so already) */
    void requestExtraction();

    /**
     * Get clusters
     * @return Clusters
     */
    QVector<Cluster>& getClusters();

    /**
     * Set the dimension index
     * @param dimensionIndex Index of the dimension to extract the meta data from
     */
    void setDimensionIndex(std::int32_t dimensionIndex);

protected:

    /** Performs the meta data extraction */
    virtual void extract() = 0;

signals:

    /**
     * Signals that the clusters changed
     * @param clusters Clusters
     */
    void clustersChanged(const QVector<Cluster>& clusters);

protected:
    hdps::Dataset<Points>   _input;             /** Smart pointer to input points */
    std::int32_t            _dimensionIndex;    /** Index of the dimension to extract the meta data from */
    QTimer                  _extractTimer;      /** Timer to prevent unnecessary updates */
    QVector<Cluster>        _clusters;          /** Extracted clusters */
};

using SharedExtractor = QSharedPointer<Extractor>;
