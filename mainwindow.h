#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgetsearch.h"
#include "widgetfavorite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_tabWidgetDictionary_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    WidgetSearch *widgetSearch;
    WidgetFavorite *widgetFavorite;
};
#endif // MAINWINDOW_H
