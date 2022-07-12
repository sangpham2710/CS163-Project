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
    for (auto& word : result)
    {
        new QListWidgetItem(word, ui->listWidgetFavoriteWord);
    }
}

WidgetFavorite::~WidgetFavorite()
{
    delete ui;
}

void WidgetFavorite::on_listWidgetFavoriteWord_itemDoubleClicked(QListWidgetItem *item)
{
    ui->tabWidgetFavoriteWord->addTab(new WidgetFavoriteDefinition(), QString(item->text()));
}


void WidgetFavorite::on_tabWidgetFavoriteWord_tabCloseRequested(int index)
{
    ui->tabWidgetFavoriteWord->removeTab(index);
}


void WidgetFavorite::on_lineEditSearchFavorite_textChanged(const QString &prefix)
{
    auto result = App::get().getFavoriteWordsWithPrefix(prefix);
    ui->listWidgetFavoriteWord->clear();
    for (auto& word : result)
    {
        new QListWidgetItem(word, ui->listWidgetFavoriteWord);
    }
}

