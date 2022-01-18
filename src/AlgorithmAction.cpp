#include "AlgorithmAction.h"
#include "IdentifierExtractor.h"
#include "StratificationExtractor.h"
#include "IntervalsExtractor.h"
#include "SettingsAction.h"
#include "ClustersFromPointsPlugin.h"

#include <QHBoxLayout>

using namespace hdps;

AlgorithmAction::AlgorithmAction(SettingsAction& settingsAction) :
    WidgetAction(&settingsAction),
    _settingsAction(settingsAction),
    _extractor(),
    _currentAction(this, "Group by", { "Identifier", "Stratification", "Intervals" }, "Identifier", "Identifier")
{
    setText("Group by");
    setMayReset(true);

    // Change extractor
    const auto changeExtractor = [this]() -> void {
        switch (static_cast<ClustersFromPointsPlugin::Algorithm>(_currentAction.getCurrentIndex()))
        {
            case ClustersFromPointsPlugin::Algorithm::Identifier:
                _extractor = SharedExtractor(new IdentifierExtractor(_settingsAction.getAlgorithmAction()));
                break;

            case ClustersFromPointsPlugin::Algorithm::Stratification:
                _extractor = SharedExtractor(new StratificationExtractor(_settingsAction.getAlgorithmAction()));
                break;

            case ClustersFromPointsPlugin::Algorithm::Interval:
                _extractor = SharedExtractor(new IntervalsExtractor(_settingsAction.getAlgorithmAction()));
                break;

            default:
                break;
        }
    };

    // Update extractor when the algorithm selection changes
    connect(&_currentAction, &OptionAction::currentIndexChanged, changeExtractor);

    // Make sure to have a default algorithm allocated
    changeExtractor();

    // Request extraction when the algorithm type changes
    connect(&_currentAction, &OptionAction::currentIndexChanged, this, [this]() {
        _extractor->resetClusters();
        _extractor->requestExtraction();
    });
}

bool AlgorithmAction::isResettable() const
{
    return _currentAction.isResettable();
}

void AlgorithmAction::reset()
{
    _currentAction.reset();
}

SharedExtractor AlgorithmAction::getExtractor()
{
    return _extractor;
}

AlgorithmAction::Widget::Widget(QWidget* parent, AlgorithmAction* algorithmAction, const std::int32_t& widgetFlags) :
    QWidget(parent)
{
    auto layout = new QHBoxLayout();
    
    layout->setMargin(0);
    layout->addWidget(algorithmAction->getCurrentAction().createWidget(this));

    setLayout(layout);

    // Replace settings tool button
    const auto onChangeAlgorithm = [this, layout, algorithmAction]() -> void {

        // Remove existing settings tool button
        layout->takeAt(1);

        // Get extractor from algorithm
        auto extractor = algorithmAction->getExtractor();

        // Add tool button
        if (extractor)
            layout->addWidget(extractor->getSettingsAction().createCollapsedWidget(this));
    };

    // Change settings widget when the algorithm changes
    connect(&algorithmAction->getCurrentAction(), &OptionAction::currentIndexChanged, onChangeAlgorithm);

    // Do initial update
    onChangeAlgorithm();
}
