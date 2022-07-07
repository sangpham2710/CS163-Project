#include "widgetfavoritedefinition.h"
#include "ui_widgetfavoritedefinition.h"

WidgetFavoriteDefinition::WidgetFavoriteDefinition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFavoriteDefinition)
{
    ui->setupUi(this);
}

WidgetFavoriteDefinition::~WidgetFavoriteDefinition()
{
    delete ui;
}
