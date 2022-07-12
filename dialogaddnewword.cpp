#include "dialogaddnewword.h"
#include "ui_dialogaddnewword.h"
#include <QMessageBox>
#include "App.h"

DialogAddNewWord::DialogAddNewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddNewWord)
{
    ui->setupUi(this);
    ui->lineEditNewWord->setEnabled(false);

}

DialogAddNewWord::~DialogAddNewWord()
{
    delete ui;
}

void DialogAddNewWord::setDataAddNewWord(const QString &newWord)
{
    ui->lineEditNewWord->setText(newWord);
}


void DialogAddNewWord::on_pushButtonAccept_clicked()
{
    QMessageBox::StandardButton confirmAccept = QMessageBox::question(this, "Title", "Are you sure to add this word to your dictionary ?",
                                                                QMessageBox::Yes | QMessageBox::No);
    if (confirmAccept == QMessageBox::Yes)
    {
        QString word = ui->lineEditNewWord->text();
        QString definition = ui->textEditNewDefinition->toPlainText();
        qDebug() << App::get().addWord(word, definition);
        ui->lineEditNewWord->clear();
        ui->textEditNewDefinition->clear();
        this->close();
    }
}

void DialogAddNewWord::on_pushButtonReject_clicked()
{
    QMessageBox::StandardButton confirmReject = QMessageBox::question(this, "Title", "Are you sure to stop the process ?",
                                                                QMessageBox::Yes | QMessageBox::No);
    if (confirmReject == QMessageBox::Yes)
    {
        this->close();
    }
}

