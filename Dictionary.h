#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
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
    Dictionary() : dictMap{}, currentDict{nullptr} { allocate(); }
    ~Dictionary() { deallocate(); }
    bool addDictionary(const QString& dictName) {
        if (dictMap.contains(dictName)) return false;
        dictMap[dictName] = new DictionaryDataStructure(dictName);
        return true;
    }
    void allocate() {
        QElapsedTimer totalTimer;
        int totalNumWords = 0;
        totalTimer.start();
        deallocate();
        QElapsedTimer timer;
        QString firstDictName = "";
        for (auto &dirName : fs::directory_iterator{"data/dicts"}) {
            QString dictName =
                QString::fromStdString(dirName.path().filename().string());
            timer.start();
            addDictionary(dictName);
            qDebug() << QString("Loaded %1 dictionary in %2 ms (%3 words)")
                            .arg(dictName)
                            .arg(timer.restart())
                            .arg(dictMap[dictName]->getNumWords());
            totalNumWords += dictMap[dictName]->getNumWords();
            if (firstDictName == "") firstDictName = dictName;
        }
        currentDict = dictMap[firstDictName];
        qDebug() << QString("Total time to load all dictionaries: %1 ms")
                        .arg(totalTimer.elapsed());
        qDebug() << QString("Loaded %1 words").arg(totalNumWords);
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
    QList<QString> getListDictionaries() { return dictMap.keys(); }
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
    bool remove(const QString& dictName) {
        QDir("data/dicts/" + dictName).removeRecursively();
        QDir("data/dicts-origin/" + dictName).removeRecursively();
        delete dictMap[dictName];
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
    QString getCurrentDictionaryName() {
        return currentDict->getDictionaryName();
    }

   private:
    Map<QString, DictionaryDataStructure *> dictMap;
    DictionaryDataStructure *currentDict;
};

#endif  // DICTIONARY_H
