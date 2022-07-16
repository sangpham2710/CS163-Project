#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgetsearch.h"
#include "widgetfavorite.h"
#include "widgetgame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Tab {
    SEARCH = 0, FAVORITE = 1, GAME = 2
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_tabWidgetDictionary_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
    WidgetSearch *widgetSearch;
    WidgetFavorite *widgetFavorite;
    WidgetGame *widgetGame;
};
#endif // MAINWINDOW_H
