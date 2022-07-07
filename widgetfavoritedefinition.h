#ifndef WIDGETFAVORITEDEFINITION_H
#define WIDGETFAVORITEDEFINITION_H

#include <QWidget>

namespace Ui {
class WidgetFavoriteDefinition;
}

class WidgetFavoriteDefinition : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFavoriteDefinition(QWidget *parent = nullptr);
    ~WidgetFavoriteDefinition();

private:
    Ui::WidgetFavoriteDefinition *ui;
};

#endif // WIDGETFAVORITEDEFINITION_H
