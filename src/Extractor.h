#pragma once

#include <PointData.h>
#include <ClusterData.h>

#include <QObject>
#include <QTimer>

using namespace hdps::plugin;
using namespace hdps::util;
using namespace hdps::gui;

/**
 * TODO
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
    std::vector<Cluster>& getClusters();

protected:

    /** Performs the meta data extraction */
    virtual void extract() = 0;

protected:
    hdps::Dataset<Points>   _input;             /** Smart pointer to input points */
    QTimer                  _extractTimer;      /** Timer to prevent unnecessary updates */
    std::vector<Cluster>    _clusters;          /** Extracted clusters */
};

using SharedExtractor = QSharedPointer<Extractor>;
