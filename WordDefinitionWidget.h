#ifndef WORDDEFINITIONWIDGET_H
#define WORDDEFINITIONWIDGET_H

#include <QWidget>

namespace Ui {
class WordDefinitionWidget;
}

class WordDefinitionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordDefinitionWidget(QWidget *parent = nullptr);
    ~WordDefinitionWidget();
    void setWord(const QString& word);
    void setDefinition(const QString& definition);
private:
    Ui::WordDefinitionWidget *ui;
};

#endif // WORDDEFINITIONWIDGET_H
