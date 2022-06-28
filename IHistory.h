#ifndef IHISTORY_H
#define IHISTORY_H

#include <QVector>
#include <QString>

class IHistory {
public:
    virtual bool add(const QString& token, int maxSize = 20) = 0;
    virtual QVector<QString> getHistory() = 0;
};

#endif // IHISTORY_H
