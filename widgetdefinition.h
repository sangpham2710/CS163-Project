#ifndef WIDGETDEFINITION_H
#define WIDGETDEFINITION_H

#include <QWidget>
#include "dialogeditword.h"

namespace Ui {
class WidgetDefinition;
}

class WidgetDefinition : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetDefinition(QWidget *parent = nullptr);
    ~WidgetDefinition();

private slots:

    void on_pushButtonEditWord_clicked();

    void on_pushButtonSetFavourite_clicked();

    void on_pushButtonRemoveWord_clicked();

private:
    Ui::WidgetDefinition *ui;
    DialogEditWord *dialogEditWord;
};

#endif // WIDGETDEFINITION_H