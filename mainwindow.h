#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Trie.h"

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
    void on_insertLineEdit_returnPressed();

    void on_findLineEdit_returnPressed();

    void on_findPrefixLineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    Trie trie;
};
#endif // MAINWINDOW_H
