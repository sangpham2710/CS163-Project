#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialogaddnewword.h>
#include <dialogeditword.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonEdit_clicked();

    void on_Game_start_clicked();

private:
    Ui::MainWindow *ui;
    DialogAddNewWord *dialogAddNewWord;
    DialogEditWord *dialogEditWord;

};
#endif // MAINWINDOW_H
