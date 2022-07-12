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
    void setWord(QString &word);
    void setDefinition(QString &definition);
private:
    Ui::WidgetFavoriteDefinition *ui;
};

#endif // WIDGETFAVORITEDEFINITION_H
