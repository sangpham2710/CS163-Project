#include "widgetsearch.h"
#include "ui_widgetsearch.h"
#include "widgetdefinition.h"
#include "App.h"

#include <QDebug>
WidgetSearch::WidgetSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSearch)
{
    ui->setupUi(this);
    App::get();
    for (auto& dictName : App::get().getListDictionaries())
    {
        ui->comboBoxDictionaryType->addItem(dictName);
    }
}

WidgetSearch::~WidgetSearch()
{
    delete ui;
}

void WidgetSearch::on_listWidgetHistory_itemDoubleClicked(QListWidgetItem *item)
{
    ui->tabWidgetDefinition->addTab(new WidgetDefinition(), QString(item->text()));
}


void WidgetSearch::on_tabWidgetDefinition_tabCloseRequested(int index)
{
    ui->tabWidgetDefinition->removeTab(index);
}


void WidgetSearch::on_pushButtonRandomWord_clicked()
{
    ui->tabWidgetDefinition->addTab(new WidgetDefinition(), QString("Word Name"));
}

void WidgetSearch::on_comboBoxDictionaryType_currentTextChanged(const QString &arg1)
{
    QString dictName = ui->comboBoxDictionaryType->currentText();
    App::get().changeDictionary(dictName);
    ui->lineEditSearch->clear();
}



