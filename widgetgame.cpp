#include "widgetgame.h"
#include <QMessageBox>
#include "App.h"
#include "ui_widgetgame.h"
#include <QDebug>
QList<QString> play;
QString ans, mode, lang;
int langPreviousIndex, modePreviousIndex;
bool isplay;
int score, questionDone;
WidgetGame::WidgetGame(QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetGame) {
    ui->setupUi(this);
    QList<QString> a = App::get().getListDictionaries(); //load dictionary name to game
    for (int i = 0; i < a.size(); i++) {
        ui->comboBoxChooseLang->addItem(a[i]);
    }
    currentDictName = a[0];
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
    langPreviousIndex=ui->comboBoxChooseLang->currentIndex();
    modePreviousIndex=ui->comboBoxChooseMode->currentIndex();
    isplay=false;
    questionDone=0;
    setDefautAnswerBackGround();
}
WidgetGame::~WidgetGame() {
    delete ui;
}

void WidgetGame::on_pushButtonStartGame_clicked() {
    isplay=true;
    setDefautAnswerBackGround();
    lang = ui->comboBoxChooseLang->currentText();
    mode = ui->comboBoxChooseMode->currentText();
    ui->pushButtonRestart->setEnabled(true);
    ui->pushButtonStartGame->setEnabled(false);
    setAnswerkeyState(true);
    ui->labelScore->setText(QString::number(score));
    ui->labelQuestionCount->setText("0/20");
    App::get().changeDictionary(lang);
    currentDictName = lang;
    QuestionPopUp();
}

void WidgetGame::on_pushButtonContinue_clicked() {
    setDefautAnswerBackGround();
    setAnswerkeyState(true);
    ui->pushButtonContinue->setEnabled(false);
    ui->labelGameState->setText("");
    QuestionPopUp();
}

