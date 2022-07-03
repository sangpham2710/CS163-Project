#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "WordDefinitionWidget.h"
#include "./ui_WordDefinitionWidget.h"

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

void MainWindow::on_pushButtonAddWord_clicked()
{
    QString word = ui->lineEditAddWord->text();
    QString definition = ui->textEditAddWordDefinition->toPlainText();
    App::get().addWord(word, definition);
}


void MainWindow::on_pushButtonEditWord_clicked()
{
    QString word = ui->lineEditEditWord->text();
    QString newDefinition = ui->textEditEditWordDefinition->toPlainText();
    App::get().addWord(word, newDefinition);
}

void MainWindow::on_lineEditFind_returnPressed()
{
    QString word = ui->lineEditFind->text();
    QString definition = App::get().getDefinition(word);
    qDebug() << definition;
}


void MainWindow::on_comboBoxDictionary_currentTextChanged(const QString &text)
{
    QString dictName = ui->comboBoxDictionary->currentText();
    App::get().changeDictionary(dictName);
    ui->listWidgetSearchResult->clear();
}


void MainWindow::on_listWidgetSearchResult_itemDoubleClicked(QListWidgetItem *item)
{
    QString word = item->text();
    for (int tabIndex = 0; tabIndex < ui->tabWidgetWordDefinition->count(); ++tabIndex) {
        if (ui->tabWidgetWordDefinition->tabText(tabIndex) == word) {
            ui->tabWidgetWordDefinition->setCurrentIndex(tabIndex);
            return;
        }
    }
    auto newTab = new WordDefinitionWidget(this);
    ui->tabWidgetWordDefinition->addTab(newTab, word);
    ui->tabWidgetWordDefinition->setCurrentIndex(ui->tabWidgetWordDefinition->count() - 1);

    newTab->setWord(word);
    newTab->setDefinition(App::get().getDefinition(word));
}


void MainWindow::on_pushButtonReset_clicked()
{
    ui->listWidgetSearchResult->clear();
    App::get().resetDictionary();
}


void MainWindow::on_lineEditFindPrefix_textChanged(const QString &text)
{
    QString prefix = ui->lineEditFindPrefix->text();
    auto result = App::get().getListWordsWithPrefix(prefix);

    ui->listWidgetSearchResult->clear();
    for (auto& word : result) {
        new QListWidgetItem(word, ui->listWidgetSearchResult);
    }
}


void MainWindow::on_tabWidgetWordDefinition_tabCloseRequested(int index)
{
    ui->tabWidgetWordDefinition->removeTab(index);
}

