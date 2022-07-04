#include "widgetfavouritelist.h"
#include "ui_widgetfavouritelist.h"
#include "widgetdefinition.h"

WidgetFavouriteList::WidgetFavouriteList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFavouriteList)
{
    ui->setupUi(this);
}

WidgetFavouriteList::~WidgetFavouriteList()
{
    delete ui;
}



void WidgetFavouriteList::on_tabWidgetFavouriteWord_tabBarDoubleClicked(int index)
{
    ui->tabWidgetFavouriteWord->addTab(new WidgetDefinition(), QString("Word").arg(ui->tabWidgetFavouriteWord->count() + 1));
}

