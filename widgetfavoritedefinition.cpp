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

void WidgetFavoriteDefinition::setWord(QString &word)
{
    ui->labelFavoriteWord->setText(word);
}

void WidgetFavoriteDefinition::setDefinition(QString &definition)
{
    ui->labelFavoriteDefinition->setText(definition);
}
