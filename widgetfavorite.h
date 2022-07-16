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
    void clearLineEditSearchFavorite();
    void clearListWidgetFavorite();
    void removeCurrentTabFavorite();
    void reloadDefinitionTabs();
    void reloadListWidgetFavorite();

private slots:


    void on_listWidgetFavoriteWord_itemDoubleClicked(QListWidgetItem *item);

    void on_tabWidgetFavoriteWord_tabCloseRequested(int index);

    void on_lineEditSearchFavorite_textChanged(const QString &arg1);

private:
    Ui::WidgetFavorite *ui;
};

#endif // widgetfavorite_H
