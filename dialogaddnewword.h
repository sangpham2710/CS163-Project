#ifndef DIALOGADDNEWWORD_H
#define DIALOGADDNEWWORD_H

#include <QDialog>

namespace Ui {
class DialogAddNewWord;
}

class DialogAddNewWord : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddNewWord(QWidget *parent = nullptr);
    ~DialogAddNewWord();

private:
    Ui::DialogAddNewWord *ui;
};

#endif // DIALOGADDNEWWORD_H
