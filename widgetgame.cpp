#include "widgetgame.h"
#include <QMessageBox>
#include "App.h"
#include "ui_widgetgame.h"
QList<QString> play;
QString ans, mode, lang;
int score;
WidgetGame::WidgetGame(QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetGame) {
    ui->setupUi(this);
    QList<QString> a = App::get().getListDictionaries(); //load dictionary name to game
    for (int i = 0; i < a.size(); i++) {
        ui->comboBoxChooseLang->addItem(a[i]);
    }
    ui->comboBoxChooseMode->addItem("Play by definition"); //load game mode
    ui->comboBoxChooseMode->addItem("Play by keyword");
    ui->pushButtonContinue->setEnabled(false);
    ui->pushButtonRestart->setEnabled(false);
    setAnswerkeyState(false);
    play.resize(5);
    play[0] = "";
    play[1] = "";
    play[2] = "";
    play[3] = "";
    play[4] = "";
    score = 0;
}
WidgetGame::~WidgetGame() {
    delete ui;
}

void WidgetGame::on_pushButtonStartGame_clicked() {
    lang = ui->comboBoxChooseLang->currentText();
    mode = ui->comboBoxChooseMode->currentText();
    ui->pushButtonRestart->setEnabled(true);
    ui->pushButtonStartGame->setEnabled(false);
    setAnswerkeyState(true);
    ui->labelScore->setText(QString::number(score));
    App::get().changeDictionary(lang);
    QuestionPopUp();
}

void WidgetGame::on_pushButtonContinue_clicked() {
    ui->pushButtonContinue->setEnabled(false);
    ui->labelGameState->setText("");
    QuestionPopUp();
}

void WidgetGame::on_pushButtonAnswer1_clicked() {
    if (ans == ui->pushButtonAnswer1->text()) {
        score += 1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText("Correct answer, please click continue");
    } else {
        ui->labelGameState->setText(
            "Wrong answer, please click restart");
        setAnswerkeyState(false);
    }
}

void WidgetGame::on_pushButtonAnswer2_clicked() {
    if (ans == ui->pushButtonAnswer2->text()) {
        score += 1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText("Correct answer, please click continue");
    } else {
        ui->labelGameState->setText(
            "Wrong answer, please click restart");
        setAnswerkeyState(false);
    }
}

void WidgetGame::on_pushButtonAnswer3_clicked() {
    if (ans == ui->pushButtonAnswer3->text()) {
        score += 1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText("Correct answer, please click continue");
    } else {
        ui->labelGameState->setText(
            "Wrong answer, please click restart");
        setAnswerkeyState(false);
    }
}


void WidgetGame::on_pushButtonAnswer4_clicked() {
    if (ans == ui->pushButtonAnswer4->text()) {
        score += 1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText("Correct answer, please click continue");
    } else {
        ui->labelGameState->setText("Wrong answer, please click restart");
        setAnswerkeyState(false);
    }
}

void WidgetGame::on_pushButtonRestart_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Do you want to restart?", "Your game score will be return to 0",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->pushButtonContinue->setEnabled(false);
        ui->labelScore->setText("");
        ui->labelQuestionEdit->setText("");
        ui->labelGameState->setText("");
        score = 0;
        ui->pushButtonStartGame->setEnabled(false);
        setAnswerkeyState(true);
        ui->labelScore->setText(QString::number(score));
        App::get().changeDictionary(lang);
        QuestionPopUp();
    }
}

void WidgetGame::QuestionPopUp()
{
    if (mode == "Play by defination") {
        play = App::get().getDefinitionAnd4Words();
        ans = play[1];
        int ran = rand() % 4;
        ran += 1;
        QString temp = play[1];
        play[1] = play[ran];
        play[ran] = play[1];
        ui->labelQuestionEdit->setText(play[0]);
        ui->pushButtonAnswer1->setText(play[1]);
        ui->pushButtonAnswer2->setText(play[2]);
        ui->pushButtonAnswer3->setText(play[3]);
        ui->pushButtonAnswer4->setText(play[4]);
    } else if (mode == "Play by keyword") {
        QList<QString> play = App::get().getWordAnd4Definitions();
        ans = play[1];
        int ran = rand() % 4;
        ran += 1;
        QString temp = play[1];
        play[1] = play[ran];
        play[ran] = play[1];
        ui->labelQuestionEdit->setText(play[0]);
        ui->pushButtonAnswer1->setText(play[1]);
        ui->pushButtonAnswer2->setText(play[2]);
        ui->pushButtonAnswer3->setText(play[3]);
        ui->pushButtonAnswer4->setText(play[4]);
    }
}

void WidgetGame::setAnswerkeyState (bool set)
{
    if (set) {
        ui->pushButtonAnswer1->setEnabled(true);
        ui->pushButtonAnswer2->setEnabled(true);
        ui->pushButtonAnswer3->setEnabled(true);
        ui->pushButtonAnswer4->setEnabled(true);
    }
    else {
        ui->pushButtonAnswer1->setEnabled(false);
        ui->pushButtonAnswer2->setEnabled(false);
        ui->pushButtonAnswer3->setEnabled(false);
        ui->pushButtonAnswer4->setEnabled(false);
    }
}

void WidgetGame::on_comboBoxChooseLang_currentTextChanged(const QString &arg1)
{

}

