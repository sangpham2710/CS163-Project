#ifndef WIDGETSEARCH_H
#define WIDGETSEARCH_H

#include <QWidget>
#include <QListWidgetItem>
#include "dialogaddnewword.h"
#include <QString>

namespace Ui {
class WidgetSearch;
}

class WidgetSearch : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSearch(QWidget *parent = nullptr);
    ~WidgetSearch();
    void loadHistory();
    void clearLineEditSearch();
    void clearWidgetHistory();
    void removeCurrentTabDefinition();
    void reloadFavoriteStates();
    const QString &getCurrentDictName() const;

private slots:

    void on_listWidgetHistory_itemDoubleClicked(QListWidgetItem *item);

    void on_tabWidgetDefinition_tabCloseRequested(int index);

    void on_pushButtonRandomWord_clicked();

    void on_comboBoxDictionaryType_currentTextChanged(const QString &arg1);

    void on_lineEditSearch_textChanged(const QString &arg1);

    void on_pushButtonReset_clicked();

    void on_pushButtonAddWord_clicked();

    void openDialogAddNewWord();

    void on_lineEditSearch_returnPressed();

private:
    Ui::WidgetSearch *ui;
    DialogAddNewWord *dialogAddNewWord;
    QString currentDictName;
};

#endif // WIDGETSEARCH_H
