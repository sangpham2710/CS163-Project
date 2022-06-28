#ifndef IFAVORITE_H
#define IFAVORITE_H

#include <QVector>
#include <QString>
#include "FavoriteWord.h"

class IFavorite {
public:
    virtual bool addWord(const FavoriteWord& word) = 0;
    virtual bool removeWord(const QString& word) = 0;
    virtual QVector<FavoriteWord> getListFavoriteWords() = 0;
};

#endif // IFAVORITE_H
