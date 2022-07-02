#ifndef HISTORY_H
#define HISTORY_H

#include "IHistory.h"
#include "QFile"
#include "QTextStream"
#include "CSV.h"

class History : public IHistory {
public:
    History() {
        list = new QList<QString>();
        loadWord();
    }
    ~History() {
        delete list;
    }
    bool loadWord() {
        QString HistoryPath = getHistoryPath();
        QFile fin;
        QTextStream in;

        fin.setFileName(HistoryPath);
        if(!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);

        while(!in.atEnd()) {
            (*list).push_back(in.readLine());
        }

        fin.close();
        return true;
    }
    bool add(const QString &token, int maxSize) {
        if ((*list).size() == maxSize) (*list).removeLast();
        (*list).push_front(token);

        QString hisPath = getHistoryPath();
        QFile fout;
        QTextStream out;

        fout.setFileName(hisPath);
        if (!fout.open(QFile::WriteOnly | QFile::Text)) return false;
        out.setDevice(&fout);

        for (int i = 0; i < (*list).size(); ++i) {
            out << (*list)[i] << '\n';
        }
        return true;
    }
    QList<QString> getHistory() {
        return (*list);
    }
    QString getHistoryPath() {
        return "data/History/index.csv";
    }
private:
    QList <QString>* list;
};

#endif // HISTORY_H
