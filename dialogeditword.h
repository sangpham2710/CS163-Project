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
    void setDataEditWord(const QString &word, const QString &definition);

private slots:

    void on_pushButtonAccept_clicked();

    void on_pushButtonReject_clicked();

private:
    Ui::DialogEditWord *ui;
};

#endif // DIALOGEDITWORD_H
