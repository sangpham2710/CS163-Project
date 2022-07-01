#ifndef HISTORY_H
#define HISTORY_H

#include "IHistory.h"
#include "QFile"
#include "QTextStream"
#include "CSV.h"

class History : public IHistory {
public:
    bool add(const QString &token, int maxSize) {
        if ((*list).size() == maxSize) (*list).removeLast();
        (*list).push_front(token);

        QString hisPath = getHistoryPath();
        QFile fin, fout;
        QTextStream in, out;
        QVector <QString> wordList;

        fin.setFileName(hisPath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);
        while (!in.atEnd()) {
            wordList.push_back(in.readLine());
        }
        fin.close();

        fout.setFileName(hisPath);
        if (!fout.open(QFile::WriteOnly | QFile::Text)) return false;
        out.setDevice(&fout);
        out << token << Qt::endl;
        for (int i = 0; i < wordList.size() - 1; ++i) {
            out << wordList[i] << Qt:: endl;
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
