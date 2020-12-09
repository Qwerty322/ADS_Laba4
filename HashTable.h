#ifndef ADS_LABA4_HASHTABLE_H
#define ADS_LABA4_HASHTABLE_H

#include <iostream>
#include <math.h>

using namespace std;


template<class Key = double , class Data = int>
class HashTable {
protected:
    int size;  // размер таблицы
    int count;  // кол-во элементов в таблице
    int view_count;
    bool isChain;  // форма представления


    Key convert(Key key);  // преобразование ключа
    int hash(Key key);  // хеш-функция

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
Key HashTable<Key, Data>::convert(Key key) {
    long int newKey = (int) (key * 1000);
    newKey *= newKey;
    int index = 0;
    for (long int i = abs(newKey); i > 0; i /= 10, index++);
    if (index % 2 == 0 && index > 6) {
        newKey %= (int) pow(10, 6 + (index - 6) / 2);
        newKey /= (int) pow(10, (index - 6) / 2);
    }
    else if (index % 2 == 1 && index > 6) {
        newKey %= (int) pow(10, 6 + (index - 6 + 1) / 2);
        newKey /= (int) pow(10, (index - 6 + 1) / 2);
    }
    return newKey;
}

template<class Key, class Data>
int HashTable<Key, Data>::hash(Key key) {
    double A = (sqrt(5) - 1) / 2;
    return (int)(((A * key) - (int)(A * key)) * size);
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
        cout << "Хеш таблица с цепочками коллизий!\n";
    } else cout << "Хеш таблица с открытой адресацией!\n";
    return isChain;
}


#endif //ADS_LABA4_HASHTABLE_H
