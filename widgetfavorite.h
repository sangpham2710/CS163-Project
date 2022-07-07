#ifndef WIDGETFavorite_H
#define WIDGETFavorite_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class WidgetFavorite;
}

class WidgetFavorite : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFavorite(QWidget *parent = nullptr);
    ~WidgetFavorite();


private slots:


    void on_listWidgetFavoriteWord_itemDoubleClicked(QListWidgetItem *item);

    void on_tabWidgetFavoriteWord_tabCloseRequested(int index);

private:
    Ui::WidgetFavorite *ui;
};

#endif // widgetfavorite_H
