#ifndef ADS_LABA4_HASHTABLE_H
#define ADS_LABA4_HASHTABLE_H

#include <iostream>
#include <map>
#include <math.h>

using namespace std;


template<class Key = string, class Data = int>
class HashTable {
protected:
    int size;  // размер таблицы
    int count;  // кол-во элементов в таблице
    int view_count;
    bool isChain;  // форма представления
    map<char, string> map;


    long long int convert(Key key);  // преобразование ключа

    int hash(int key);  // хеш-функция

    int hash1(int key);  // хеш-функция

    void initMap();

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
    initMap();
}

template<class Key, class Data>
long long int HashTable<Key, Data>::convert(Key key) {
    string str1;
    for (char &i : key) {
        str1 += map[i];
    }
    long long int newKey = 0;
    for (double p = 0, i = str1.length() - 1; i >= 0; --i, p++) {
        if (str1[i] == '1') {
            newKey += (int) pow(2, p);
        }
    }
    return newKey;
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

template<class Key, class Data>
void HashTable<Key, Data>::initMap() {
    map.insert(pair<char, string>('a', "00001"));
    map.insert(pair<char, string>('b', "00010"));
    map.insert(pair<char, string>('c', "00011"));
    map.insert(pair<char, string>('d', "00100"));
    map.insert(pair<char, string>('e', "00101"));
    map.insert(pair<char, string>('f', "00110"));
    map.insert(pair<char, string>('g', "00111"));
    map.insert(pair<char, string>('h', "01000"));
    map.insert(pair<char, string>('i', "01001"));
    map.insert(pair<char, string>('j', "01010"));
    map.insert(pair<char, string>('k', "01011"));
    map.insert(pair<char, string>('l', "01100"));
    map.insert(pair<char, string>('m', "01101"));
    map.insert(pair<char, string>('n', "01110"));
    map.insert(pair<char, string>('o', "01111"));
    map.insert(pair<char, string>('p', "10000"));
    map.insert(pair<char, string>('q', "10001"));
    map.insert(pair<char, string>('r', "10010"));
    map.insert(pair<char, string>('s', "10011"));
    map.insert(pair<char, string>('t', "10100"));
    map.insert(pair<char, string>('u', "10101"));
    map.insert(pair<char, string>('v', "10110"));
    map.insert(pair<char, string>('w', "10111"));
    map.insert(pair<char, string>('x', "11000"));
    map.insert(pair<char, string>('y', "11001"));
    map.insert(pair<char, string>('z', "11010"));
}

template<class Key, class Data>
int HashTable<Key, Data>::hash1(int key) {
    return 1 + (key % (size - 2));
}


#endif //ADS_LABA4_HASHTABLE_H
