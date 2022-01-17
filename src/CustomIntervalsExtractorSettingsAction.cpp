#include "CustomIntervalsExtractorSettingsAction.h"
#include "CustomIntervalsExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

using namespace hdps;

CustomIntervalsExtractorSettingsAction::CustomIntervalsExtractorSettingsAction(CustomIntervalsExtractor& customIntervalsExtractor) :
    WidgetAction(&customIntervalsExtractor),
    _customIntervalsExtractor(customIntervalsExtractor),
    _rangeAction(this, "Point value range", 1, 100, 10, 10),
    _numberOfClustersInRangeAction(this, "Number of clusters in range", 1, 1000000000),
    _addClusterAction(this, "Add cluster(s)")
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    // Request extraction when the number of strata changes
    connect(&_rangeAction, &DecimalRangeAction::rangeChanged, &_customIntervalsExtractor, &CustomIntervalsExtractor::requestExtraction);
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

    layout->addWidget(customIntervalsExtractorSettingsAction->getAddClusterAction().createWidget(this), 3, 1);

    setPopupLayout(layout);
}
