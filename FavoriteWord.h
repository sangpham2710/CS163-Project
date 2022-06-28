#ifndef FAVORITEWORD_H
#define FAVORITEWORD_H

#include <QString>

class FavoriteWord {
public:
    QString word;
    QString definition;
    FavoriteWord() : word{}, definition{} {}
    FavoriteWord(QString word, QString definition) : word{std::move(word)}, definition{std::move(definition)} {}
};

#endif // FAVORITEWORD_H
