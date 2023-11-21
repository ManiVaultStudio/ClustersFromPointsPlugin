#pragma once

#include <actions/WidgetAction.h>
#include <actions/WidgetActionWidget.h>
#include <actions/StringAction.h>
#include <actions/TriggerAction.h>
#include <actions/IntegralAction.h>

using namespace mv::gui;

class IndexExtractor;

/**
 * Index extractor settings action class
 *
 * Action class for configuring index extractor settings
 *
 * @author Thomas Kroes
 */
class IndexExtractorSettingsAction : public WidgetAction
{
    Q_OBJECT

public:

    /** Widget class for index extractor settings action */
    class Widget : public WidgetActionWidget
    {
    protected:

        /**
         * Constructor
         * @param parent Pointer to parent widget
         * @param indexExtractorSettingsAction Pointer to index extractor settings action
         * @param widgetFlags Widget flags for the configuration of the widget
         */
        Widget(QWidget* parent, IndexExtractorSettingsAction* indexExtractorSettingsAction, const std::int32_t& widgetFlags);

    protected:

        friend class IndexExtractorSettingsAction;
    };

protected:

    /**
     * Get widget representation of the identifier extractor settings action
     * @param parent Pointer to parent widget
     * @param widgetFlags Widget flags for the configuration of the widget
     */
    QWidget* getWidget(QWidget* parent, const std::int32_t& widgetFlags) override
    {
        return new Widget(parent, this, widgetFlags);
    }

public:

    /**
     * Constructor
     * @param indexExtractor Reference to index extractor
     */
    IndexExtractorSettingsAction(IndexExtractor& indexExtractor);

public: // Action getters

    IntegralAction& getStartIndexAction() { return _startIndexAction; }

protected:
    IndexExtractor&     _indexExtractor;        /** Reference to index extractor */
    IntegralAction      _startIndexAction;      /** Start index action */

    friend class IndexExtractor;
};
