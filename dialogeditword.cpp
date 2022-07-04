#include "dialogeditword.h"
#include "ui_dialogeditword.h"

DialogEditWord::DialogEditWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditWord)
{
    ui->setupUi(this);
    ui->lineEditEditWord->setText("Word Name");
    ui->lineEditEditWord->setEnabled(false);
}

DialogEditWord::~DialogEditWord()
{
    delete ui;
}
