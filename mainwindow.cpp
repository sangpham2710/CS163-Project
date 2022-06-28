#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxSearch->addItem("Eng - Eng");
    ui->comboBoxSearch->addItem("Viet - Eng");
    ui->comboBoxSearch->addItem("Eng - Viet");
    ui->comboBoxSearch->addItem("Slang");
    ui->comboBoxSearch->addItem("Emoji");
    ui->comboBoxSearch->addItem("Favourite");
    this->setFixedHeight(544);
    this->setFixedWidth(960);
}

MainWindow::~MainWindow()
{
    delete ui;
}


