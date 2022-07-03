#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H
#include <QDialog>
namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{

    Q_OBJECT

public:
    explicit GameDialog(QWidget *parent = nullptr, QString lang = "", QString state = "");
    ~GameDialog();

private slots:
    void on_Game_Quit_Button_clicked();
    void on_pushButton_clicked();
private:
    Ui::GameDialog *ui;
    QString state;
    QString lang;
};

#endif // GAME_DIALOG_H
