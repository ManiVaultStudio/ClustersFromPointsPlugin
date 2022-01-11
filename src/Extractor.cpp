#include "Extractor.h"

using namespace hdps;
using namespace hdps::util;

Extractor::Extractor(QObject* parent, hdps::Dataset<Points> input) :
    QObject(parent),
    _input(input),
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

std::vector<Cluster>& Extractor::getClusters()
{
    return _clusters;
}