void WidgetGame::on_pushButtonAnswer1_clicked() {
    questionDone+=1;
    ui->labelQuestionCount->setText (QString::number(questionDone) +"/20");
    if (ans == ui->labelAnswer1->text()) {
        ui->pushButtonAnswer1->setStyleSheet("QPushButton { background-color: green; }\n"
                                             "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        score += 1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText("Correct answer, please click continue");
    } else {
        ui->pushButtonAnswer1->setStyleSheet("QPushButton { background-color: red; }\n"
                                             "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        ui->labelGameState->setText(
            "Wrong answer, please click continue");
        ui->pushButtonContinue->setEnabled(true);
    }
    setAnswerkeyState(false);
    if (questionDone==20) {
        gameFinish();
    }
}

void WidgetGame::on_pushButtonAnswer2_clicked() {
    questionDone+=1;
    ui->labelQuestionCount->setText (QString::number(questionDone) +"/20");
    if (ans == ui->labelAnswer2->text()) {
        ui->pushButtonAnswer2->setStyleSheet("QPushButton { background-color: green; }\n"
                                             "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        score += 1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText("Correct answer, please click continue");
    } else {
        ui->pushButtonAnswer2->setStyleSheet("QPushButton { background-color: red; }\n"
                                             "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        ui->labelGameState->setText(
            "Wrong answer, please click continue");
        ui->pushButtonContinue->setEnabled(true);
        setAnswerkeyState(false);
    }
    setAnswerkeyState(false);
    if (questionDone==20) {
        gameFinish();
    }

}

void WidgetGame::on_pushButtonAnswer3_clicked() {
    questionDone+=1;
    ui->labelQuestionCount->setText (QString::number(questionDone) +"/20");
    if (ans == ui->labelAnswer3->text()) {
        ui->pushButtonAnswer3->setStyleSheet("QPushButton { background-color: green; }\n"
                                             "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        score += 1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText("Correct answer, please click continue");
    } else {
        ui->pushButtonAnswer3->setStyleSheet("QPushButton { background-color: red; }\n"
                                             "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        ui->labelGameState->setText(
            "Wrong answer, please click continue");
        ui->pushButtonContinue->setEnabled(true);
        setAnswerkeyState(false);
    }
    setAnswerkeyState(false);
    if (questionDone==20) {
        gameFinish();
    }
}


void WidgetGame::on_pushButtonAnswer4_clicked() {
    questionDone+=1;
    ui->labelQuestionCount->setText (QString::number(questionDone) +"/20");
    if (ans == ui->labelAnswer4->text()) {
        ui->pushButtonAnswer4->setStyleSheet("QPushButton { background-color: green; }\n"
                                             "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        score += 1;
        ui->labelScore->setText(QString::number(score));
        ui->pushButtonContinue->setEnabled(true);
        ui->labelGameState->setText("Correct answer, please click continue");
    } else {
        ui->pushButtonAnswer4->setStyleSheet("QPushButton { background-color: red; }\n"
                                             "QPushButton:enabled { background-color: rgb(200,0,0); }\n");
        ui->labelGameState->setText("Wrong answer, please click continue");
        ui->pushButtonContinue->setEnabled(true);
        setAnswerkeyState(false);
    }
    setAnswerkeyState(false);
    if (questionDone==20) {
        gameFinish();
    }
}

void WidgetGame::on_pushButtonRestart_clicked() {
    setDefautAnswerBackGround();
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Do you want to restart?", "Your game score will be return to 0",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->pushButtonContinue->setEnabled(false);
        ui->labelScore->setText("");
        ui->labelQuestionEdit->setText("QUESTION");
        ui->labelGameState->setText("");
        score = 0;
        ui->pushButtonStartGame->setEnabled(false);
        setAnswerkeyState(true);
        ui->labelScore->setText(QString::number(score));
        App::get().changeDictionary(lang);
        currentDictName = lang;
        QuestionPopUp();
        ui->labelQuestionCount->setText ("0/20");
        questionDone=0;
    }

}

void WidgetGame::QuestionPopUp()
{
    if (mode == "Play by definition") {
        play = App::get().getDefinitionAnd4Words();
        ans = play[1];
        int ran = rand() % 4;
        ran += 1;
        QString temp = play[1];
        play[1] = play[ran];
        play[ran] = temp;
        ui->labelQuestionEdit->setText(play[0]);
        ui->labelAnswer1->setText(play[1]);
        ui->labelAnswer2->setText(play[2]);
        ui->labelAnswer3->setText(play[3]);
        ui->labelAnswer4->setText(play[4]);
    } else if (mode == "Play by keyword") {
        QList<QString> play = App::get().getWordAnd4Definitions();
        ans = play[1];
        int ran = rand() % 4;
        ran += 1;
        QString temp = play[1];
        play[1] = play[ran];
        play[ran] = temp;
        ui->labelQuestionEdit->setText(play[0]);
        ui->labelAnswer1->setText(play[1]);
        ui->labelAnswer2->setText(play[2]);
        ui->labelAnswer3->setText(play[3]);
        ui->labelAnswer4->setText(play[4]);
    }
}

void WidgetGame::restart(QString lang)
{
    isplay=false;
    App::get().changeDictionary(lang);
    currentDictName = lang;
    score=0;
    questionDone=0;
    ui->labelScore->setText("");
    ui->pushButtonStartGame->setEnabled(true);
    ui->pushButtonContinue->setEnabled(false);
    ui->pushButtonRestart->setEnabled(false);
    ui->labelGameState->setText("");
    ui->labelQuestionEdit->setText("QUESTION");
    ui->labelQuestionCount->setText("");
    setDefautAnswerBackGround();
    ui->labelAnswer1->setText("A");
    ui->labelAnswer2->setText("B");
    ui->labelAnswer3->setText("C");
    ui->labelAnswer4->setText("D");
    setAnswerkeyState(false);
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


void WidgetGame::on_comboBoxChooseLang_currentIndexChanged(int index)
{
    if (ui->comboBoxChooseLang->currentIndex() != langPreviousIndex) {
        if (isplay) {
            QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Title", "You are changing game language \nYour game score will be return to 0",
                QMessageBox::Yes | QMessageBox::No);
            if (reply==QMessageBox::Yes) {
                lang=ui->comboBoxChooseLang->currentText();
                langPreviousIndex=ui->comboBoxChooseLang->currentIndex();
                restart(lang);
            }
            else {
                ui->comboBoxChooseLang->setCurrentIndex(langPreviousIndex);
            }
        }
        else {
            langPreviousIndex=ui->comboBoxChooseLang->currentIndex();
        }
    }
}


void WidgetGame::on_comboBoxChooseMode_currentIndexChanged(int index)
{
    if (ui->comboBoxChooseMode->currentIndex() != modePreviousIndex) {
        if (isplay) {
            QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Title", "You are changing game mode \nYour game score will be return to 0",
                QMessageBox::Yes | QMessageBox::No);
            if (reply==QMessageBox::Yes) {
                mode=ui->comboBoxChooseMode->currentText();
                modePreviousIndex=ui->comboBoxChooseMode->currentIndex();
                restart(lang);
            }
            else {
                ui->comboBoxChooseMode->setCurrentIndex(modePreviousIndex);
            }
        }
        else {
            modePreviousIndex=ui->comboBoxChooseMode->currentIndex();
        }
    }
}

void WidgetGame::gameFinish()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Do you want to restart?", "You have finished the game "  "\n" "Your score is: " + QString::number(score) + "/20" ,
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        restart(lang);
    }
}

void WidgetGame::setDefautAnswerBackGround()
{
    ui->pushButtonAnswer1->setStyleSheet("QPushButton { background-color: rgb(253, 253, 253); }\n"
                                         "QPushButton:enabled { background-color: rgb(253, 253, 253); }\n");
    ui->pushButtonAnswer2->setStyleSheet("QPushButton { background-color: rgb(253, 253, 253); }\n"
                                         "QPushButton:enabled { background-color: rgb(253, 253, 253); }\n");
    ui->pushButtonAnswer3->setStyleSheet("QPushButton { background-color: rgb(253, 253, 253); }\n"
                                         "QPushButton:enabled { background-color: rgb(253, 253, 253); }\n");
    ui->pushButtonAnswer4->setStyleSheet("QPushButton { background-color: rgb(253, 253, 253); }\n"
                                         "QPushButton:enabled { background-color: rgb(253, 253, 253); }\n");
}

void WidgetGame::resetGame()
{
    restart(lang);
}

bool WidgetGame::isPlaying()
{
    return isplay;
}

void WidgetGame::reloadListDictionaries()
{
    ui->comboBoxChooseLang->clear();
    for (auto& dictName : App::get().getListDictionaries()) {
        ui->comboBoxChooseLang->addItem(dictName);
    }
    if (App::get().getListDictionaries().contains(currentDictName)) {
        ui->comboBoxChooseLang->setCurrentText(currentDictName);
    } else {
        currentDictName = App::get().getCurrentDictionaryName();
        ui->comboBoxChooseLang->setCurrentText(currentDictName);
    }
}

const QString &WidgetGame::getCurrentDictName() const
{
    return currentDictName;
}

