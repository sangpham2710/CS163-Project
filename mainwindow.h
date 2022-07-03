#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>

#include "App.h"
#include "Trie.h"
#include "WordDefinitionWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:

    void on_pushButtonAddWord_clicked();

    void on_pushButtonEditWord_clicked();

    void on_lineEditFind_returnPressed();

    void on_comboBoxDictionary_currentTextChanged(const QString &arg1);

    void on_listWidgetSearchResult_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButtonReset_clicked();

    void on_lineEditFindPrefix_textChanged(const QString &arg1);

    void on_tabWidgetWordDefinition_tabCloseRequested(int index);

   private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
