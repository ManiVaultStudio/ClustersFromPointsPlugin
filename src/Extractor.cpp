#include "Extractor.h"

using namespace hdps;
using namespace hdps::util;

Extractor::Extractor(QObject* parent, hdps::Dataset<Points> input) :
    QObject(parent),
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
        QApplication::setOverrideCursor(Qt::WaitCursor);
        {
            extract();

            emit clustersChanged(_clusters);
        }
        QApplication::restoreOverrideCursor();
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
