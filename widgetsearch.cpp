#include "widgetsearch.h"
#include "ui_widgetsearch.h"
#include "widgetdefinition.h"
#include "App.h"
#include <QMessageBox>

#include <QDebug>
WidgetSearch::WidgetSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSearch)
{
    ui->setupUi(this);
    App::get();
    for (auto& dictName : App::get().getListDictionaries())
    {
        ui->comboBoxDictionaryType->addItem(dictName);
    }
    ui->tabWidgetDefinition->clear();
    ui->radioButtonSearchKeyword->setChecked(true);
    ui->pushButtonAddWord->setEnabled(false);
    loadHistory();
}

WidgetSearch::~WidgetSearch()
{
    delete ui;
}

//Double click to word in history
void WidgetSearch::on_listWidgetHistory_itemDoubleClicked(QListWidgetItem *item)
{
    QString word = item->text();
    for (int tabIndex = 0; tabIndex < ui->tabWidgetDefinition->count(); ++tabIndex)
    {
        if (ui->tabWidgetDefinition->tabText(tabIndex) == word)
        {
            ui->tabWidgetDefinition->setCurrentIndex(tabIndex);
            return;
        }
    }
    auto newTab = new WidgetDefinition(this);
    ui->tabWidgetDefinition->addTab(newTab, word);
    ui->tabWidgetDefinition->setCurrentIndex(ui->tabWidgetDefinition->count() - 1);
    //set title of the definition
    newTab->setWord(word);

    //set definition of the definition
    QString definition = App::get().getDefinition(word);
    newTab->setDefinition(definition);

    //set favorite
    newTab->setFavorite(word);
}



void WidgetSearch::on_tabWidgetDefinition_tabCloseRequested(int index)
{
    ui->tabWidgetDefinition->removeTab(index);
}


void WidgetSearch::on_pushButtonRandomWord_clicked()
{
    ui->tabWidgetDefinition->addTab(new WidgetDefinition(), QString("Word Name"));
}

//Change text in combo box dictionary type
void WidgetSearch::on_comboBoxDictionaryType_currentTextChanged(const QString &text)
{
    QString dictName = ui->comboBoxDictionaryType->currentText();
    App::get().changeDictionary(dictName);
    ui->lineEditSearch->clear();
    loadHistory();
}

//Change text in searching bar -> change text in history widget
void WidgetSearch::on_lineEditSearch_textChanged(const QString &prefix)
{
    auto result = App::get().getListWordsWithPrefix(prefix);
    if (result.size() == 0)
    {
        //Add new word enabled
        ui->pushButtonAddWord->setEnabled(true);
    }
    else ui->pushButtonAddWord->setEnabled(false);

    if (prefix == "") {
        loadHistory();
        return;
    }
    ui->listWidgetHistory->clear();
    for (auto& word : result) {
        new QListWidgetItem(word, ui->listWidgetHistory);
    }
}

//Change text in history widget
void WidgetSearch::loadHistory() {
    ui->listWidgetHistory->clear();
    for (auto& word : App::get().getHistory()) {
        new QListWidgetItem(word, ui->listWidgetHistory);
    }
    for (int listIndex = 0; listIndex < ui->listWidgetHistory->count(); ++listIndex) {
        auto item = ui->listWidgetHistory->item(listIndex);
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
}

//Press reset button
void WidgetSearch::on_pushButtonReset_clicked()
{
    QMessageBox::StandardButton confirm = QMessageBox::question(this, "Title", "Do you want to reset your dictionary ?", QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes)
    {
        ui->listWidgetHistory->clear();
        ui->tabWidgetDefinition->clear();
        ui->lineEditSearch->clear();
        App::get().resetDictionary();
    }
}

void WidgetSearch::openDialogAddNewWord()
{
    QString newWord = ui->lineEditSearch->text();
    DialogAddNewWord dialogAddNewWord;
    dialogAddNewWord.setDataAddNewWord(newWord);
    dialogAddNewWord.exec();
}

//Press add new word button
void WidgetSearch::on_pushButtonAddWord_clicked()
{
    QMessageBox::StandardButton confirm = QMessageBox::question(this, "Title", "Do you want to add this word to your dictionary ?", QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes)
    {
        openDialogAddNewWord();
    }
}


