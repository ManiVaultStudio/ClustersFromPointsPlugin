#include "IntervalExtractorSettingsAction.h"
#include "IntervalExtractor.h"

#include <Application.h>

#include <QHBoxLayout>

using namespace hdps;

IntervalExtractorSettingsAction::IntervalExtractorSettingsAction(CustomIntervalsExtractor& intervalExtractor) :
    WidgetAction(&intervalExtractor),
    _stratificationExtractor(intervalExtractor),
    _rangeAction(this, "Point value range", 1, 100, 10, 10),
    _numberOfClustersInRangeAction(this, "Number of clusters in range", 1, 1000000000),
    _addClusterAction(this, "Add cluster(s)")
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    // Request extraction when the number of strata changes
    //connect(&_rangeAction, &IntegralAction::valueChanged, &_stratificationExtractor, &IntervalExtractor::requestExtraction);
}

IntervalExtractorSettingsAction::Widget::Widget(QWidget* parent, IntervalExtractorSettingsAction* intervalExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, intervalExtractorSettingsAction, widgetFlags)
{
    auto layout = new QGridLayout();

    layout->addWidget(intervalExtractorSettingsAction->getRangeAction().getRangeMinAction().createLabelWidget(this), 0, 0);
    layout->addWidget(intervalExtractorSettingsAction->getRangeAction().getRangeMinAction().createWidget(this), 0, 1);

    layout->addWidget(intervalExtractorSettingsAction->getRangeAction().getRangeMinAction().createLabelWidget(this), 1, 0);
    layout->addWidget(intervalExtractorSettingsAction->getRangeAction().getRangeMinAction().createWidget(this), 1, 1);

    layout->addWidget(intervalExtractorSettingsAction->getNumberOfClustersInRangeAction().createLabelWidget(this), 2, 0);
    layout->addWidget(intervalExtractorSettingsAction->getNumberOfClustersInRangeAction().createWidget(this), 2, 1);

    layout->addWidget(intervalExtractorSettingsAction->getAddClusterAction().createWidget(this), 3, 1);

    setPopupLayout(layout);
}
