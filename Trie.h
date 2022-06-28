#ifndef TRIE_H
#define TRIE_H

#include "Map.h"
#include <QString>
#include <QChar>
#include <QVector>
#include <functional>

class Trie
{
private:
    class TrieNode {
    public:
        bool flag;
        Map<QChar, TrieNode*> next;
        TrieNode() : flag{0}, next{} {}
    };
    TrieNode* root;
    void clear(TrieNode*& root) {
        for (auto& ch : root->next.keys()) {
            clear(root->next[ch]);
            delete root->next[ch];
            root->next[ch] = nullptr;
        }
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
    void insert(const QString& word) {
        TrieNode* ptr = root;
        for (auto& ch : word) {
            if (!ptr->next.contains(ch))
                ptr->next[ch] = new TrieNode();
            ptr = ptr->next[ch];
        }
        ptr->flag = true;
    }
    bool search(const QString& word) {
        TrieNode* ptr = root;
        for (auto& ch : word) {
            if (!ptr->next.contains(ch)) return false;
            ptr = ptr->next[ch];
        }
        return ptr->flag;
    }
    QVector<QString> searchPrefix(QString prefix) {
        QVector<QString> result;
        TrieNode* ptr = root;
        for (auto& ch : prefix) {
            if (!ptr->next.contains(ch)) return result;
            ptr = ptr->next[ch];
        }

        std::function<void(TrieNode*, QString)> dfs = [&](TrieNode* root, QString suffix) {
            if (root == nullptr) return;
            if (root->flag) {
                result.push_back(prefix + suffix);
            }
            for (auto& ch : root->next.keys()) {
                dfs(root->next[ch], suffix + ch);
            }
        };
        dfs(ptr, "");
        return result;
    }
};

#endif // TRIE_H
