#include "widgetfavorite.h"
#include "ui_widgetfavorite.h"
#include "widgetfavoritedefinition.h"

WidgetFavorite::WidgetFavorite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFavorite)
{
    ui->setupUi(this);
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

