#ifndef DICTIONARYDATASTRUCTURE_H
#define DICTIONARYDATASTRUCTURE_H

#include "Trie.h"

class DictionaryDataStructure {
public:
    DictionaryDataStructure() : trie{new Trie<QString>()} {}
    DictionaryDataStructure(const QString& dictName) : trie{new Trie<QString>()}, dictName{dictName} {}
    ~DictionaryDataStructure() {
        delete trie;
    }
private:
    Trie<QString>* trie;
    QString dictName;
    void loadWords() {
        // open folder having name dictName
    }
    QList<QString> getListWordsWithPrefix(const QString &prefix, int maxResultLength) {
        trie->searchPrefix();
    }
};

#endif // DICTIONARYDATASTRUCTURE_H
