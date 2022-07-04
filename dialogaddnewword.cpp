#include "dialogaddnewword.h"
#include "ui_dialogaddnewword.h"

DialogAddNewWord::DialogAddNewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddNewWord)
{
    ui->setupUi(this);
}

DialogAddNewWord::~DialogAddNewWord()
{
    delete ui;
}
