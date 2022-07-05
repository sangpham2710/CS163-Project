#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "WordDefinitionWidget.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    App::get();
    for (auto& dictName : App::get().getListDictionaries())
        ui->comboBoxDictionary->addItem(dictName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAddWord_clicked()
{
    QString word = ui->lineEditAddWord->text();
    QString definition = ui->textEditAddWordDefinition->toPlainText();
    qDebug() << App::get().addWord(word, definition);
    ui->lineEditAddWord->clear();
    ui->textEditAddWordDefinition->clear();
}


void MainWindow::on_pushButtonEditWord_clicked()
{
    QString word = ui->lineEditEditWord->text();
    QString newDefinition = ui->textEditEditWordDefinition->toPlainText();
    qDebug() << App::get().editWord(word, newDefinition);
    ui->lineEditEditWord->clear();
    ui->textEditEditWordDefinition->clear();
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
    ui->lineEditFindPrefix->clear();
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
    QString definition = App::get().getDefinition(word);
    newTab->setWord(word);
    newTab->setDefinition(definition);
}


void MainWindow::on_pushButtonReset_clicked()
{
    ui->listWidgetSearchResult->clear();
    App::get().resetDictionary();
}


void MainWindow::on_lineEditFindPrefix_textChanged(const QString &prefix)
{
    auto result = App::get().getListWordsWithPrefix(prefix);
    if (prefix == "") {
        loadHistory();
        return;
    }
    ui->listWidgetSearchResult->clear();
    for (auto& word : result) {
        new QListWidgetItem(word, ui->listWidgetSearchResult);
    }
}


void MainWindow::on_tabWidgetWordDefinition_tabCloseRequested(int index)
{
    ui->tabWidgetWordDefinition->removeTab(index);
}

void MainWindow::loadHistory() {
    ui->listWidgetSearchResult->clear();
    for (auto& word : App::get().getHistory()) {
        new QListWidgetItem(word, ui->listWidgetSearchResult);
    }
    for (int listIndex = 0; listIndex < ui->listWidgetSearchResult->count(); ++listIndex) {
        auto item = ui->listWidgetSearchResult->item(listIndex);
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
}


void MainWindow::on_lineEditFavoriteFindPrefix_textChanged(const QString &prefix)
{
    auto result = App::get().getFavoriteWordsWithPrefix(prefix);
    ui->listWidgetFavoriteSearchResult->clear();
    for (auto& word : result) {
        new QListWidgetItem(word, ui->listWidgetFavoriteSearchResult);
    }
}


void MainWindow::on_listWidgetFavoriteSearchResult_itemDoubleClicked(QListWidgetItem *item)
{
    QString wordDictName = item->text();
    for (int tabIndex = 0; tabIndex < ui->tabWidgetFavoriteWordDefinition->count(); ++tabIndex) {
        if (ui->tabWidgetFavoriteWordDefinition->tabText(tabIndex) == wordDictName) {
            ui->tabWidgetFavoriteWordDefinition->setCurrentIndex(tabIndex);
            return;
        }
    }
    auto newTab = new WordDefinitionWidget(this);
    ui->tabWidgetFavoriteWordDefinition->addTab(newTab, wordDictName);
    ui->tabWidgetFavoriteWordDefinition->setCurrentIndex(ui->tabWidgetFavoriteWordDefinition->count() - 1);
    QString definition = App::get().getFavoriteWordDefinition(wordDictName);
    newTab->setWord(wordDictName);
    newTab->setDefinition(definition);
}


void MainWindow::on_tabWidgetFavoriteWordDefinition_tabCloseRequested(int index)
{
    ui->tabWidgetFavoriteWordDefinition->removeTab(index);
}

