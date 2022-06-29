#ifndef IFAVORITE_H
#define IFAVORITE_H

#include <QList>
#include <QString>

class IFavorite {
public:
    virtual bool addWord(const QString& word, const QString& definition) = 0;
    virtual bool removeWord(const QString& word) = 0;
    virtual QList<QString> getFavoriteWords() = 0;
    virtual QString getFavoriteWordDefinition(const QString& word) = 0;
};

#endif // IFAVORITE_H
