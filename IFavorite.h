#ifndef IFAVORITE_H
#define IFAVORITE_H

#include <QList>
#include <QString>

class IFavorite {
   public:
    virtual bool addWord(const QString& word, const QString& dictName, const QString& filePath) = 0;
    virtual bool removeWord(const QString& wordDictName) = 0;
    virtual QList<QString> getFavoriteWordsWithPrefix(
        const QString& prefix, int maxResultLength = 20) = 0;
    virtual QString getFavoriteWordDefinition(const QString& wordDictName) = 0;
    virtual ~IFavorite() = default;
};

#endif  // IFAVORITE_H
