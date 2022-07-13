#ifndef FAVORITE_H
#define FAVORITE_H

#include "IFavorite.h"
#include "Trie.h"
#include "CSV.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>

class Favorite : public IFavorite {
   public:
    Favorite() : trie{new Trie<QString>()} {
        loadData();
    }
    ~Favorite() {
        delete trie;
    }

    bool loadData() {
        QString favoritePath = getFavoritePath();
        QFile fin;
        QTextStream in;

        fin.setFileName(favoritePath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);

        QString line, _wordDictName, _defiPath;
        while(!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _wordDictName, _defiPath);
            (*trie)[_wordDictName] = _defiPath;
        }
        fin.close();
        return true;
    }
    bool addWord(const QString &word, const QString &dictName, const QString& filePath) {
        QString wordDictName = QString("%1 (%2)").arg(word).arg(dictName);
        if (trie->contains(wordDictName)) return false;

        (*trie)[wordDictName] = filePath;
        QString favoritePath = getFavoritePath();

        QFile fout;
        QTextStream out;

        fout.setFileName(favoritePath);
        if (!fout.open(QFile::WriteOnly | QFile::Text | QFile::Append)) return false;

        out.setDevice(&fout);
        out << CSV::writeLine(wordDictName, filePath) << '\n';
        fout.close();
        return true;
    }
    bool containsWord(const QString& word) {
        return trie->contains(word);
    }
    bool removeWord(const QString &wordDictName) {
        if (!trie->contains(wordDictName)) return false;
        trie->remove(wordDictName);

        QString favoritePath = getFavoritePath();
        QFile fin, fout;
        QTextStream in, out;
        QList<QString> listWordDictNames, listDefinitionPaths;
        QString line, _wordDictname, _defiPath;
        int wordIndex;

        fin.setFileName(favoritePath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _wordDictname, _defiPath);
            listWordDictNames.push_back(_wordDictname);
            listDefinitionPaths.push_back(_defiPath);
        }
        fin.close();

        wordIndex = listWordDictNames.indexOf(wordDictName);
        if (wordIndex == -1) return false;
        listWordDictNames.removeAt(wordIndex);
        listDefinitionPaths.removeAt(wordIndex);

        fout.setFileName(favoritePath);
        if (!fout.open(QFile::WriteOnly | QFile::Text)) return false;
        out.setDevice(&fout);
        for (int i = 0; i < listWordDictNames.size(); ++i) {
            out << CSV::writeLine(listWordDictNames[i], listDefinitionPaths[i]) << '\n';
        }
        fout.close();
        return true;
    }
    QList<QString> getFavoriteWordsWithPrefix(const QString &prefix, int maxResultLength) {
        return trie->searchPrefix(prefix, maxResultLength);
    }
    QString getFavoriteWordDefinition(const QString &wordDictName) {
        if (!trie->contains(wordDictName)) return QString();
        QString defiPath = (*trie)[wordDictName];
        QString word = getWord(wordDictName);
        QFile fin;
        QTextStream in;
        QString line, _word, _defi;
        fin.setFileName(defiPath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return QString();
        in.setDevice(&fin);
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _word, _defi);
            if (_word == word) {
                fin.close();
                return _defi;
            }
        }
        fin.close();
        return QString();
    }
    QString getWord(const QString& wordDictName) {
        return wordDictName.first(wordDictName.lastIndexOf('(') - 1);
    }
    QString getFavoritePath() {
        return "data/favorite/index.csv";
    }
   private:
    Trie<QString>* trie;
};

#endif  // FAVORITE_H
