#include "IndexExtractorSettingsAction.h"
#include "IndexExtractor.h"
#include "ClustersFromPointsPlugin.h"

#include <Application.h>

#include <QHBoxLayout>

IndexExtractorSettingsAction::IndexExtractorSettingsAction(IndexExtractor& indexExtractor) :
    WidgetAction(&indexExtractor, "IndexExtractorSettingsAction"),
    _indexExtractor(indexExtractor),
    _startIndexAction(this, "Start index", 0, 1000000, 0)
{
    setIcon(Application::getIconFont("FontAwesome").getIcon("cog"));
    setText("Settings");

    _startIndexAction.setUpdateDuringDrag(false);
    _startIndexAction.setDefaultWidgetFlags(IntegralAction::SpinBox);
}

IndexExtractorSettingsAction::Widget::Widget(QWidget* parent, IndexExtractorSettingsAction* indexExtractorSettingsAction, const std::int32_t& widgetFlags) :
    WidgetActionWidget(parent, indexExtractorSettingsAction, widgetFlags)
{
    auto layout = new QHBoxLayout();

    layout->addWidget(indexExtractorSettingsAction->getStartIndexAction().createLabelWidget(this));
    layout->addWidget(indexExtractorSettingsAction->getStartIndexAction().createWidget(this));

    setLayout(layout);
}
