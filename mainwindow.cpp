#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "widgetsearch.h"
#include "widgetfavourite.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidgetDictionary->clear();
    ui->tabWidgetDictionary->addTab(new WidgetSearch(), QString("Search").arg(ui->tabWidgetDictionary->count() + 1));
    ui->tabWidgetDictionary->addTab(new widgetfavourite(), QString("Favourite").arg(ui->tabWidgetDictionary->count() + 1));



}

MainWindow::~MainWindow()
{
    delete ui;
}





