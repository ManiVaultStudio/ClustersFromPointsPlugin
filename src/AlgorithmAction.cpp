#include "AlgorithmAction.h"
#include "IdentifierExtractor.h"
#include "StratificationExtractor.h"
#include "CustomIntervalsExtractor.h"
#include "ExtractorAction.h"
#include "ExtractMetaDataPlugin.h"

#include <QHBoxLayout>

using namespace hdps;

AlgorithmAction::AlgorithmAction(ExtractorAction& extractorAction, const Dataset<Points>& input) :
    WidgetAction(&extractorAction),
    _extractorAction(extractorAction),
    _input(input),
    _extractor(),
    _currentAction(this, "Group by", { "Identifier", "Stratification", "Intervals" }, "Identifier", "Identifier")
{
    setText("Extract by");
    setMayReset(true);

    // Change extractor
    const auto changeExtractor = [this]() -> void {
        switch (static_cast<ExtractMetaDataPlugin::Algorithm>(_currentAction.getCurrentIndex()))
        {
            case ExtractMetaDataPlugin::Algorithm::Identifier:
                _extractor = SharedExtractor(new IdentifierExtractor(*this, _input));
                break;

            case ExtractMetaDataPlugin::Algorithm::Stratification:
                _extractor = SharedExtractor(new StratificationExtractor(*this, _input));
                break;

            case ExtractMetaDataPlugin::Algorithm::Interval:
                _extractor = SharedExtractor(new CustomIntervalsExtractor(*this, _input));
                break;

            default:
                break;
        }

        // Pass-through clusters changed event
        connect(_extractor.get(), &Extractor::clustersChanged, this, &AlgorithmAction::clustersChanged);
    };

    // Update extractor when the algorithm selection changes
    connect(&_currentAction, &OptionAction::currentIndexChanged, changeExtractor);

    // Make sure to have a default algorithm allocated
    changeExtractor();

    // Request extraction when the algorithm type changes
    connect(&_currentAction, &OptionAction::currentIndexChanged, this, [this]() {
        _extractor->requestExtraction();
    });

    // Perform initial extraction
    _extractor->requestExtraction();
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

        // Add tool button
        layout->addWidget(algorithmAction->getExtractor()->getSettingsAction().createCollapsedWidget(this));
    };

    // Change settings widget when the algorithm changes
    connect(&algorithmAction->getCurrentAction(), &OptionAction::currentIndexChanged, onChangeAlgorithm);

    // Do initial update
    onChangeAlgorithm();
}
