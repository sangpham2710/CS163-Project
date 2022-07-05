#ifndef widgetfavourite_H
#define widgetfavourite_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class widgetfavourite;
}

class widgetfavourite : public QWidget
{
    Q_OBJECT

public:
    explicit widgetfavourite(QWidget *parent = nullptr);
    ~widgetfavourite();

private slots:


    void on_listWidgetFavouriteLWord_itemDoubleClicked(QListWidgetItem *item);

    void on_tabWidgetFavouriteWord_tabCloseRequested(int index);

private:
    Ui::widgetfavourite *ui;
};

#endif // widgetfavourite_H
