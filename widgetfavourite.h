#ifndef WIDGETFAVOURITE_H
#define WIDGETFAVOURITE_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class WidgetFavourite;
}

class WidgetFavourite : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFavourite(QWidget *parent = nullptr);
    ~WidgetFavourite();

private slots:


    void on_listWidgetFavouriteWord_itemDoubleClicked(QListWidgetItem *item);

    void on_tabWidgetFavouriteWord_tabCloseRequested(int index);

private:
    Ui::WidgetFavourite *ui;
};

#endif // widgetfavourite_H
