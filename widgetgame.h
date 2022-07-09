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

private:
    Ui::WidgetGame *ui;
};

#endif // WIDGETGAME_H
