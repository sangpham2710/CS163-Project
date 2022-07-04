#include "widgetsearch.h"
#include "ui_widgetsearch.h"
#include "widgetdefinition.h"

WidgetSearch::WidgetSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSearch)
{
    ui->setupUi(this);
}

WidgetSearch::~WidgetSearch()
{
    delete ui;
}

void WidgetSearch::on_tabWidgetDefinition_tabBarDoubleClicked(int index)
{
    ui->tabWidgetDefinition->addTab(new WidgetDefinition(), QString("Word").arg(ui->tabWidgetDefinition->count() + 1));
}


void WidgetSearch::on_pushButtonAddNewWord_clicked()
{
    dialogAddNewWord = new DialogAddNewWord(this);
    dialogAddNewWord->show();
}

