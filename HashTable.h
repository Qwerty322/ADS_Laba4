#ifndef ADS_LABA4_HASHTABLE_H
#define ADS_LABA4_HASHTABLE_H

#include <iostream>

using namespace std;


template<class Key = int, class Data = int>
class HashTable {
protected:
    int size;  // размер таблицы
    int count;  // кол-во элементов в таблице
    int view_count;
    bool isChain;  // форма представления


    int convert(Key key);  // преобразование ключа

    int hash(int key);  // хеш-функция

public:
    class Iterator {
    protected:
        int index;
    public:
        virtual void checkException() = 0;

        virtual void toBegin() = 0;

        virtual void toEnd() = 0;

        virtual Data &operator*() = 0;  // доступ к чтению/записи

        virtual void operator++() = 0; // переход к следующему элементу

        virtual void operator++(int) = 0; // переход к следующему элементу

        virtual bool operator==(HashTable<Key, Data>::Iterator *it) = 0;  // сравнение элементов

    };

    HashTable();  // конструктор

    virtual ~HashTable() = default;  // деструктор

    bool showMode(); // опрос формы представления

    int getCount(); // опрос кол-ва элементов в таблице

    int getSize();  // опрос размера таблицы

    int getViewCount();

    bool isEmpty();  // опрос на пустоту списка

    virtual bool insert(Key key, Data data) = 0;  // вставка элемента в таблицу

    virtual bool remove(Key key) = 0;  // удаление элемента из таблицы

    virtual Data search(Key key) = 0;  // поиск элемента в таблице

    virtual void clear() = 0;  // очистка таблицы

    virtual void printHash() = 0;  // вывод таблицы

    virtual HashTable::Iterator *begin() = 0;  // запрос итератора begin()

    virtual HashTable::Iterator *end() = 0; // запрос итератора end()
};


template<class Key, class Data>
HashTable<Key, Data>::HashTable() {
    size = 0;
    count = 0;
    view_count = 0;
}

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

template<class Key, class Data>
bool HashTable<Key, Data>::showMode() {
    if (isChain) {
        cout << "Form is chain!\n";
    } else cout << "Form is open!\n";
    return isChain;
}


#endif //ADS_LABA4_HASHTABLE_H
