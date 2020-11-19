#ifndef ADS_LABA4_CHAINHASH_H
#define ADS_LABA4_CHAINHASH_H

#include <iostream>
#include "HashTable.h"

using namespace std;

template<class Key = int, class Data = int>
class ChainHash : public HashTable<Key, Data> {
private:
    class Chain {
    private:
        class Node {
        public:
            Key key;
            Data data;
            Node *next;

            Node(Key key1, Data data1, Node *node = nullptr);
        };

        Node *head;
        int size;
        int view_count;

    public:
        Chain();

        Chain(Chain &chain);

        ~Chain();

        int getSize();

        int getViewCount();

        bool add(Key key, Data data);

        bool del(Key key);

        Data get(Key key);

        void show();

    };

    Chain **arr;

    int nearPow2(int x);

public:
    explicit ChainHash(int _size);

    ChainHash(ChainHash<Key, Data> &ch);

    ~ChainHash();

    bool insert(Key key, Data data);

    bool remove(Key key);

    Data search(Key key);

    void clear();

    void printHash();

};

template<class Key, class Data>
int ChainHash<Key, Data>::nearPow2(int x) {
    if (x == 0) return 1;
    int res = 1;
    while (x > 0) {
        res <<= 1;
        x >>= 1;
    }
    return res >>= 1;
}

template<class Key, class Data>
ChainHash<Key, Data>::ChainHash(int _size) {
    this->size = nearPow2(_size);
    arr = new Chain*[this->size];
    for (int i = 0; i < this->size; ++i) {
        arr[i] = nullptr;
    }
    this->count = 0;
    this->view_count = 0;
}

template<class Key, class Data>
ChainHash<Key, Data>::ChainHash(ChainHash<Key, Data> &ch) {
    this->size = ch.size;
    arr = new Chain[this->size];
    for (int i = 0; i < this->size; ++i) {
        arr[i] = ch.arr[i];
    }
    this->count = ch.count;
    this->view_count = 0;
}

template<class Key, class Data>
ChainHash<Key, Data>::~ChainHash() {
    clear();
}

template<class Key, class Data>
void ChainHash<Key, Data>::clear() {
    for (int i = 0; i < this->size; ++i) {
        delete arr[i];
    }
    delete arr;
    this->size = 0;
    this->count = 0;
}

template<class Key, class Data>
bool ChainHash<Key, Data>::insert(Key key, Data data) {
    int hashKey = this->hash(this->convert(key));
    if (arr[hashKey] == nullptr) {
        arr[hashKey] = new Chain();
    }
    bool flag = arr[hashKey]->add(key, data);
    this->view_count = arr[hashKey]->getViewCount();
    if (!flag) return flag;
    this->count++;
    return flag;
}

template<class Key, class Data>
bool ChainHash<Key, Data>::remove(Key key) {
    if (this->isEmpty()) return false;
    int hashKey = this->hash(this->convert(key));
    if (arr[hashKey] == nullptr) return false;
    bool flag = arr[hashKey]->del(key);
    this->view_count = arr[hashKey]->getViewCount();
    if (!flag) return flag;
    if (!arr[hashKey]->getSize()) {
        delete arr[hashKey];
        arr[hashKey] = nullptr;
    }
    this->count--;
    return flag;
}

template<class Key, class Data>
Data ChainHash<Key, Data>::search(Key key) {
    if (this->isEmpty()) throw runtime_error("EXCEPTION");
    int hashKey = this->hash(this->convert(key));
    if (arr[hashKey] == nullptr) throw runtime_error("EXCEPTION");
    try {
        return arr[hashKey]->get(key);
    } catch (runtime_error e) {
        throw e;
    }
}

template<class Key, class Data>
void ChainHash<Key, Data>::printHash() {
    if (this->isEmpty()) return;
    for (int i = 0; i < this->size; ++i) {
        if (arr[i]) {
            cout << i << ") ";
            arr[i]->show();
        }
    }

}

template<class Key, class Data>
ChainHash<Key, Data>::Chain::Node::Node(Key key1, Data data1, ChainHash::Chain::Node *node) {
    key = key1;
    data = data1;
    next = node;
}

template<class Key, class Data>
ChainHash<Key, Data>::Chain::Chain() {
    head = nullptr;
    size = 0;
    view_count = 0;
}

template<class Key, class Data>
ChainHash<Key, Data>::Chain::Chain(ChainHash::Chain &chain) {
    if (chain.head) {
        Node *tmp = chain.head;
        head = new Node(tmp->key, tmp->data);
        Node *p = head;
        tmp = tmp->next;
        while (tmp) {
            Node *newNode = new Node(tmp->key, tmp->data);
            p->next = newNode;
            tmp = tmp->next;
            p = p->next;
        }
        size = chain.size;
        view_count = chain.view_count;
    }
}

template<class Key, class Data>
ChainHash<Key, Data>::Chain::~Chain() {
    Node *p = head;
    while (p) {
        Node *prev = p;
        p = p->next;
        delete prev;
    }
    size = 0;
    view_count = 0;
}

template<class Key, class Data>
int ChainHash<Key, Data>::Chain::getSize() {
    return size;
}

template<class Key, class Data>
int ChainHash<Key, Data>::Chain::getViewCount() {
    int tmp = view_count;
    view_count = 0;
    return tmp;
}

template<class Key, class Data>
bool ChainHash<Key, Data>::Chain::add(Key key, Data data) {
    if (!head) {
        head = new Node(key, data);
        size++;
        view_count++;
        return true;
    }
    Node *tmp = head;
    while (tmp) {
        view_count++;
        if (tmp->data == data) return false;
        if (!tmp->next) break;
        tmp = tmp->next;
    }
    Node *node = new Node(key, data);
    tmp->next = node;
    size++;
    return true;
}

template<class Key, class Data>
bool ChainHash<Key, Data>::Chain::del(Key key) {
    if (!head) return false;
    Node *tmp = head;
    Node *prev;
    while (tmp) {
        view_count++;
        if (tmp->key == key)
            break;
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp) return false;
    if (tmp == head)
        head = head->next;
    else
        prev->next = tmp->next;
    delete tmp;
    size--;
    return true;
}

template<class Key, class Data>
Data ChainHash<Key, Data>::Chain::get(Key key) {
    if (!head) throw runtime_error("EXCEPTION");
    Node *tmp = head;
    while (tmp) {
        view_count++;
        if (tmp->key == key)
            break;
        tmp = tmp->next;
    }
    if (!tmp) throw runtime_error("EXCEPTION");
    return tmp->data;
}

template<class Key, class Data>
void ChainHash<Key, Data>::Chain::show() {
    if (!head) return;
    Node *tmp = head;
    while (tmp) {
        cout << tmp->key << "(" << tmp->data << ") ";
        tmp = tmp->next;
    }
    cout << endl;
}


#endif //ADS_LABA4_CHAINHASH_H
