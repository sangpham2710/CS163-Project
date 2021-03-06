#ifndef WIDGETDEFINITION_H
#define WIDGETDEFINITION_H

#include <QWidget>
#include "dialogeditword.h"
#include "widgetsearch.h"

namespace Ui {
class WidgetDefinition;
}

class WidgetDefinition : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetDefinition(QWidget *parent = nullptr);
    ~WidgetDefinition();
    void setDefinition(const QString &definition);
    void setWord(const QString &word);
    void setFavoriteState(const QString &word);
    const QString& getWord() const;

private slots:

    void on_pushButtonEditWord_clicked();

    void on_pushButtonSetFavorite_clicked();

    void on_pushButtonRemoveWord_clicked();

    void openDialogEditWord();


private:
    Ui::WidgetDefinition *ui;
    DialogEditWord *dialogEditWord;
    WidgetSearch *widgetSearch;
};

#endif // WIDGETDEFINITION_H
