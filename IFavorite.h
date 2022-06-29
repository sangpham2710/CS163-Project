#ifndef IFAVORITE_H
#define IFAVORITE_H

#include <QList>
#include <QString>
#include "FavoriteWord.h"

class IFavorite {
public:
    virtual bool addWord(const FavoriteWord& word) = 0;
    virtual bool removeWord(const QString& word) = 0;
    virtual QList<FavoriteWord> getListFavoriteWords() = 0;
};

#endif // IFAVORITE_H
