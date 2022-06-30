#ifndef FAVORITE_H
#define FAVORITE_H

#include "IFavorite.h"

class Favorite : public IFavorite {
public:
    bool addWord(const QString &word, const QString &filePath);
    bool removeWord(const QString &word);
    QList<QString> getFavoriteWordsWithPrefix(const QString &prefix, int maxResultLength);
    QString getFavoriteWordDefinition(const QString &word);
};

#endif // FAVORITE_H
