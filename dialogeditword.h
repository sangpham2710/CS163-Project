#ifndef DIALOGEDITWORD_H
#define DIALOGEDITWORD_H

#include <QDialog>

namespace Ui {
class DialogEditWord;
}

class DialogEditWord : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditWord(QWidget *parent = nullptr);
    ~DialogEditWord();

private slots:

private:
    Ui::DialogEditWord *ui;
};

#endif // DIALOGEDITWORD_H
