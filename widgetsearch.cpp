#include "widgetsearch.h"
#include "ui_widgetsearch.h"
#include "widgetdefinition.h"
#include "App.h"

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

    //set definition of the definition
    QString definition = App::get().getDefinition(word);
    newTab->setDefinition(definition);
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
}

//Change text in searching bar -> change text in history widget
void WidgetSearch::on_lineEditSearch_textChanged(const QString &prefix)
{
    auto result = App::get().getListWordsWithPrefix(prefix);
    if (result.size() == 0)
    {
        //Add new word enabled
    }
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
    ui->listWidgetHistory->clear();
    App::get().resetDictionary();
}


void WidgetSearch::on_lineEditSearch_returnPressed()
{
    ui->listWidgetHistory->clear();
    if (ui->radioButtonSearchDictionary->isChecked()) {
        auto result = App::get().getListWordsHaveDefinition(ui->lineEditSearch->text());
        for (auto& word : result) {
            new QListWidgetItem(word, ui->listWidgetHistory);
        }
    }
}

