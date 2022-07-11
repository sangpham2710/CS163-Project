#ifndef APP_H
#define APP_H

#include "Dictionary.h"
#include "Favorite.h"
#include "History.h"
#include "IDictionary.h"
#include "IFavorite.h"
#include "IHistory.h"

class App {
   public:
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    ~App() {
        delete dictionary;
        delete favorite;
        delete history;
    }
    static App& get() {
        static App app;
        return app;
    }
    // dictionary functionalities
    QList<QString> getListWordsWithPrefix(const QString& prefix) {
        return dictionary->getListWordsWithPrefix(prefix);
    }
    QString getCurrentDictionaryName() {
        return dictionary->getCurrentDictionaryName();
    }
    QList<QString> getListDictionaries() {
        return dictionary->getListDictionaries();
    }
    bool changeDictionary(const QString& dictName) {
        return dictionary->changeDictionary(dictName);
    }
    bool addWord(const QString& word, const QString& definition) {
        return dictionary->addWord(word, definition);
    }
    bool editWord(const QString& word, const QString& newDefinition) {
        return dictionary->editWord(word, newDefinition);
    }
    bool removeWord(const QString& word) {
        auto dictDefi = dictionary->getDefinition(word);
        if (!dictionary->removeWord(word)) return false;
        if (favorite->getFavoriteWordDefinition(word) == dictDefi) {
            if (!favorite->removeWord(word)) return false;
        }
        return true;
    }
    bool resetDictionary() { return dictionary->reset(); }
    QString getDefinition(const QString& word) {
        history->add(word);
        return dictionary->getDefinition(word);
    }
    QString getRandomWord() {
        return dictionary->getRandomWord();
    }
    QList<QString> getWordAnd4Definitions() {
        QList<QString> words;
        QList<QString> defis;
        for (int i = 0; i < 4; ++i) {
            words.push_back(dictionary->getRandomWord());
            defis.push_back(dictionary->getDefinition(words.back()));
        }
        return {words[0], defis[0], defis[1], defis[2], defis[3]};
    }
    QList<QString> getDefinitionAnd4Words() {
        QList<QString> words;
        QList<QString> defis;
        for (int i = 0; i < 4; ++i) {
            words.push_back(dictionary->getRandomWord());
            defis.push_back(dictionary->getDefinition(words.back()));
        }
        return {defis[0], words[0], words[1], words[2], words[3]};
    }
    QList<QString> getListWordsHaveDefinition(const QString& token) {
        history->add(token);
        return dictionary->getListWordsHaveDefinition(token);
    }
    // favorite functionalities
    bool addWordToFavorite(const QString& word) {
        return favorite->addWord(word, getCurrentDictionaryName(), dictionary->getFullDefinitionPath(word));
    }
    bool isWordInFavorite(const QString& word) {
        return favorite->containsWord(word, getCurrentDictionaryName());
    }
    bool removeWordFromFavorite(const QString& word, bool containsDictName = false) {
        if (containsDictName) {
            return favorite->removeWord(word);
        } else {
            return favorite->removeWord(QString("%1 (%2)").arg(word).arg(getCurrentDictionaryName()));
        }
    }
    QList<QString> getFavoriteWordsWithPrefix(const QString& prefix) {
        return favorite->getFavoriteWordsWithPrefix(prefix);
    }
    QString getFavoriteWordDefinition(const QString& wordDictName) {
        return favorite->getFavoriteWordDefinition(wordDictName);
    }
    // history functionalities
    QList<QString> getHistory() { return history->getHistory(); }

   private:
    App() {
        dictionary = new Dictionary();
        favorite = new Favorite();
        history = new History();
    }

    IDictionary* dictionary;
    IFavorite* favorite;
    IHistory* history;
};

#endif  // APP_H
