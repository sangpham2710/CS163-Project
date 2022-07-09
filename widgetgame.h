#ifndef WIDGETGAME_H
#define WIDGETGAME_H

#include <QWidget>

namespace Ui {
class WidgetGame;
}

class WidgetGame : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetGame(QWidget *parent = nullptr);
    ~WidgetGame();

private slots:
    void on_pushButtonStartGame_clicked();


    void on_pushButtonReset_clicked();


    void on_pushButtonContinue_clicked();

    void on_pushButtonAnswer1_clicked();

    void on_pushButtonAnswer2_clicked();

    void on_pushButtonAnswer3_clicked();

    void on_pushButtonAnswer4_clicked();

    void on_pushButtonRestart_clicked();

private:
    Ui::WidgetGame *ui;
};

#endif // WIDGETGAME_H
