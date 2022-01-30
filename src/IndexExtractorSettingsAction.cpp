#include "IndexExtractorSettingsAction.h"
#include "IndexExtractor.h"
#include "ClustersFromPointsPlugin.h"

#include <Application.h>

#include <QHBoxLayout>

IndexExtractorSettingsAction::IndexExtractorSettingsAction(IndexExtractor& indexExtractor) :
    WidgetAction(&indexExtractor),
    _indexExtractor(indexExtractor),
    _startIndexAction(this, "Start index", 0, 1000000, 0, 0)
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    _startIndexAction.setUpdateDuringDrag(false);
    _startIndexAction.setDefaultWidgetFlags(IntegralAction::SpinBox);
    _startIndexAction.setSettingsPrefix("/StartIndex", &_indexExtractor.getClustersFromPointsPlugin());

    // Request extraction when the start index changes
    connect(&_startIndexAction, &IntegralAction::valueChanged, &_indexExtractor, &IndexExtractor::requestExtraction);

    // Request extraction an initial extraction
    _indexExtractor.requestExtraction();
}

IndexExtractorSettingsAction::Widget::Widget(QWidget* parent, IndexExtractorSettingsAction* indexExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, indexExtractorSettingsAction, widgetFlags)
{
    auto layout = new QHBoxLayout();

    layout->addWidget(indexExtractorSettingsAction->getStartIndexAction().createLabelWidget(this));
    layout->addWidget(indexExtractorSettingsAction->getStartIndexAction().createWidget(this));

    setPopupLayout(layout);
}
