#ifndef WIDGETFAVORITEDEFINITION_H
#define WIDGETFAVORITEDEFINITION_H

#include <QWidget>
#include "widgetfavorite.h"

namespace Ui {
class WidgetFavoriteDefinition;
}

class WidgetFavoriteDefinition : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFavoriteDefinition(QWidget *parent = nullptr);
    ~WidgetFavoriteDefinition();
    void setWord(const QString &word);
    void setDefinition(const QString &definition);
    void setFavoriteState(const QString &word);
    const QString& getWord() const;
private slots:
    void on_pushButtonSetFavorite_clicked();

private:
    Ui::WidgetFavoriteDefinition *ui;
    WidgetFavorite *widgetFavorite;
};

#endif // WIDGETFAVORITEDEFINITION_H
