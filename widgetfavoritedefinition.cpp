#include "widgetfavoritedefinition.h"
#include "ui_widgetfavoritedefinition.h"
#include "App.h"

WidgetFavoriteDefinition::WidgetFavoriteDefinition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFavoriteDefinition)
{
    ui->setupUi(this);
    widgetFavorite = reinterpret_cast<WidgetFavorite*>(parent);
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

void WidgetFavoriteDefinition::setFavoriteState(QString &word)
{
    if (App::get().isWordInFavorite(word, true)) {
        ui->pushButtonSetFavorite->setText("Unlike");
    } else {
        ui->pushButtonSetFavorite->setText("Like");
    }
}

void WidgetFavoriteDefinition::on_pushButtonSetFavorite_clicked()
{
    QString word = ui->labelFavoriteWord->text();
    App::get().removeWordFromFavorite(word, true);
    widgetFavorite->clearListWidgetFavorite();
    widgetFavorite->clearLineEditSearchFavorite();
    widgetFavorite->removeCurrentTabFavorite();
}

