#include "dialogeditword.h"
#include "ui_dialogeditword.h"

DialogEditWord::DialogEditWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditWord)
{
    ui->setupUi(this);
    this->setFixedWidth(360);
    this->setFixedHeight(240);
    this->setWindowTitle("Edit Word - Dictionary");

    ui->lineEditWord->setText("Word Name");
    ui->lineEditWord->setEnabled(false);
    ui->lineEditCurrentDefinition->setText("Word Definition");
    ui->lineEditCurrentDefinition->setEnabled(false);
}

DialogEditWord::~DialogEditWord()
{
    delete ui;
}


