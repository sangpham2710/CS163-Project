#include "dialogaddnewword.h"
#include "ui_dialogaddnewword.h"

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
