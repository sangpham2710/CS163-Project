#include "dialogeditword.h"
#include "ui_dialogeditword.h"
#include <QMessageBox>
#include "App.h"

DialogEditWord::DialogEditWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditWord)
{
    ui->setupUi(this);
    ui->lineEditEditWord->setEnabled(false);
    this->setWindowTitle("Dictionary - Edit Word");
}

DialogEditWord::~DialogEditWord()
{
    delete ui;
}

void DialogEditWord::setDataEditWord(const QString &word, const QString &definition)
{
    ui->lineEditEditWord->setText(word);
    ui->textEditEditDefinition->setText(definition);
}

void DialogEditWord::on_pushButtonAccept_clicked()
{
    QMessageBox::StandardButton confirmAccept = QMessageBox::question(this, "Title", "Are you sure to edit this word ?",
                                                                QMessageBox::Yes | QMessageBox::No);
    if (confirmAccept == QMessageBox::Yes)
    {
        QString word = ui->lineEditEditWord->text();
        QString newDefinition = ui->textEditEditDefinition->toPlainText();
        qDebug() << App::get().editWord(word, newDefinition);
        ui->lineEditEditWord->clear();
        ui->textEditEditDefinition->clear();
        this->close();
    }
}

void DialogEditWord::on_pushButtonReject_clicked()
{
    QMessageBox::StandardButton confirmReject = QMessageBox::question(this, "Title", "Are you sure to stop the process ?",
                                                                QMessageBox::Yes | QMessageBox::No);
    if (confirmReject == QMessageBox::Yes)
    {
        this->close();
    }
}

