#ifndef IDICTIONARY_H
#define IDICTIONARY_H

#include <QVector>
#include <QString>

class IDictionary {
public:
    virtual QVector<QString> getListWordsWithPrefix(const QString& prefix, int resultLength = 20) = 0;
    virtual bool changeDictionary(const QString& dictName) = 0;
    virtual bool addWord(const QString& word, const QString& definition) = 0;
    virtual bool removeWord(const QString& word) = 0;
    virtual bool reset() = 0;
    virtual QString getDefinition(const QString& word) = 0;
    virtual QString getRandomWord() = 0;
    virtual QString getRandomDefinition() = 0;
    virtual QString getListWordsHaveDefinition(const QString& token, int resultLength = 20) = 0;
};

#endif // IDICTIONARY_H
