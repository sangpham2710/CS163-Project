#include "widgetgame.h"
#include "ui_widgetgame.h"
#include "App.h"
#include <QMessageBox>
QList <QString> play;
QString ans;
int score;
WidgetGame::WidgetGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetGame)
{
    ui->setupUi(this);
    ui->comboBoxChooseLang->addItem("");
    QList<QString> a= App::get().getListDictionaries();
    for (int i=0;i<a.size();i++) {
        ui->comboBoxChooseLang->addItem(a[i]);
    }
    ui->comboBoxChooseMode->addItem ("");
    ui->comboBoxChooseMode->addItem ("Play by defination");
    ui->comboBoxChooseMode->addItem ("Play by keyword");
    ui->pushButtonContinue->setEnabled(false);
    ui->pushButtonRestart->setEnabled (false);
    ui->pushButtonAnswer1->setEnabled(false);
    ui->pushButtonAnswer2->setEnabled(false);
    ui->pushButtonAnswer3->setEnabled(false);
    ui->pushButtonAnswer4->setEnabled(false);
    play.resize(5);
    play[0]="Question: ";
    play[1]="Answer1";
    play[2]="Answer2";
    play[3]="Answer3";
    play[4]="Answer4";
    score=0;
}
WidgetGame::~WidgetGame()
{
    delete ui;
}

void WidgetGame::on_pushButtonStartGame_clicked()
{
    QString a="";
    QString lang=ui->comboBoxChooseLang->currentText();
    QString mode=ui->comboBoxChooseMode->currentText();
    if (lang==a and mode== a) {
        QMessageBox::warning(this, "Eror", "You haven't select game mode and language");
    }
    else if (mode==a) {
        QMessageBox::warning(this, "Eror", "You haven't select game mode");
    }
    else if (lang==a) {
        QMessageBox::warning(this, "Eror", "You haven't select game language");
    }
    else {
        ui->comboBoxChooseLang->setEnabled(false);
        ui->comboBoxChooseMode->setEnabled (false);
        ui->pushButtonRestart->setEnabled(true);
        ui->pushButtonStartGame->setEnabled(false);
        ui->pushButtonAnswer1->setEnabled(true);
        ui->pushButtonAnswer2->setEnabled(true);
        ui->pushButtonAnswer3->setEnabled(true);
        ui->pushButtonAnswer4->setEnabled(true);
        ui->labelScore->setText(QString::number(score));
        App::get().changeDictionary(lang);
        if (mode== "Play by defination") {
                play = App::get().getDefinitionAnd4Words();
                ans=play[1];
                int ran=rand() %4;
                ran+=1;
                QString temp=play[1];
                play[1]=play[ran];
                play[ran]=play[1];
                ui->labelQuestionEdit->setText (play[0]);
                ui->pushButtonAnswer1->setText (play[1]);
                ui->pushButtonAnswer2->setText (play[2]);
                ui->pushButtonAnswer3->setText (play[3]);
                ui->pushButtonAnswer4->setText (play[4]);
        }
        else if (mode=="Play by keyword") {
            QList<QString> play = App::get().getWordAnd4Definitions();
            ans=play[1];
            int ran=rand() %4;
            ran+=1;
            QString temp=play[1];
            play[1]=play[ran];
            play[ran]=play[1];
            ui->labelQuestionEdit->setText (play[0]);
            ui->pushButtonAnswer1->setText (play[1]);
            ui->pushButtonAnswer2->setText (play[2]);
            ui->pushButtonAnswer3->setText (play[3]);
            ui->pushButtonAnswer4->setText (play[4]);
        }
    }
}



void WidgetGame::on_pushButtonReset_clicked()
{
    QMessageBox::StandardButton reply= QMessageBox::question(this, "Do you want to reset?", "Your game score will be return to 0", QMessageBox::Yes | QMessageBox::No);
    if (reply== QMessageBox::Yes) {
        ui->pushButtonContinue->setEnabled(false);
        ui->pushButtonStartGame->setEnabled(true);
        ui->labelScore->setText ("");
        ui->pushButtonAnswer1->setText ("Answer1");
        ui->pushButtonAnswer2->setText ("Answer2");
        ui->pushButtonAnswer3->setText ("Answer3");
        ui->pushButtonAnswer4->setText ("Answer4");
        ui->comboBoxChooseLang->setCurrentIndex(0);
        ui->comboBoxChooseMode->setCurrentIndex(0);
        ui->labelQuestionEdit->setText("");
        ui->pushButtonAnswer1->setEnabled(false);
        ui->pushButtonAnswer2->setEnabled(false);
        ui->pushButtonAnswer3->setEnabled(false);
        ui->pushButtonAnswer4->setEnabled(false);
        ui->labelGameState->setText ("");
        score=0;
        ui->comboBoxChooseLang->setEnabled(true);
        ui->comboBoxChooseMode->setEnabled(true);
        ui->pushButtonRestart->setEnabled(false);
    }
}

