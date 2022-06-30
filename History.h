#ifndef HISTORY_H
#define HISTORY_H

#include "IHistory.h"

class History : public IHistory {
public:
    bool add(const QString &token, int maxSize);
    QList<QString> getHistory();
};

#endif // HISTORY_H
