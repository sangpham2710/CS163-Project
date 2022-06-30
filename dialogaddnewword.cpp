#include "dialogaddnewword.h"
#include "ui_dialogaddnewword.h"

DialogAddNewWord::DialogAddNewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddNewWord)
{
    ui->setupUi(this);
    this->setFixedHeight(180);
    this->setFixedWidth(360);
    this->setWindowTitle("Add New Word - Dictionary");

}

DialogAddNewWord::~DialogAddNewWord()
{
    delete ui;
}
