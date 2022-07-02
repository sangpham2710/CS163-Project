#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>

#include "Trie.h"
#include "App.h"
#include "WordDefinitionWidget.h"

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

    void on_pushButtonAddWord_clicked();

    void on_pushButtonEditWord_clicked();

    void on_lineEditFindPrefix_returnPressed();

    void on_lineEditFind_returnPressed();

    void on_comboBoxDictionary_currentTextChanged(const QString &arg1);

    void on_listWidgetSearchResult_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
