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

void WidgetDefinition::setDefinition(const QString &definition)
{
    ui->labelDefinition->setText(definition);
}

void WidgetDefinition::on_pushButtonEditWord_clicked()
{
    dialogEditWord = new DialogEditWord(this);
    dialogEditWord->show();
}


void WidgetDefinition::on_pushButtonSetFavorite_clicked()
{
    if (ui->pushButtonSetFavorite->text() == "Set Favorite")
    {
        //Set Favorite for the word
        ui->pushButtonSetFavorite->setText("Remove Favorite");

    }
    else
    {
        //Remove favorite for the word
        ui->pushButtonSetFavorite->setText("Set Favorite");
    }
}


void WidgetDefinition::on_pushButtonRemoveWord_clicked()
{
    QMessageBox::StandardButton confirm = QMessageBox::question(this, "Title", "Are you sure to remove this word", QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes)
    {

    }
    else
    {

    }

}

