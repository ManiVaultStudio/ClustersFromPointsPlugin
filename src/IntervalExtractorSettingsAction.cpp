#include "IntervalExtractorSettingsAction.h"
#include "IntervalExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

using namespace hdps;

IntervalExtractorSettingsAction::IntervalExtractorSettingsAction(IntervalExtractor& intervalExtractor) :
    WidgetAction(&intervalExtractor, "IntervalExtractorSettingsAction"),
    _intervalExtractor(intervalExtractor),
    _dimensionAction(this, "Dimension"),
    _intervalAction(this, "Point value range"),
    _numberOfPointsAction(this, "Number of points", 0, 1000000000)
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    //_intervalAction.getRangeMinAction().setUpdateDuringDrag(false);
    //_intervalAction.getRangeMaxAction().setUpdateDuringDrag(false);

    // Update the data range and perform an initial extraction
    _intervalExtractor.updateDataRange();
    _intervalExtractor.requestExtraction();

    // Request extraction when the current dimension changes
    connect(&_dimensionAction, &DimensionPickerAction::currentDimensionIndexChanged, this, [this](const std::int32_t& currentDimensionIndex) {
        _intervalExtractor.updateDataRange();
        _intervalExtractor.requestExtraction();
    });

    // Set the number of clusters action as read-only
    _numberOfPointsAction.setEnabled(false);
    _numberOfPointsAction.setDefaultWidgetFlags(IntegralAction::LineEdit);

    // Request extraction when the current dimension changes
    connect(&_dimensionAction, &DimensionPickerAction::currentDimensionIndexChanged, this, [this](const std::int32_t& currentDimensionIndex) {
        _intervalExtractor.requestExtraction();
    });

    // Request extraction when the number of strata changes
    connect(&_intervalAction, &DecimalRangeAction::rangeChanged, &_intervalExtractor, &Extractor::requestExtraction);

    // Update actions post-extraction
    connect(&_intervalExtractor, &Extractor::extracted, this, [this]() -> void {
        _numberOfPointsAction.setValue(_intervalExtractor.getCluster().getNumberOfIndices());
    });

    const auto updateDataRangeAction = [this]() -> void {

        // Get the data range from the extractor
        const auto dataRange = _intervalExtractor.getDataRange();

        // Only process valid range
        if (dataRange.first >= dataRange.second)
            return;

        // Update the range in the action
        _intervalAction.setRange({ dataRange.first, dataRange.second });
    };

    // Update the range action when the data range in the extractor changes
    connect(&_intervalExtractor, &IntervalExtractor::dataRangeChanged, this, updateDataRangeAction);

    // Perform an initial update of the data range action
    updateDataRangeAction();
}

IntervalExtractorSettingsAction::Widget::Widget(QWidget* parent, IntervalExtractorSettingsAction* intervalExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, intervalExtractorSettingsAction, widgetFlags)
{
    auto layout = new QGridLayout();

    layout->addWidget(intervalExtractorSettingsAction->getDimensionAction().createLabelWidget(this), 0, 0);
    layout->addWidget(intervalExtractorSettingsAction->getDimensionAction().createWidget(this), 0, 1);
    layout->addWidget(intervalExtractorSettingsAction->getRangeAction().getRangeMinAction().createLabelWidget(this), 1, 0);
    layout->addWidget(intervalExtractorSettingsAction->getRangeAction().getRangeMinAction().createWidget(this), 1, 1);
    layout->addWidget(intervalExtractorSettingsAction->getRangeAction().getRangeMaxAction().createLabelWidget(this), 2, 0);
    layout->addWidget(intervalExtractorSettingsAction->getRangeAction().getRangeMaxAction().createWidget(this), 2, 1);
    layout->addWidget(intervalExtractorSettingsAction->getNumberOfPointsAction().createLabelWidget(this), 3, 0);
    layout->addWidget(intervalExtractorSettingsAction->getNumberOfPointsAction().createWidget(this), 3, 1);

    setLayout(layout);
}
