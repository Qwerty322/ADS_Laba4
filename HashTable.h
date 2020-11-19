#ifndef ADS_LABA4_HASHTABLE_H
#define ADS_LABA4_HASHTABLE_H
#include <iostream>

using namespace std;

template<class Key = int, class Data = int>
class HashTable {
protected:
    int size;
    int count;
    int view_count;

    int convert(Key key);

    int hash(int key);

public:
    int getCount();

    int getSize();

    int getViewCount();

    bool isEmpty();

    virtual void printHash() = 0;

    virtual Data search(Key key) = 0;

    virtual bool insert(Key key, Data data) = 0;

    virtual bool remove(Key key) = 0;

    virtual void clear() = 0;
};

template<class Key, class Data>
int HashTable<Key, Data>::convert(Key key) {
    int pair1 = key / 1000000;
    int pair2 = key / 1000 % 1000;
    int pair3 = key % 1000;
    return (pair1 ^ 1 + pair2 ^ 2 + pair3 ^ 3) % 1000;
}

template<class Key, class Data>
int HashTable<Key, Data>::hash(int key) {
    return key % size;
}

template<class Key, class Data>
int HashTable<Key, Data>::getCount() {
    return count;
}

template<class Key, class Data>
int HashTable<Key, Data>::getSize() {
    return size;
}

template<class Key, class Data>
int HashTable<Key, Data>::getViewCount() {
    int tmp = view_count;
    view_count = 0;
    return tmp;
}

template<class Key, class Data>
bool HashTable<Key, Data>::isEmpty() {
    return count == 0;
}


#endif //ADS_LABA4_HASHTABLE_H
