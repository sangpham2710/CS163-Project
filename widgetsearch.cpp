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

void WidgetSearch::on_listWidgetHistory_itemDoubleClicked(QListWidgetItem *item)
{
    ui->tabWidgetDefinition->addTab(new WidgetDefinition(), QString(item->text()).arg(ui->tabWidgetDefinition->count() + 1));
}


void WidgetSearch::on_tabWidgetDefinition_tabCloseRequested(int index)
{
    ui->tabWidgetDefinition->removeTab(index);
}


void WidgetSearch::on_pushButtonRandomWord_clicked()
{
    ui->tabWidgetDefinition->addTab(new WidgetDefinition(), QString("Word Name").arg(ui->tabWidgetDefinition->count() + 1));
}

