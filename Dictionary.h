#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QList>
#include "Map.h"
#include "IDictionary.h"
#include "DictionaryDataStructure.h"

class Dictionary : public IDictionary {
public:
    Dictionary() {
        QList<QString> dictNames = {
            "Eng-Eng-small",
            "Eng-Eng",
            "Eng-Vie",
            "Vie-Eng",
            "Slang",
            "Emotional",
        };
        for (auto& dictName : dictNames) {
            dictMap[dictName] = new DictionaryDataStructure(dictName);
        }
        currentDict = dictMap[dictNames[0]];
    }
    ~Dictionary() {
        for (auto& dictName : dictMap.keys()) delete dictMap[dictName];
    }
    QList<QString> getListWordsWithPrefix(const QString &prefix, int maxResultLength) {
        return currentDict->getListWordsWithPrefix(prefix, maxResultLength);
    }
    bool changeDictionary(const QString &dictName) {
        if (currentDict->getDictionaryName() == dictName) return true;
        if (!dictMap.contains(dictName)) return false;
        currentDict = dictMap[dictName];
        return true;
    }
    bool addWord(const QString &word, const QString &definition) {
        return currentDict->addWord(word, definition);
    }
    bool editWord(const QString &word, const QString &newDefinition) {
        return currentDict->editWord(word, newDefinition);
    }
    bool removeWord(const QString &word) {
        return currentDict->removeWord(word);
    }
    bool reset() {
        // NOT DONE
        return true;
    }
    QString getDefinition(const QString &word) {
        return currentDict->getDefinition(word);
    }
    QString getRandomWord() {
        // NOT DONE
        return "";
    }
    QList<QString> getListWordsHaveDefinition(const QString &token, int maxResultLength) {
        return currentDict->getListWordsHaveDefinition(token, maxResultLength);
    }
    QString getFullDefinitionPath(const QString &word) {
        return currentDict->getFullDefinitionPath(word);
    }
private:
    Map<QString, DictionaryDataStructure*> dictMap;
    DictionaryDataStructure* currentDict;
};

#endif // DICTIONARY_H
