#ifndef WIDGETSEARCH_H
#define WIDGETSEARCH_H

#include <QWidget>
#include "dialogaddnewword.h"

namespace Ui {
class WidgetSearch;
}

class WidgetSearch : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSearch(QWidget *parent = nullptr);
    ~WidgetSearch();

private slots:
    void on_tabWidgetDefinition_tabBarDoubleClicked(int index);

    void on_pushButtonAddNewWord_clicked();

private:
    Ui::WidgetSearch *ui;
    DialogAddNewWord *dialogAddNewWord;
};

#endif // WIDGETSEARCH_H
