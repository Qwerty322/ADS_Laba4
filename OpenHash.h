#ifndef ADS_LABA4_OPENHASH_H
#define ADS_LABA4_OPENHASH_H

#include <iostream>
#include "HashTable.h"

using namespace std;

enum Status {
    FREE, BUSY, DELETED
};

template<class Key = double , class Data = int>
class OpenHash : public HashTable<Key, Data> {
private:
    class Cell {
    public:
        Key key;
        Data data;
        Status status;

        Cell();
    };

    Cell *array;

    int upperPow2(int x);

    int squadZond(Key key, int i);


public:
    class Iterator : public HashTable<Key, Data>::Iterator {
    public:
        OpenHash<Key, Data> *table;

        Cell *current;

        explicit Iterator(HashTable<Key, Data> *ch);

        void checkException() override;

        void toBegin() override;

        void toEnd() override;

        Data &operator*() override;

        void operator++() override;

        void operator++(int) override;

        bool operator==(typename HashTable<Key, Data>::Iterator *it) override;

    };

    explicit OpenHash(int _size);

    OpenHash(OpenHash<Key, Data> &ch);

    ~OpenHash() override;

    bool insert(Key key, Data data) override;

    bool remove(Key key) override;

    Data search(Key key) override;

    void clear() override;

    void printHash() override;

    typename HashTable<Key, Data>::Iterator *begin() override;

    typename HashTable<Key, Data>::Iterator *end() override;
};

template<class Key, class Data>
OpenHash<Key, Data>::Iterator::Iterator(HashTable<Key, Data> *ch) {
    this->table = (OpenHash<Key, Data> *) ch;
    this->current = nullptr;
    this->index = 0;
}

template<class Key, class Data>
void OpenHash<Key, Data>::Iterator::checkException() {
    if (!table || !current) throw runtime_error("EXCEPTION!");
}

template<class Key, class Data>
void OpenHash<Key, Data>::Iterator::toBegin() {
    if (!table) throw runtime_error("EXCEPTION!");
    for (int i = 0; i < table->size; ++i) {
        if (table->array[i].status == BUSY) {
            this->index = i;
            this->current = &table->array[i];
            return;
        }
    }
}

template<class Key, class Data>
void OpenHash<Key, Data>::Iterator::toEnd() {
    if (!table) throw runtime_error("EXCEPTION!");
    for (int i = table->size - 1; i >= 0; --i) {
        if (table->array[i].status == BUSY) {
            this->index = i;
            this->current = &table->array[i];
            return;
        }
    }
}

template<class Key, class Data>
Data &OpenHash<Key, Data>::Iterator::operator*() {
    checkException();
    if (!current) throw runtime_error("EXCEPTION!");
    return current->data;
}

template<class Key, class Data>
void OpenHash<Key, Data>::Iterator::operator++() {
    checkException();
    if (this->index == table->size - 1) throw runtime_error("EXCEPTION!");
    for (int i = this->index + 1; i < table->size; ++i) {
        if (table->array[i].status == BUSY) {
            this->index = i;
            this->current = &table->array[i];
            return;
        }
    }
    throw runtime_error("EXCEPTION!");
}

template<class Key, class Data>
void OpenHash<Key, Data>::Iterator::operator++(int) {
    checkException();
    if (this->index == table->size - 1) throw runtime_error("EXCEPTION!");
    for (int i = this->index + 1; i < table->size; ++i) {
        if (table->array[i].status == BUSY) {
            this->index = i;
            this->current = &table->array[i];
            return;
        }
    }
    throw runtime_error("EXCEPTION!");
}

template<class Key, class Data>
bool OpenHash<Key, Data>::Iterator::operator==(typename HashTable<Key, Data>::Iterator *it) {
    return this->current == static_cast<OpenHash<>::Iterator *>(it)->current;
}


template<class Key, class Data>
int OpenHash<Key, Data>::upperPow2(int x) {
    x--;
    for (int p = 1; p < 32; p <<= 1) x |= (x >> p);
    return ++x;
}

