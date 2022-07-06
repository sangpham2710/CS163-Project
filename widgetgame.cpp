#include "widgetgame.h"
#include "ui_widgetgame.h"

WidgetGame::WidgetGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGame)
{
    ui->setupUi(this);
}

WidgetGame::~WidgetGame()
{
    delete ui;
}
