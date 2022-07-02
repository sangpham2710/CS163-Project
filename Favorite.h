#ifndef FAVORITE_H
#define FAVORITE_H

#include "IFavorite.h"
#include "Trie.h"
#include "QFile"
#include "QTextStream"
#include "CSV.h"

class Favorite : public IFavorite {
public:
    Favorite() {
        trie = new Trie<QString>();
        loadWord();
    }
    ~Favorite() {
        delete trie;
    }
    bool loadWord() {
        QString favoritePath = getFavoritePath();
        QFile fin;
        QTextStream in;

        fin.setFileName(favoritePath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);

        QString line, _word, _defiPath;
        while(!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _word, _defiPath);
            (*trie)[_word + getDictName(_defiPath)] = _defiPath;
        }
        fin.close();
        return true;
    }
    bool addWord(const QString &word, const QString &filePath) {

        QString key = word + getDictName(filePath);
        if (trie->contains(key)) return false;

        (*trie)[key] = filePath;
        QString favoritePath = getFavoritePath();

        QFile fout;
        QTextStream out;

        fout.setFileName(favoritePath);
        if (!fout.open(QFile::WriteOnly | QFile::Text | QFile::Append)) return false;

        out.setDevice(&fout);
        out << CSV::writeLine(word, filePath) << '\n';
        fout.close();

        return true;
    }
    bool removeWord(const QString &word, const QString &filePath) {
        QString key = word + getDictName(filePath);
        if (!trie->contains(key)) return false;

        trie->remove(key);

        // remove word in file
        QString favoritePath = getFavoritePath();
        QFile fin, fout;
        QTextStream in, out;
        QVector<QString> listWords, listPaths;
        QString line, _word, _path;
        int wordIndex;

        fin.setFileName(favoritePath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _word, _path);
            listWords.push_back(_word);
            listPaths.push_back(_path);
        }
        fin.close();

        wordIndex = listWords.indexOf(word);
        if (wordIndex == -1) return false;
        listWords.removeAt(wordIndex);
        listPaths.removeAt(wordIndex);

        fout.setFileName(favoritePath);
        if (!fout.open(QFile::WriteOnly | QFile::Text)) return false;
        out.setDevice(&fout);
        for (int i = 0; i < listWords.size(); ++i) {
            out << CSV::writeLine(listWords[i], listPaths[i]) << '\n';
        }
        fout.close();
        return true;
    }
    QList<QString> getFavoriteWordsWithPrefix(const QString &prefix, int maxResultLength) {
        return trie->searchPrefix(prefix, maxResultLength);
    }
    QString getFavoriteWordDefinition(const QString &word, const QString &filePath) {
        QString key = word + getDictName(filePath);
        if (!trie->contains(key)) return QString();

        QString defiPath = (*trie)[key];
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
    QString getFavoritePath() {
        return "data/favorite/index.csv";
    }

    QString getDictName(QString filePath) {
        QString dictName = "(";
        for (int i = 11; filePath[i] != '/'; ++i) { // data/dicts/Eng-Eng/...
            dictName += filePath[i];
        }
        return dictName + ')';
    }
private:
    Trie<QString>* trie;
};

#endif // FAVORITE_H