template<class Key, class Data>
int OpenHash<Key, Data>::squadZond(Key key, int i) {
    float c1 = 0.5;
    float c2 = 0.5;
    return (int) (this->hash(key) + c1 * i + c2 * i * i) % this->size;
}

template<class Key, class Data>
OpenHash<Key, Data>::OpenHash(int _size) {
    this->isChain = 0;
    this->size = upperPow2(_size);
    array = new Cell[this->size];
    for (int i = 0; i < this->size; ++i) {
        array[i].status = FREE;
    }
    this->count = 0;
    this->view_count = 0;
}

template<class Key, class Data>
void OpenHash<Key, Data>::clear() {
    if (this->isEmpty()) return;
    for (int i = 0; i < this->size; i++) {
        array[i].status = FREE;
    }
    this->count = 0;
}

template<class Key, class Data>
OpenHash<Key, Data>::~OpenHash() {
    delete[] array;
}

template<class Key, class Data>
OpenHash<Key, Data>::OpenHash(OpenHash<Key, Data> &ch) {
    this->isChain = 0;
    this->size = ch.size;
    array = new Cell[this->size];
    for (int i = 0; i < this->size; ++i) {
        array[i] = ch.array[i];
    }
    this->count = ch.count;
    this->view_count = ch.view_count;
}

template<class Key, class Data>
bool OpenHash<Key, Data>::insert(Key key, Data data) {
    for (int i = 0; i < this->size - 1; ++i) {
        this->view_count++;
        int hashKey = squadZond(this->convert(key), i);
        if (array[hashKey].status == BUSY && array[hashKey].key == key) break;
        if (array[hashKey].status == BUSY) continue;
        array[hashKey].key = key;
        array[hashKey].data = data;
        array[hashKey].status = BUSY;
        this->count++;
        return true;
    }
    return false;
}

template<class Key, class Data>
bool OpenHash<Key, Data>::remove(Key key) {
    if (this->isEmpty()) return false;
    for (int i = 0; i < this->size - 1; ++i) {
        this->view_count++;
        int hashKey = squadZond(this->convert(key), i);
        if (array[hashKey].status == FREE) break;
        if (array[hashKey].key == key && array[hashKey].status == BUSY) {
            array[hashKey].status = DELETED;
            this->count--;
            return true;
        }
    }
    return false;
}

template<class Key, class Data>
Data OpenHash<Key, Data>::search(Key key) {
    if (this->isEmpty()) throw runtime_error("EXCEPTION");
    for (int i = 0; i < this->size - 1; ++i) {
        this->view_count++;
        int hashKey = squadZond(this->convert(key), i);
        if (array[hashKey].status == FREE) break;
        if (array[hashKey].key == key && array[hashKey].status == BUSY) {
            return array[hashKey].data;
        }
    }
    throw runtime_error("EXCEPTION");
}

template<class Key, class Data>
void OpenHash<Key, Data>::printHash() {
    if (this->isEmpty()) return;
    cout << "Table:\n";
    for (int i = 0; i < this->size; ++i) {
        if (array[i].status == BUSY) {
            cout << i << ") " << array[i].key << "(" << array[i].data << ") - BUSY" << endl;
        } else if (array[i].status == DELETED) {
            cout << i << ") " << array[i].key << "(" << array[i].data << ") - DELETED" << endl;
        } else if (array[i].status == FREE) {
            cout << i << ") " << array[i].key << "(" << array[i].data << ") - FREE" << endl;
        }
    }
}

template<class Key, class Data>
typename HashTable<Key, Data>::Iterator *OpenHash<Key, Data>::begin() {
    HashTable<>::Iterator *iterator = new OpenHash<>::Iterator(this);
    iterator->toBegin();
    return iterator;
}

template<class Key, class Data>
typename HashTable<Key, Data>::Iterator *OpenHash<Key, Data>::end() {
    HashTable<>::Iterator *iterator = new OpenHash<>::Iterator(this);
    iterator->toEnd();
    return iterator;
}


template<class Key, class Data>
OpenHash<Key, Data>::Cell::Cell() {
    key = 0;
    data = 0;
    status = FREE;
}


#endif //ADS_LABA4_OPENHASH_H
