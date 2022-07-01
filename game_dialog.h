#ifndef GAME_DIALOG_H
#define GAME_DIALOG_H
#include <QDialog>
namespace Ui {
class Game_Dialog;
}

class Game_Dialog : public QDialog
{

    Q_OBJECT

public:
    explicit Game_Dialog(QWidget *parent = nullptr, QString lang = "", QString state = "");
    ~Game_Dialog();


    const QString &getState() const;
    void setState(const QString &newState);
    const QString &getLang() const;
    void setLang(const QString &newLang);

private slots:
    void on_Game_Quit_Button_clicked();
    void on_pushButton_clicked();
private:
    Ui::Game_Dialog *ui;
    QString state;
    QString lang;
};

#endif // GAME_DIALOG_H