void WidgetGame::on_pushButtonContinue_clicked()
{
    ui->pushButtonContinue->setEnabled(false);
    QString lang=ui->comboBoxChooseLang->currentText();
    QString mode=ui->comboBoxChooseMode->currentText();
    ui->labelGameState->setText ("");
    if (mode== "Play by defination") {
            play = App::get().getDefinitionAnd4Words();
            ans=play[1];
            int ran=rand() %4;
            ran+=1;
            QString temp=play[1];
            play[1]=play[ran];
            play[ran]=play[1];
            ui->labelQuestionEdit->setText (play[0]);
            ui->pushButtonAnswer1->setText (play[1]);
            ui->pushButtonAnswer2->setText (play[2]);
            ui->pushButtonAnswer3->setText (play[3]);
            ui->pushButtonAnswer4->setText (play[4]);
    }
    else if (mode=="Play by keyword") {
        QList<QString> play = App::get().getWordAnd4Definitions();
        ans=play[1];
        int ran=rand() %4;
        ran+=1;
        QString temp=play[1];
        play[1]=play[ran];
        play[ran]=play[1];
        ui->labelQuestionEdit->setText (play[0]);
        ui->pushButtonAnswer1->setText (play[1]);
        ui->pushButtonAnswer2->setText (play[2]);
        ui->pushButtonAnswer3->setText (play[3]);
        ui->pushButtonAnswer4->setText (play[4]);
    }
}

void WidgetGame::on_pushButtonAnswer1_clicked()
{
    if (ans==ui->pushButtonAnswer1->text()) {
        score+=1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText ("Correct answer, please click continue");
    }
    else {
        ui->labelGameState->setText ("Wrong answer, please click reset or restart");
        ui->pushButtonAnswer1->setEnabled(false);
        ui->pushButtonAnswer2->setEnabled(false);
        ui->pushButtonAnswer3->setEnabled(false);
        ui->pushButtonAnswer4->setEnabled(false);
    }
}

void WidgetGame::on_pushButtonAnswer2_clicked()
{
    if (ans == ui->pushButtonAnswer2->text()) {
        score+=1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText ("Correct answer, please click continue");
    }
    else {
        ui->labelGameState->setText ("Wrong answer, please click reset or restart");
        ui->pushButtonAnswer1->setEnabled(false);
        ui->pushButtonAnswer2->setEnabled(false);
        ui->pushButtonAnswer3->setEnabled(false);
        ui->pushButtonAnswer4->setEnabled(false);
    }
}

void WidgetGame::on_pushButtonAnswer3_clicked()
{
    if (ans == ui->pushButtonAnswer3->text()) {
        score+=1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText ("Correct answer, please click continue");
    }
    else {
        ui->labelGameState->setText ("Wrong answer, please click reset or restart");
        ui->pushButtonAnswer1->setEnabled(false);
        ui->pushButtonAnswer2->setEnabled(false);
        ui->pushButtonAnswer3->setEnabled(false);
        ui->pushButtonAnswer4->setEnabled(false);
    }
}


void WidgetGame::on_pushButtonAnswer4_clicked()
{
    if (ans == ui->pushButtonAnswer4->text()) {
        score+=1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText ("Correct answer, please click continue");
    }
    else {
        ui->labelGameState->setText ("Wrong answer, please click reset or restart");
        ui->pushButtonAnswer1->setEnabled(false);
        ui->pushButtonAnswer2->setEnabled(false);
        ui->pushButtonAnswer3->setEnabled(false);
        ui->pushButtonAnswer4->setEnabled(false);
    }
}

void WidgetGame::on_pushButtonRestart_clicked()
{
    QMessageBox::StandardButton reply= QMessageBox::question(this, "Do you want to restart?", "Your game score will be return to 0", QMessageBox::Yes | QMessageBox::No);
    if (reply== QMessageBox::Yes) {
        ui->pushButtonContinue->setEnabled(false);
        ui->pushButtonStartGame->setEnabled(true);
        ui->labelScore->setText ("");
        ui->pushButtonAnswer1->setText ("Answer1");
        ui->pushButtonAnswer2->setText ("Answer2");
        ui->pushButtonAnswer3->setText ("Answer3");
        ui->pushButtonAnswer4->setText ("Answer4");
        ui->labelQuestionEdit->setText("");
        ui->pushButtonAnswer1->setEnabled(false);
        ui->pushButtonAnswer2->setEnabled(false);
        ui->pushButtonAnswer3->setEnabled(false);
        ui->pushButtonAnswer4->setEnabled(false);
        ui->labelGameState->setText ("");
        score=0;
        ui->pushButtonStartGame->setEnabled(false);
        ui->pushButtonAnswer1->setEnabled(true);
        ui->pushButtonAnswer2->setEnabled(true);
        ui->pushButtonAnswer3->setEnabled(true);
        ui->pushButtonAnswer4->setEnabled(true);
        ui->labelScore->setText(QString::number(score));
        QString lang=ui->comboBoxChooseLang->currentText();
        QString mode=ui->comboBoxChooseMode->currentText();
        App::get().changeDictionary(lang);
        if (mode== "Play by defination") {
                play = App::get().getDefinitionAnd4Words();
                ans=play[1];
                int ran=rand() %4;
                ran+=1;
                QString temp=play[1];
                play[1]=play[ran];
                play[ran]=play[1];
                ui->labelQuestionEdit->setText (play[0]);
                ui->pushButtonAnswer1->setText (play[1]);
                ui->pushButtonAnswer2->setText (play[2]);
                ui->pushButtonAnswer3->setText (play[3]);
                ui->pushButtonAnswer4->setText (play[4]);
        }
        else if (mode=="Play by keyword") {
            QList<QString> play = App::get().getWordAnd4Definitions();
            ans=play[1];
            int ran=rand() %4;
            ran+=1;
            QString temp=play[1];
            play[1]=play[ran];
            play[ran]=play[1];
            ui->labelQuestionEdit->setText (play[0]);
            ui->pushButtonAnswer1->setText (play[1]);
            ui->pushButtonAnswer2->setText (play[2]);
            ui->pushButtonAnswer3->setText (play[3]);
            ui->pushButtonAnswer4->setText (play[4]);
        }
    }
}

