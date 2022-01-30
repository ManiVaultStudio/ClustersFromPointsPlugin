#include "AlgorithmAction.h"
#include "IdentifierExtractor.h"
#include "IndexExtractor.h"
#include "StratificationExtractor.h"
#include "IntervalExtractor.h"
#include "SettingsAction.h"
#include "ClustersFromPointsPlugin.h"

#include <QHBoxLayout>

using namespace hdps;

AlgorithmAction::AlgorithmAction(SettingsAction& settingsAction) :
    WidgetAction(&settingsAction),
    _settingsAction(settingsAction),
    _extractor(),
    _currentAction(this, "Group by", ClustersFromPointsPlugin::algorithmNames.values())
{
    setText("Group by"); 
    setMayReset(true);
}

SharedExtractor AlgorithmAction::getExtractor()
{
    return _extractor;
}

void AlgorithmAction::init()
{
    // Change extractor
    const auto changeExtractor = [this]() -> void {
        switch (static_cast<ClustersFromPointsPlugin::Algorithm>(_currentAction.getCurrentIndex()))
        {
            case ClustersFromPointsPlugin::Algorithm::Identifier:
                _extractor = SharedExtractor(new IdentifierExtractor(_settingsAction.getAlgorithmAction()));
                break;

            case ClustersFromPointsPlugin::Algorithm::Index:
                _extractor = SharedExtractor(new IndexExtractor(_settingsAction.getAlgorithmAction()));
                break;

            case ClustersFromPointsPlugin::Algorithm::Stratification:
                _extractor = SharedExtractor(new StratificationExtractor(_settingsAction.getAlgorithmAction()));
                break;

            case ClustersFromPointsPlugin::Algorithm::Interval:
                _extractor = SharedExtractor(new IntervalExtractor(_settingsAction.getAlgorithmAction()));
                break;

            default:
                break;
        }

        // Notify that the current extractor changed
        emit extractorChanged(_extractor.get());
    };

    // Update extractor when the algorithm selection changes
    connect(&_currentAction, &OptionAction::currentIndexChanged, changeExtractor);

    // Make sure to have a default algorithm allocated
    changeExtractor();

    // Request extraction when the algorithm type changes
    //connect(&_currentAction, &OptionAction::currentIndexChanged, _extractor.get(), &Extractor::resetClusters);
}

AlgorithmAction::Widget::Widget(QWidget* parent, AlgorithmAction* algorithmAction, const std::int32_t& widgetFlags) :
    QWidget(parent)
{
    auto layout = new QHBoxLayout();
    
    layout->setMargin(0);
    layout->addWidget(algorithmAction->getCurrentAction().createWidget(this));

    setLayout(layout);

    // Replace settings tool button
    const auto extractorChanged = [this, layout, algorithmAction](Extractor* extractor = nullptr) -> void {

        // Remove existing settings tool button
        if (layout->count() == 2)
            layout->takeAt(1);

        // Add tool button
        if (extractor)
            layout->addWidget(extractor->getSettingsAction().createCollapsedWidget(this));
    };

    // Change settings widget when the algorithm changes
    connect(algorithmAction, &AlgorithmAction::extractorChanged, this, extractorChanged);

    // Do initial update
    extractorChanged();
}
