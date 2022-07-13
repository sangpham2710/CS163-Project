#ifndef HISTORY_H
#define HISTORY_H

#include <QFile>
#include <QList>
#include <QString>
#include <QTextStream>

#include "IHistory.h"

class History : public IHistory {
   public:
    History() : list{new QList<QString>()} { loadData(); }
    ~History() { delete list; }
    bool loadData() {
        QString historyPath = getHistoryPath();
        QFile fin;
        QTextStream in;

        fin.setFileName(historyPath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);

        while (!in.atEnd()) {
            list->push_back(in.readLine());
        }
        fin.close();
        return true;
    }
    bool add(const QString& token, int maxSize) {
        if (list->size() == maxSize) list->pop_back();
        list->push_front(token);

        QString historyPath = getHistoryPath();
        QFile fout;
        QTextStream out;

        fout.setFileName(historyPath);
        if (!fout.open(QFile::WriteOnly | QFile::Text)) return false;
        out.setDevice(&fout);

        for (int i = 0; i < list->size(); ++i) {
            out << (*list)[i] << '\n';
        }
        return true;
    }
    QList<QString> getHistory() { return *list; }
    QString getHistoryPath() {
        return "/Users/tranhainam/Documents/build-CS163-Project-Qt_6_3_0_for_macOS-Debug/data/history/"
               "index.csv";
    }

   private:
    QList<QString>* list;
};

#endif  // HISTORY_H
