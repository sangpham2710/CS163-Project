#include "dialogeditword.h"
#include "ui_dialogeditword.h"
#include "App.h"

DialogEditWord::DialogEditWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditWord)
{
    ui->setupUi(this);
    ui->lineEditEditWord->setEnabled(false);
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

void DialogEditWord::on_DialogEditWord_accepted()
{
    QString word = ui->lineEditEditWord->text();
    QString newDefinition = ui->textEditEditDefinition->toPlainText();
    qDebug() << App::get().editWord(word, newDefinition);
    ui->lineEditEditWord->clear();
    ui->textEditEditDefinition->clear();
}

