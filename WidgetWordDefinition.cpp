#include "WidgetWordDefinition.h"
#include "ui_WidgetWordDefinition.h"

WidgetWordDefinition::WidgetWordDefinition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetWordDefinition)
{
    ui->setupUi(this);
}

WidgetWordDefinition::~WidgetWordDefinition()
{
    delete ui;
}
