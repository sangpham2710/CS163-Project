#ifndef WIDGETFAVOURITELIST_H
#define WIDGETFAVOURITELIST_H

#include <QWidget>

namespace Ui {
class WidgetFavouriteList;
}

class WidgetFavouriteList : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFavouriteList(QWidget *parent = nullptr);
    ~WidgetFavouriteList();

private slots:

    void on_tabWidgetFavouriteWord_tabBarDoubleClicked(int index);

private:
    Ui::WidgetFavouriteList *ui;
};

#endif // WIDGETFAVOURITELIST_H
