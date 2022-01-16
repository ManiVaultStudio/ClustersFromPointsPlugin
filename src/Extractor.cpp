#include "Extractor.h"
#include "AlgorithmAction.h"

using namespace hdps;

Extractor::Extractor(AlgorithmAction& algorithmAction, hdps::Dataset<Points> input) :
    QObject(&algorithmAction),
    _algorithmAction(algorithmAction),
    _input(input),
    _dimensionIndex(0),
    _extractTimer(),
    _clusters()
{
    // Configure extraction timer
    _extractTimer.setSingleShot(true);
    _extractTimer.setInterval(100);

    // Perform the extract process when the timer times out
    connect(&_extractTimer, &QTimer::timeout, [this]() {

        // Perform the extraction
        extract();

        // Notify others that the clusters changed
        emit clustersChanged(_clusters);

        // Execute post extraction operations
        postExtract();
    });
}

void Extractor::requestExtraction()
{
    // Do not extract when the timers is active
    if (_extractTimer.isActive())
        return;

    // Postpone extraction
    _extractTimer.start();
}

QVector<Cluster>& Extractor::getClusters()
{
    return _clusters;
}

void Extractor::setDimensionIndex(std::int32_t dimensionIndex)
{
    _dimensionIndex = dimensionIndex;

    requestExtraction();
}
