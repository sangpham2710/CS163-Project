#ifndef DICTIONARYDATASTRUCTURE_H
#define DICTIONARYDATASTRUCTURE_H

#include "Trie.h"

class DictionaryDataStructure {
public:
    DictionaryDataStructure() : trie{new Trie<QString>()} {}
    DictionaryDataStructure(const QString& dictName) : trie{new Trie<QString>()}, dictName{dictName} {
        loadWords();
    }
    ~DictionaryDataStructure() {
        delete trie;
    }
    QString getDictionaryName() {
        return dictName;
    }
    void loadWords() {
        trie->clear();
        QString wordFolderPath = QString("D:/CS163-Project/data/dicts/%1/words/index.csv").arg(dictName);
        // load words from file

    }
    QList<QString> getListWordsWithPrefix(const QString &prefix, int maxResultLength) {
        return trie->searchPrefix(prefix, maxResultLength);
    }
    bool addWord(const QString& word, const QString& definition) {
        if (trie->contains(word)) return false;
        (*trie)[word] = "tmp.txt";
        QString path = getFullDefinitionPath(word);
        // append definition into tmp.txt
        return true;
    }
    bool editWord(const QString& word, const QString& newDefinition) {
        if (!trie->contains(word)) return false;
        QString path = getFullDefinitionPath(word);
        // edit word in file using path variable
        return true;
    }
    bool removeWord(const QString& word) {
        if (!trie->contains(word)) return false;
        QString path = getFullDefinitionPath(word);
        // remove word in file using path variable
        trie->remove(word);
        return true;
    }
    QString getDefinition(const QString& word) {
        if (!trie->contains(word)) return "";
        QString path = getFullDefinitionPath(word);
        // get definition of word in file using path variable
        QString definition = "nothing";
        return definition;
    }
    QList<QString> getListWordsHaveDefinition(const QString& token, int maxResultLength) {
        return {};
    }
    QString getFullDefinitionPath(const QString& word) {
        if (!trie->contains(word)) return "";
        return QString("D:/CS163-Project/data/dicts/%1/defis/$2.csv").arg(dictName).arg((*trie)[word]);
    }
private:
    Trie<QString>* trie;
    QString dictName;
};

#endif // DICTIONARYDATASTRUCTURE_H
