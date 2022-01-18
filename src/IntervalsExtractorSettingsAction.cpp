#include "CustomIntervalsExtractorSettingsAction.h"
#include "CustomIntervalsExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

using namespace hdps;

CustomIntervalsExtractorSettingsAction::CustomIntervalsExtractorSettingsAction(CustomIntervalsExtractor& customIntervalsExtractor) :
    WidgetAction(&customIntervalsExtractor),
    _customIntervalsExtractor(customIntervalsExtractor),
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
    connect(&_customIntervalsExtractor, &Extractor::dimensionIndexChanged, &_customIntervalsExtractor, &Extractor::updateDataRange);

    // Perform an initial computation of the data range
    _customIntervalsExtractor.updateDataRange();

    // Take action when the data range changed
    const auto intervalChanged = [this]() -> void {

        _customIntervalsExtractor.requestExtraction();

        // Establish the number of points
        const auto numberOfPoints = _customIntervalsExtractor.getCandidateCluster().getNumberOfIndices();

        // Update actions
        _numberOfPointsAction.setValue(numberOfPoints);
        _clusterNameAction.setEnabled(numberOfPoints >= 1);
        _clusterNameAction.setString("[" + QString::number(_intervalAction.getMinimum()) + " - " + QString::number(_intervalAction.getMaximum()) + "]");
        _addClusterAction.setEnabled(numberOfPoints >= 1);
    };

    // Request extraction when the number of strata changes
    connect(&_intervalAction, &DecimalRangeAction::rangeChanged, this, intervalChanged);

    const auto updateDataRangeAction = [this]() -> void {

        // Get the data range from the extractor
        const auto dataRange = _customIntervalsExtractor.getDataRange();

        // Update the range in the action
        _intervalAction.setRange(dataRange.first, dataRange.second);
    };

    // Update the range action when the data range in the extractor changes
    connect(&_customIntervalsExtractor, &Extractor::dataRangeChanged, this, updateDataRangeAction);

    // Perform an initial update of the data range action
    updateDataRangeAction();

    // Add cluster when the action is triggered
    connect(&_addClusterAction, &TriggerAction::triggered, this, [this]() -> void {

        // Update cluster name
        _customIntervalsExtractor.getCandidateCluster().setName(_clusterNameAction.getString());

        // Add clusters for the current configuration
        _customIntervalsExtractor.addCluster(_customIntervalsExtractor.getCandidateCluster());
    });
}

CustomIntervalsExtractorSettingsAction::Widget::Widget(QWidget* parent, CustomIntervalsExtractorSettingsAction* customIntervalsExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, customIntervalsExtractorSettingsAction, widgetFlags)
{
    auto layout = new QGridLayout();

    layout->addWidget(customIntervalsExtractorSettingsAction->getRangeAction().getRangeMinAction().createLabelWidget(this), 0, 0);
    layout->addWidget(customIntervalsExtractorSettingsAction->getRangeAction().getRangeMinAction().createWidget(this), 0, 1);
    layout->addWidget(customIntervalsExtractorSettingsAction->getRangeAction().getRangeMaxAction().createLabelWidget(this), 1, 0);
    layout->addWidget(customIntervalsExtractorSettingsAction->getRangeAction().getRangeMaxAction().createWidget(this), 1, 1);
    layout->addWidget(customIntervalsExtractorSettingsAction->getNumberOfClustersInRangeAction().createLabelWidget(this), 2, 0);
    layout->addWidget(customIntervalsExtractorSettingsAction->getNumberOfClustersInRangeAction().createWidget(this), 2, 1);
    layout->addWidget(customIntervalsExtractorSettingsAction->getClusterNameAction().createLabelWidget(this), 3, 0);
    layout->addWidget(customIntervalsExtractorSettingsAction->getClusterNameAction().createWidget(this), 3, 1);
    layout->addWidget(customIntervalsExtractorSettingsAction->getAddClusterAction().createWidget(this), 4, 1);

    setPopupLayout(layout);
}
