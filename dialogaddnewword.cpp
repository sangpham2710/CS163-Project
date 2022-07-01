#include "DialogAddNewWord.h"
#include "ui_DialogAddNewWord.h"

DialogAddNewWord::DialogAddNewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddNewWord)
{
    ui->setupUi(this);
    //this->setFixedSize(360,360);
    this->setWindowTitle("Add New Word - Dictionary");


}

DialogAddNewWord::~DialogAddNewWord()
{
    delete ui;
}
