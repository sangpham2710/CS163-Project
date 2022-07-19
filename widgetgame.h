#ifndef WIDGETGAME_H
#define WIDGETGAME_H

#include <QWidget>
#include <QString>

namespace Ui {
class WidgetGame;
}

class WidgetGame : public QWidget {
    Q_OBJECT

   public:
    explicit WidgetGame(QWidget *parent = nullptr);
    ~WidgetGame();

    const QString &getCurrentDictName() const;
    void resetGame();
    bool isPlaying();
    void reloadListDictionaries();

private slots:
    void on_pushButtonStartGame_clicked();

    void on_pushButtonContinue_clicked();

    void on_pushButtonAnswer1_clicked();

    void on_pushButtonAnswer2_clicked();

    void on_pushButtonAnswer3_clicked();

    void on_pushButtonAnswer4_clicked();

    void on_pushButtonRestart_clicked();

    void QuestionPopUp ();

    void restart (QString lang);

    void setAnswerkeyState (bool set);

    void on_comboBoxChooseLang_currentIndexChanged(int index);

    void on_comboBoxChooseMode_currentIndexChanged(int index);

    void gameFinish();

    void setDefautAnswerBackGround();

private:
    Ui::WidgetGame *ui;
    QString currentDictName;
};

#endif  // WIDGETGAME_H
