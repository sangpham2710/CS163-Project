#include "widgetfavorite.h"
#include "ui_widgetfavorite.h"
#include "widgetfavoritedefinition.h"
#include "App.h"

WidgetFavorite::WidgetFavorite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFavorite)
{
    ui->setupUi(this);
    auto result = App::get().getFavoriteWordsWithPrefix("");
    ui->tabWidgetFavoriteWord->clear();
    for (auto& word : result)
    {
        new QListWidgetItem(word, ui->listWidgetFavoriteWord);
    }
}

WidgetFavorite::~WidgetFavorite()
{
    delete ui;
}


void WidgetFavorite::on_tabWidgetFavoriteWord_tabCloseRequested(int index)
{
    ui->tabWidgetFavoriteWord->removeTab(index);
}

//Text change in search bar
void WidgetFavorite::on_lineEditSearchFavorite_textChanged(const QString &prefix)
{
    auto result = App::get().getFavoriteWordsWithPrefix(prefix);
    ui->listWidgetFavoriteWord->clear();
    for (auto& word : result)
    {
        new QListWidgetItem(word, ui->listWidgetFavoriteWord);
    }
}

//Double click to word in history
void WidgetFavorite::on_listWidgetFavoriteWord_itemDoubleClicked(QListWidgetItem *item)
{
    QString word = item->text();
    for (int tabIndex = 0; tabIndex < ui->tabWidgetFavoriteWord->count(); ++tabIndex)
    {
        if (ui->tabWidgetFavoriteWord->tabText(tabIndex) == word)
        {
            ui->tabWidgetFavoriteWord->setCurrentIndex(tabIndex);
            return;
        }
    }
    auto newTab = new WidgetFavoriteDefinition(this);
    ui->tabWidgetFavoriteWord->addTab(newTab, word);
    ui->tabWidgetFavoriteWord->setCurrentIndex(ui->tabWidgetFavoriteWord->count() - 1);
    //Set word
    newTab->setWord(word);
    //Set definition
    QString definition = App::get().getDefinition(word);
    newTab->setDefinition(definition);
    //Set favorite state
    newTab->setFavoriteState(word);
}

void WidgetFavorite::clearLineEditSearchFavorite()
{
    ui->lineEditSearchFavorite->clear();
}

void WidgetFavorite::clearListWidgetFavorite()
{
    auto result = App::get().getFavoriteWordsWithPrefix("");
    ui->tabWidgetFavoriteWord->clear();
    for (auto& word : result)
    {
        new QListWidgetItem(word, ui->listWidgetFavoriteWord);
    }
}

void WidgetFavorite::removeCurrentTabFavorite()
{
    int index = ui->tabWidgetFavoriteWord->currentIndex();
    ui->tabWidgetFavoriteWord->removeTab(index);
}
