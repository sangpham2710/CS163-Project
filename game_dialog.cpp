#include "game_dialog.h"
#include "ui_game_dialog.h"
#include <QMessageBox>
#include <QDebug>
Game_Dialog::Game_Dialog(QWidget *parent, QString lang, QString state) :
    QDialog(parent),
    ui(new Ui::Game_Dialog), lang(lang), state(state)
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
    ui->Dif_Chosen->setText (result);
    ui->Lang_Chosen->setText (lang);
}

Game_Dialog::~Game_Dialog()
{
    delete ui;
}


void Game_Dialog::on_Game_Quit_Button_clicked()
{
    close();
}


void Game_Dialog::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question (this, "Restart", "Do you want to restart?" , QMessageBox::Yes| QMessageBox::No);
    if (reply==QMessageBox::Yes);
}


