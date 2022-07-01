#ifndef WIDGETWORDDEFINITION_H
#define WIDGETWORDDEFINITION_H

#include <QWidget>

namespace Ui {
class WidgetWordDefinition;
}

class WidgetWordDefinition : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetWordDefinition(QWidget *parent = nullptr);
    ~WidgetWordDefinition();

private:
    Ui::WidgetWordDefinition *ui;
};

#endif // WIDGETWORDDEFINITION_H
