#ifndef TRIE_H
#define TRIE_H

#include "Map.h"
#include <QString>
#include <QChar>
#include <QList>
#include <functional>

template <class T>
class Trie
{
private:
    class TrieNode {
    public:
        bool flag;
        T* value;
        Map<QChar, TrieNode*> next;
        TrieNode() : flag{0}, value{nullptr}, next{} {}
        bool isLeaf() {
            return next.empty();
        }
    };

    TrieNode* root;

    void clear(TrieNode*& root) {
        for (auto& ch : root->next.keys()) {
            clear(root->next[ch]);
            delete root->next[ch];
            root->next[ch] = nullptr;
        }
        if (root->value) delete root->value;
    }

    TrieNode* find(const QString& word) {
        TrieNode* ptr = root;
        for (auto& ch : word) {
            if (!ptr->next.contains(ch)) return nullptr;
            ptr = ptr->next[ch];
        }
        return ptr;
    }
public:
    Trie() : root{new TrieNode()} {}
    ~Trie() {
        clear();
        delete root;
    }

    void clear() {
        clear(root);
    }

    TrieNode* insert(const QString& word, const T& value) {
        TrieNode* ptr = root;
        for (auto& ch : word) {
            if (!ptr->next.contains(ch))
                ptr->next[ch] = new TrieNode();
            ptr = ptr->next[ch];
        }
        ptr->flag = true;
        ptr->value = new T(value);
        return ptr;
    }

    bool contains(const QString& word) {
        auto ptr = find(word);
        if (ptr) return ptr->flag;
        else return false;
    }

    bool remove(const QString& word) {
        QList<TrieNode*> stackNodes;
        TrieNode* ptr = root;
        stackNodes.push_back(ptr);
        for (auto& ch : word) {
            if (!ptr->next.contains(ch)) return false;
            ptr = ptr->next[ch];
            stackNodes.push_back(ptr);
        }
        if (!ptr->flag) return false;
        ptr->flag = false;
        for (int i = stackNodes.size() - 1; i > 0; --i) {
            TrieNode* cur = stackNodes[i];
            TrieNode* par = stackNodes[i - 1];
            QChar curChar = word[i - 1];
            if (cur->isLeaf() && !cur->flag) {
                par->next.remove(curChar);
                delete cur;
            } else break;
        }
        return true;
    }

    T& value(const QString& word) {
        auto res = find(word);
        if (res && res->value) {
            return *res->value;
        } else {
            return *insert(word, T{})->value;
        }
    }

    T& operator[](const QString& word) {
        return this->value(word);
    }

    QList<QString> searchPrefix(const QString& prefix, int maxResultLength) const {
        QList<QString> result;
        TrieNode* ptr = root;
        for (auto& ch : prefix) {
            if (!ptr->next.contains(ch)) return result;
            ptr = ptr->next[ch];
        }
        std::function<void(TrieNode*, const QString&)> dfs = [&](TrieNode* root, const QString& suffix) {
            if (root == nullptr) return;
            if (result.size() >= maxResultLength) return;
            if (root->flag) result.push_back(prefix + suffix);
            for (auto& ch : root->next.keys()) {
                dfs(root->next[ch], suffix + ch);
            }
        };
        dfs(ptr, "");
        return result;
    }
};

#endif // TRIE_H
