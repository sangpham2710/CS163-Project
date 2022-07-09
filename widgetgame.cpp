#include "widgetgame.h"
#include "ui_widgetgame.h"
#include "App.h"
WidgetGame::WidgetGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGame)
{
    ui->setupUi(this);
    QList<QString> a= getListDictionaries();
}

WidgetGame::~WidgetGame()
{
    delete ui;
}

void WidgetGame::on_pushButtonStartGame_clicked()
{

}

