#include "widgetfavourite.h"
#include "ui_widgetfavourite.h"
#include "widgetdefinition.h"

widgetfavourite::widgetfavourite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetfavourite)
{
    ui->setupUi(this);
}

widgetfavourite::~widgetfavourite()
{
    delete ui;
}


void widgetfavourite::on_listWidgetFavouriteLWord_itemDoubleClicked(QListWidgetItem *item)
{
    ui->tabWidgetFavouriteWord->addTab(new WidgetDefinition(), QString(item->text().arg(ui->tabWidgetFavouriteWord->count() + 1)));
}


void widgetfavourite::on_tabWidgetFavouriteWord_tabCloseRequested(int index)
{
    ui->tabWidgetFavouriteWord->removeTab(index);
}

