#ifndef DICTIONARYDATASTRUCTURE_H
#define DICTIONARYDATASTRUCTURE_H

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <chrono>
#include <random>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

#include "CSV.h"
#include "Trie.h"

using std::string;
using std::ifstream;
using std::vector;
using std::pair;
using std::sort;

class DictionaryDataStructure {
   public:
    DictionaryDataStructure() : trie{new Trie<QString>()} {}
    DictionaryDataStructure(const QString& dictName)
        : trie{new Trie<QString>()}, dictName{dictName} {
        loadWords();
    }
    ~DictionaryDataStructure() { delete trie; }
    QString getDictionaryName() { return dictName; }
    int getNumWords() { return trie->size(); }
    bool loadWords() {
        trie->clear();
        QString wordPath = getFullWordPath();
        // load words from file
        QFile fin(wordPath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        QTextStream in(&fin);
        QString line, word, definitionFileName;
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, word, definitionFileName);
            (*trie)[word] = definitionFileName;
        }
        fin.close();
        return true;
    }
    QList<QString> getListWordsWithPrefix(const QString& prefix,
                                          int maxResultLength) {
        return trie->searchPrefix(prefix, maxResultLength);
    }
    bool addWord(const QString& word, const QString& definition) {
        qDebug() << trie->contains(word) << '\n';
        if (trie->contains(word)) return false;
        (*trie)[word] = "tmp";
        QString wordPath = getFullWordPath();
        QString definitionPath =
            QString("data/dicts/%1/defis/tmp.csv").arg(dictName);

        // append definition into word/index.csv and defis/tmp.csv
        QFile fout;
        QTextStream out;

        fout.setFileName(wordPath);
        if (!fout.open(QFile::WriteOnly | QFile::Text | QFile::Append))
            return false;

        out.setDevice(&fout);
        out << CSV::writeLine(word, "tmp") << '\n';
        fout.close();

        fout.setFileName(definitionPath);
        if (!fout.open(QFile::WriteOnly | QFile::Text | QFile::Append))
            return false;
        out.setDevice(&fout);
        out << CSV::writeLine(word, definition) << '\n';
        fout.close();
        return true;
    }
    bool editWord(const QString& word, const QString& newDefinition) {
        if (!trie->contains(word)) return false;
        QString definitionPath = getFullDefinitionPath(word);
        // edit word in file using path variable
        QList<QString> listWords;
        QList<QString> listDefinitions;

        QFile fin(definitionPath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;

        QTextStream in(&fin);
        QString line, _word, _definition;
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _word, _definition);
            listWords.push_back(_word);
            listDefinitions.push_back(_definition);
        }
        fin.close();

        int wordIndex = listWords.indexOf(word);
        if (wordIndex == -1) return false;
        listDefinitions[wordIndex] = newDefinition;

        QFile fout(definitionPath);
        if (!fout.open(QFile::WriteOnly | QFile::Text)) return false;
        QTextStream out(&fout);

        for (int i = 0; i < listWords.size(); ++i) {
            out << CSV::writeLine(listWords[i], listDefinitions[i]) << '\n';
        }

        fout.close();

        return true;
    }
    bool removeWord(const QString& word) {
        if (!trie->contains(word)) return false;
        QString wordPath = getFullWordPath();
        QString definitionPath = getFullDefinitionPath(word);
        trie->remove(word);
        QList<QString> listWords;
        QList<QString> listDefinitions;
        // remove word in file
        QFile fin, fout;
        QTextStream in, out;
        QString line, _word, _definition;
        int wordIndex;

        fin.setFileName(wordPath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _word, _definition);
            listWords.push_back(_word);
            listDefinitions.push_back(_definition);
        }
        fin.close();

        wordIndex = listWords.indexOf(word);
        if (wordIndex == -1) return false;
        listWords.removeAt(wordIndex);
        listDefinitions.removeAt(wordIndex);

        fout.setFileName(wordPath);
        if (!fout.open(QFile::WriteOnly | QFile::Text)) return false;
        out.setDevice(&fout);
        for (int i = 0; i < listWords.size(); ++i) {
            out << CSV::writeLine(listWords[i], listDefinitions[i]) << '\n';
        }
        fout.close();

        // remove definition in file
        listWords.clear();
        listDefinitions.clear();
        fin.setFileName(definitionPath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return false;
        in.setDevice(&fin);
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _word, _definition);
            listWords.push_back(_word);
            listDefinitions.push_back(_definition);
        }
        fin.close();

        wordIndex = listWords.indexOf(word);
        if (wordIndex == -1) return false;
        listWords.removeAt(wordIndex);
        listDefinitions.removeAt(wordIndex);

        fout.setFileName(definitionPath);
        if (!fout.open(QFile::WriteOnly | QFile::Text)) return false;
        out.setDevice(&fout);
        for (int i = 0; i < listWords.size(); ++i) {
            out << CSV::writeLine(listWords[i], listDefinitions[i]) << '\n';
        }
        fout.close();
        return true;
    }
    QString getRandomWord() {
        std::mt19937 rng(
            std::chrono::steady_clock::now().time_since_epoch().count());
        int wordIndex = rng() % trie->size();
        int currentIndex = 0;
        QFile fin;
        QTextStream in;
        QString line, _word, _definition;
        QString wordPath = getFullWordPath();
        fin.setFileName(wordPath);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return QString();
        in.setDevice(&fin);
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _word, _definition);
            if (currentIndex++ == wordIndex) {
                fin.close();
                return _word;
            }
        }
        fin.close();
        return QString();
    }
    QString getDefinition(const QString& word) {
        if (!trie->contains(word)) return QString();
        QString path = getFullDefinitionPath(word);
        // get definition of word in file using path variable
        QFile fin(path);
        if (!fin.open(QFile::ReadOnly | QFile::Text)) return QString();
        QTextStream in(&fin);
        QString line, _word, _definition;
        while (!in.atEnd()) {
            line = in.readLine();
            CSV::readLine(line, _word, _definition);
            if (_word == word) {
                fin.close();
                return _definition;
            }
        }
        fin.close();
        return QString();
    }
    QList<QString> getListWordsHaveDefinition(const QString& token,
                                              int maxResultLength) {
        // read the number of files first
        string defiInfoPath = QString("data/dicts/%1/defis/info.txt").arg(dictName).toStdString();
        ifstream ifs;
        ifs.open(defiInfoPath);
        if (!ifs.is_open()) return {};
        int maxLines, numFiles;
        ifs >> maxLines >> numFiles;
        ifs.close();
        vector<pair<int, QString>> listOccurences;
        // then read each of the definition files
        for (int fileId = 0; fileId < numFiles; ++fileId) {
            QFile fin(QString("data/dicts/%1/defis/%2.csv").arg(dictName).arg(QString::number(fileId)));
            if (!fin.open(QFile::ReadOnly | QFile::Text)) return {};
            QTextStream in(&fin);
            QString line, _word, _definition;
            while (!in.atEnd()) {
                line = in.readLine();
                CSV::readLine(line, _word, _definition);
                int numOccurences = countOccurences(token, _definition);
                if (numOccurences > 0)
                    listOccurences.push_back({numOccurences, std::move(_word)});
            }
            fin.close();
        }
        sort(listOccurences.rbegin(), listOccurences.rend());
        QList<QString> result;
        for (int i = 0; i < std::min((int)listOccurences.size(), maxResultLength); ++i) {
            result.push_back(listOccurences[i].second);
        }
        return result;
    }
    int countOccurences(const QString& pattern, const QString& text) {
        QString s = pattern + "☺" + text;
        int n = (int) s.size();
        QList<int> z(n);
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r)
                z[i] = std::min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
        int result = 0;
        for (int i = 0; i < text.size(); ++i) {
            if (z[i + pattern.size() + 1] == pattern.size()) ++result;
        }
        return result;
    }
    QString getFullWordPath() {
        return QString(
                   "data/dicts/%1/"
                   "words/index.csv")
            .arg(dictName);
    }
    QString getFullDefinitionPath(const QString& word) {
        if (!trie->contains(word)) return "";
        QString definition = (*trie)[word];
        return QString(
                   "data/dicts/%1/"
                   "defis/%2.csv")
            .arg(dictName)
            .arg(definition);
    }

   private:
    Trie<QString>* trie;
    QString dictName;
};

#endif  // DICTIONARYDATASTRUCTURE_H
