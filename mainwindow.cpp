#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "widgetsearch.h"
#include "widgetfavourite.h"
#include "widgetgame.h"

#include "App.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidgetDictionary->clear();
    ui->tabWidgetDictionary->addTab(new WidgetSearch(), QString("Search"));
    ui->tabWidgetDictionary->addTab(new WidgetFavourite(), QString("Favourite"));
    ui->tabWidgetDictionary->addTab(new WidgetGame(), QString("Game"));

    App::get();


}

MainWindow::~MainWindow()
{
    delete ui;
}





