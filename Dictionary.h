#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QDebug>
#include <QDir>
#include <QList>
#include <QString>
#include <filesystem>
#include <string>

#include "DictionaryDataStructure.h"
#include "IDictionary.h"
#include "Map.h"

using std::string;
namespace fs = std::filesystem;

class Dictionary : public IDictionary {
   public:
    Dictionary() { allocate(); }
    ~Dictionary() { deallocate(); }
    void allocate() {
        deallocate();
        for (auto &dirName : fs::directory_iterator{"data/dicts"}) {
            QString dictName =
                QString::fromStdString(dirName.path().filename().string());
            dictMap[dictName] = new DictionaryDataStructure(dictName);
        }
        currentDict = dictMap["Eng-Eng-small"];
    }
    void deallocate() {
        for (auto &dictName : dictMap.keys()) {
            if (dictMap[dictName]) delete dictMap[dictName];
        }
    }
    QList<QString> getListWordsWithPrefix(const QString &prefix,
                                          int maxResultLength) {
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
        QString dictName = currentDict->getDictionaryName();
        string dictNameStdString = dictName.toStdString();
        QDir("data/dicts/" + dictName).removeRecursively();
        fs::copy("data/dicts-origin/" + dictNameStdString,
                 "data/dicts/" + dictNameStdString,
                 fs::copy_options::recursive);
        delete dictMap[dictName];
        dictMap[dictName] = new DictionaryDataStructure(dictName);
        currentDict = dictMap[dictName];
        return true;
    }
    QString getDefinition(const QString &word) {
        return currentDict->getDefinition(word);
    }
    QString getRandomWord() { return currentDict->getRandomWord(); }
    QList<QString> getListWordsHaveDefinition(const QString &token,
                                              int maxResultLength) {
        return currentDict->getListWordsHaveDefinition(token, maxResultLength);
    }
    QString getFullDefinitionPath(const QString &word) {
        return currentDict->getFullDefinitionPath(word);
    }

   private:
    Map<QString, DictionaryDataStructure *> dictMap;
    DictionaryDataStructure *currentDict;
};

#endif  // DICTIONARY_H
