#ifndef MAP_H
#define MAP_H

#include <QList>
#include <algorithm>

template <typename Key, typename T>
class Map {
public:
    struct Node {
        Key key;
        T* value;
        Node *left;
        Node *right;
        int height;
        Node(const Key &ele, T *val, Node *lt, Node *rt, int h = 0)
                : key{ele}, value{val}, left{lt}, right{rt}, height{h} {}
        Node(Key &&ele, T *val, Node *lt, Node *rt, int h = 0)
                : key{std::move(ele)}, value{val}, left{lt}, right{rt}, height{h} {}
    };
    Map() : root{nullptr} {}
    ~Map() { clear(root); }

    bool empty() const { return root == nullptr; }
    void clear() { clear(root); }
    bool contains(const Key &x) const { return contains(root, x); }
    void insert(const Key &x, const T &value) { insert(root, x, value); }
    void remove(const Key &x) { remove(root, x); }
    T& value(const Key &x) {
        auto res = find(root, x);
        if (res) {
            return *res->value;
        } else {
            return *insert(root, x, T{})->value;
        }
    }
    T& operator[](const Key &x) {
        return this->value(x);
    }
    QList<Key> keys() {
        QList<Key> result;
        getKeys(root, result);
        return result;
    }

private:
    Node *root;

    static const int ALLOWED_IMBALANCE = 1;

    int height(Node *t) const { return t == nullptr ? -1 : t->height; }

    bool contains(Node *t, const Key &x) const {
        if (t == nullptr)
            return false;
        else if (x < t->key)
            return contains(t->left, x);
        else if (x > t->key)
            return contains(t->right, x);
        else
            return true;
    }

    Node *insert(Node *&t, const Key &x, const T &value) {
        if (t == nullptr)
            return t = new Node{x, new T(value), nullptr, nullptr};
        else if (x < t->key)
            return insert(t->left, x, value);
        else if (t->key < x)
            return insert(t->right, x, value);
        balance(t);
    }

    void remove(Node *&t, const Key &x) {
        if (t == nullptr)
            return;
        else if (x < t->key)
            remove(t->left, x);
        else if (t->key < x)
            remove(t->right, x);
        else if (t->left && t->right) {
            t->key = findMin(t->right)->key;
            remove(t->right, t->key);
        } else {
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            if (oldNode->value) {
                delete oldNode->value;
            }
            delete oldNode;
        }
        balance(t);
    }

    void clear(Node *&t) {
        if (t == nullptr) return;
        clear(t->left);
        clear(t->right);
        if (t->value) {
            delete t->value;
        }
        delete t;
        t = nullptr;
    }

    void getKeys(Node *t, QList<Key>& result) {
        if (t == nullptr) return;
        getKeys(t->left, result);
        result.push_back(t->key);
        getKeys(t->right, result);
    }

    void balance(Node *&t) {
        if (t == nullptr) return;
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    void rotateWithLeftChild(Node *&k2) {
        Node *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(Node *&k2) {
        Node *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(k2->height, height(k1->right)) + 1;
        k2 = k1;
    }

    void doubleWithLeftChild(Node *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(Node *&k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    Node *find(Node *t, const Key &x) const {
        if (t == nullptr)
            return nullptr;
        else if (x < t->key)
            return find(t->left, x);
        else if (x > t->key)
            return find(t->right, x);
        else
            return t;
    }
};

#endif // MAP_H
