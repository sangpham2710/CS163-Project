#include "widgetfavorite.h"
#include "ui_widgetfavorite.h"
#include "widgetdefinition.h"

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
    ui->tabWidgetFavoriteWord->addTab(new WidgetDefinition(), QString(item->text()));
}


void WidgetFavorite::on_tabWidgetFavoriteWord_tabCloseRequested(int index)
{
    ui->tabWidgetFavoriteWord->removeTab(index);
}

