#include "IntervalsExtractorSettingsAction.h"
#include "IntervalsExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

using namespace hdps;

IntervalsExtractorSettingsAction::IntervalsExtractorSettingsAction(IntervalsExtractor& intervalsExtractor) :
    WidgetAction(&intervalsExtractor),
    _intervalsExtractor(intervalsExtractor),
    _intervalAction(this, "Point value range"),
    _numberOfPointsAction(this, "Number of points", 0, 1000000000),
    _clusterNameAction(this, "Cluster name"),
    _addClusterAction(this, "Add cluster(s)")
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    // Set the number of clusters action as read-only
    _numberOfPointsAction.setEnabled(false);
    _numberOfPointsAction.setDefaultWidgetFlags(IntegralAction::LineEdit);

    // Update the extractor data range when the extractor current dimension index changes
    connect(&_intervalsExtractor, &Extractor::dimensionIndexChanged, &_intervalsExtractor, &Extractor::updateDataRange);

    // Perform an initial computation of the data range
    _intervalsExtractor.updateDataRange();

    // Request extraction when the number of strata changes
    connect(&_intervalAction, &DecimalRangeAction::rangeChanged, &_intervalsExtractor, &Extractor::requestExtraction);

    // Update actions post-extraction
    connect(&_intervalsExtractor, &Extractor::extracted, this, [this]() -> void {

        // Establish the number of points
        const auto numberOfPoints = _intervalsExtractor.getCandidateCluster().getNumberOfIndices();

        // Update actions
        _numberOfPointsAction.setValue(numberOfPoints);
        _clusterNameAction.setEnabled(numberOfPoints >= 1);
        _clusterNameAction.setString("[" + QString::number(_intervalAction.getMinimum()) + " - " + QString::number(_intervalAction.getMaximum()) + "]");
        _addClusterAction.setEnabled(numberOfPoints >= 1);
    });

    const auto updateDataRangeAction = [this]() -> void {

        // Get the data range from the extractor
        const auto dataRange = _intervalsExtractor.getDataRange();

        // Update the range in the action
        _intervalAction.setRange(dataRange.first, dataRange.second);
    };

    // Update the range action when the data range in the extractor changes
    connect(&_intervalsExtractor, &Extractor::dataRangeChanged, this, updateDataRangeAction);

    // Perform an initial update of the data range action
    updateDataRangeAction();

    // Add cluster when the action is triggered
    connect(&_addClusterAction, &TriggerAction::triggered, this, [this]() -> void {

        // Update cluster name
        _intervalsExtractor.getCandidateCluster().setName(_clusterNameAction.getString());

        // Add clusters for the current configuration
        _intervalsExtractor.addCluster(_intervalsExtractor.getCandidateCluster());
    });

    // Perform an initial extraction
    _intervalsExtractor.requestExtraction();
}

IntervalsExtractorSettingsAction::Widget::Widget(QWidget* parent, IntervalsExtractorSettingsAction* intervalsExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, intervalsExtractorSettingsAction, widgetFlags)
{
    auto layout = new QGridLayout();

    layout->addWidget(intervalsExtractorSettingsAction->getRangeAction().getRangeMinAction().createLabelWidget(this), 0, 0);
    layout->addWidget(intervalsExtractorSettingsAction->getRangeAction().getRangeMinAction().createWidget(this), 0, 1);
    layout->addWidget(intervalsExtractorSettingsAction->getRangeAction().getRangeMaxAction().createLabelWidget(this), 1, 0);
    layout->addWidget(intervalsExtractorSettingsAction->getRangeAction().getRangeMaxAction().createWidget(this), 1, 1);
    layout->addWidget(intervalsExtractorSettingsAction->getNumberOfClustersInRangeAction().createLabelWidget(this), 2, 0);
    layout->addWidget(intervalsExtractorSettingsAction->getNumberOfClustersInRangeAction().createWidget(this), 2, 1);
    layout->addWidget(intervalsExtractorSettingsAction->getClusterNameAction().createLabelWidget(this), 3, 0);
    layout->addWidget(intervalsExtractorSettingsAction->getClusterNameAction().createWidget(this), 3, 1);
    layout->addWidget(intervalsExtractorSettingsAction->getAddClusterAction().createWidget(this), 4, 1);

    setPopupLayout(layout);
}
