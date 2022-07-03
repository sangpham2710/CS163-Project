#include "GameDialog.h"
#include "ui_GameDialog.h"
#include <QMessageBox>
#include <QDebug>
GameDialog::GameDialog(QWidget *parent, QString lang, QString state) :
    QDialog(parent),
    ui(new Ui::GameDialog), lang(lang), state(state)
{
    ui->setupUi(this);
    int i=0;
    QString a=" ";
    while (state[i] != a[0]) {
        i++;
    }
    QString result;
    result.resize(i);
    for (int j=0;j<i;j++) {
        result[j]=state[j];
    }
    ui->DifChosen->setText (result);
    ui->LangChosen->setText (lang);
}

GameDialog::~GameDialog()
{
    delete ui;
}


void GameDialog::on_Game_Quit_Button_clicked()
{
    close();
}


void GameDialog::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question (this, "Restart", "Do you want to restart?" , QMessageBox::Yes| QMessageBox::No);
    if (reply==QMessageBox::Yes);
}


