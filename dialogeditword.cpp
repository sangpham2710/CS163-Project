#include "DialogEditWord.h"
#include "ui_DialogEditWord.h"

DialogEditWord::DialogEditWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditWord)
{
    ui->setupUi(this);
    //this->setFixedSize(360,382);
    this->setWindowTitle("Edit Word - Dictionary");
    ui->lineEditWord->setText("New Word");
    ui->lineEditWord->setEnabled(false);
}

DialogEditWord::~DialogEditWord()
{
    delete ui;
}


