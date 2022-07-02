#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <typeinfo>
#include <QListWidgetItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    App::get();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_pushButtonAddWord_clicked()
//{
//    QString word = ui->lineEditAddWord->text();
//    QString definition = ui->textEditAddWordDefinition->toPlainText();
//    App::get().addWord(word, definition);
//}


//void MainWindow::on_pushButtonEditWord_clicked()
//{
//    QString word = ui->lineEditEditWord->text();
//    QString newDefinition = ui->textEditEditWordDefinition->toPlainText();
//    App::get().addWord(word, newDefinition);
//}


void MainWindow::on_lineEditFindPrefix_returnPressed()
{
    QString prefix = ui->lineEditFindPrefix->text();
    qDebug() << prefix;
    auto result = App::get().getListWordsWithPrefix(prefix);
    qDebug() << "OK";

//    for (auto& word : result) {
//        new QListWidgetItem(word, ui->listWidgetSearchResult);
//    }
}


//void MainWindow::on_lineEditFind_returnPressed()
//{
//    QString word = ui->lineEditFind->text();
//    QString definition = App::get().getDefinition(word);
//}


//void MainWindow::on_comboBoxDictionary_currentTextChanged(const QString &text)
//{
//    QString dictName = ui->comboBoxDictionary->currentText();
//    App::get().changeDictionary(dictName);
//}

