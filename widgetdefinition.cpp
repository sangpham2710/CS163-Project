#include "widgetdefinition.h"
#include "ui_widgetdefinition.h"
#include <QMessageBox>
#include "App.h"

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

void WidgetDefinition::setWord(const QString &word)
{
    ui->labelWord->setText(word);
}

void WidgetDefinition::openDialogEditWord()
{
    QString word = ui->labelWord->text();
    QString definition = ui->labelDefinition->text();
    DialogEditWord dialogEditWord;
    dialogEditWord.setDataEditWord(word, definition);
    dialogEditWord.exec();
}

void WidgetDefinition::on_pushButtonEditWord_clicked()
{
    QMessageBox::StandardButton confirm = QMessageBox::question(this, "Title", "Do you want to edit this word",
                                                                QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes)
    {
        openDialogEditWord();
    }
}

void WidgetDefinition::setFavorite(const QString &word)
{
    bool state = App::get().isWordInFavorite(word);
    if (state)
    {
        ui->pushButtonSetFavorite->setText("Unlike");
    }
    else
    {
        ui->pushButtonSetFavorite->setText("Like");
    }
}

void WidgetDefinition::on_pushButtonSetFavorite_clicked()
{

    QString word = ui->labelWord->text();
    bool state = App::get().isWordInFavorite(word);
    if (state)
    {
        App::get().removeWordFromFavorite(word);
        ui->pushButtonSetFavorite->setText("Like");
    }
    else
    {
        App::get().addWordToFavorite(word);
        ui->pushButtonSetFavorite->setText("Unike");
    }
}



void WidgetDefinition::on_pushButtonRemoveWord_clicked()
{
    QMessageBox::StandardButton confirm = QMessageBox::question(this, "Title", "Are you sure to remove this word",
                                                                QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes)
    {
        QString removeWord = ui->labelWord->text();
        App::get().removeWord(removeWord);
    }

}

