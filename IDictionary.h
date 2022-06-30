#ifndef IDICTIONARY_H
#define IDICTIONARY_H

#include <QList>
#include <QString>

class IDictionary {
public:
    virtual QList<QString> getListWordsWithPrefix(const QString& prefix, int maxResultLength = 20) = 0;
    virtual bool changeDictionary(const QString& dictName) = 0;
    virtual bool addWord(const QString& word, const QString& definition) = 0;
    virtual bool removeWord(const QString& word) = 0;
    virtual bool reset() = 0;
    virtual QString getDefinition(const QString& word) = 0;
    virtual QString getRandomWord() = 0;
    virtual QString getListWordsHaveDefinition(const QString& token, int maxResultLength = 20) = 0;
    virtual QString getFullDefinitionPath(const QString& word) = 0;
};

#endif // IDICTIONARY_H
