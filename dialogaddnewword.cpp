#include "dialogaddnewword.h"
#include "ui_dialogaddnewword.h"
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

void DialogAddNewWord::setData(const QString &newWord)
{
    ui->lineEditNewWord->setText(newWord);
}

void DialogAddNewWord::on_buttonBoxConfirm_accepted()
{
    QString word = ui->lineEditNewWord->text();
    QString definition = ui->textEditNewDefinition->toPlainText();
    qDebug() << App::get().addWord(word, definition);
    ui->lineEditNewWord->clear();
    ui->textEditNewDefinition->clear();
}

