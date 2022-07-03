#include "WordDefinitionWidget.h"
#include "./ui_WordDefinitionWidget.h"

WordDefinitionWidget::WordDefinitionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordDefinitionWidget)
{
    ui->setupUi(this);
}

WordDefinitionWidget::~WordDefinitionWidget()
{
    delete ui;
}

void WordDefinitionWidget::setWord(const QString &word)
{
    ui->groupBoxWord->setTitle(word);
}

void WordDefinitionWidget::setDefinition(const QString &definition)
{
    ui->labelDefinition->setText(definition);
}
