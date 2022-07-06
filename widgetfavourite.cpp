#include "widgetfavourite.h"
#include "ui_widgetfavourite.h"
#include "widgetdefinition.h"

WidgetFavourite::WidgetFavourite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFavourite)
{
    ui->setupUi(this);
}

WidgetFavourite::~WidgetFavourite()
{
    delete ui;
}

void WidgetFavourite::on_listWidgetFavouriteWord_itemDoubleClicked(QListWidgetItem *item)
{
    ui->tabWidgetFavouriteWord->addTab(new WidgetDefinition(), QString(item->text()));
}


void WidgetFavourite::on_tabWidgetFavouriteWord_tabCloseRequested(int index)
{
    ui->tabWidgetFavouriteWord->removeTab(index);
}

