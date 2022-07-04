#include "widgetdefinition.h"
#include "ui_widgetdefinition.h"
#include <QMessageBox>

WidgetDefinition::WidgetDefinition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetDefinition)
{
    ui->setupUi(this);
}

WidgetDefinition::~WidgetDefinition()
{
    delete ui;
}


void WidgetDefinition::on_pushButtonEditWord_clicked()
{
    dialogEditWord = new DialogEditWord(this);
    dialogEditWord->show();
}


void WidgetDefinition::on_pushButtonSetFavourite_clicked()
{
    if (ui->pushButtonSetFavourite->text() == "Set Favourite")
    {
        //Set Favourite for the word
        ui->pushButtonSetFavourite->setText("Remove Favourite");

    }
    else
    {
        //Remove favourite for the word
        ui->pushButtonSetFavourite->setText("Set Favourite");
    }
}

