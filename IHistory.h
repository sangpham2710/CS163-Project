#ifndef IHISTORY_H
#define IHISTORY_H

#include <QList>
#include <QString>

class IHistory {
   public:
    virtual bool add(const QString& token, int maxSize = 20) = 0;
    virtual QList<QString> getHistory() = 0;
    virtual ~IHistory() = default;
};

#endif  // IHISTORY_H
