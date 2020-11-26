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
    bool isChain;


    int convert(Key key);

    int hash(int key);

//    class Chain {
//    private:
//        class Node {
//        public:
//            Key key;
//            Data data;
//            Node *next;
//
//            Node(Key key1, Data data1, Node *node = nullptr);
//        };
//
//        Node *head;
//        int size;
//        int view_count;
//
//    public:
//        Chain();
//
//        Chain(Chain &chain);
//
//        ~Chain();
//
//        int getSize();
//
//        int getViewCount();
//
//        bool add(Key key, Data data);
//
//        bool del(Key key);
//
//        Data get(Key key);
//
//        void show();
//
//    };

//    class Cell {
//    public:
//        Key key;
//        Data data;
//        Status status;
//
//        Cell();
//    };

//    Chain **arr;
//
//    Cell *array;

//    int lowerPow2(int x);
//
//    int upperPow2(int x);
//
//    int squadZond(int key, int i);

public:
    class Iterator {
    protected:
        int index;
    public:
        virtual void checkException() = 0;

        virtual void toBegin() = 0;

        virtual void toEnd() = 0;

        virtual Data &operator*() = 0;

        virtual void operator++() = 0;

        virtual void operator++(int) = 0;

//        virtual bool operator==(HashTable<Key, Data>::Iterator *it) = 0;

    };

    HashTable();

    virtual ~HashTable() = default;

//    void selectChainMode(int _size);
//
//    void selectOpenMode(int _size);
//
    bool showMode();

    int getCount();

    int getSize();

    int getViewCount();

    bool isEmpty();

    virtual bool insert(Key key, Data data) = 0;

    virtual bool remove(Key key) = 0;

    virtual Data search(Key key) = 0;

    virtual void clear() = 0;

    virtual void printHash() = 0;

    virtual HashTable::Iterator* begin() = 0;

    virtual HashTable::Iterator* end() = 0;
};

//template<class Key, class Data>
//HashTable<Key, Data>::Cell::Cell() {
//    key = 0;
//    data = 0;
//    status = FREE;
//}
//
//template<class Key, class Data>
//HashTable<Key, Data>::Chain::Chain() {
//    head = nullptr;
//    size = 0;
//    view_count = 0;
//}
//
//template<class Key, class Data>
//HashTable<Key, Data>::Chain::Chain(HashTable::Chain &chain) {
//    if (chain.head) {
//        Node *tmp = chain.head;
//        head = new Node(tmp->key, tmp->data);
//        Node *p = head;
//        tmp = tmp->next;
//        while (tmp) {
//            Node *newNode = new Node(tmp->key, tmp->data);
//            p->next = newNode;
//            tmp = tmp->next;
//            p = p->next;
//        }
//        size = chain.size;
//        view_count = chain.view_count;
//    }
//}
//
//template<class Key, class Data>
//HashTable<Key, Data>::Chain::~Chain() {
//    Node *p = head;
//    while (p) {
//        Node *prev = p;
//        p = p->next;
//        delete prev;
//    }
//    size = 0;
//    view_count = 0;
//}
//
//template<class Key, class Data>
//int HashTable<Key, Data>::Chain::getSize() {
//    return size;
//}
//
//template<class Key, class Data>
//int HashTable<Key, Data>::Chain::getViewCount() {
//    int tmp = view_count;
//    view_count = 0;
//    return tmp;
//}
//
//template<class Key, class Data>
//bool HashTable<Key, Data>::Chain::add(Key key, Data data) {
//    if (!head) {
//        head = new Node(key, data);
//        size++;
//        view_count++;
//        return true;
//    }
//    Node *tmp = head;
//    while (tmp) {
//        view_count++;
//        if (tmp->data == data) return false;
//        if (!tmp->next) break;
//        tmp = tmp->next;
//    }
//    Node *node = new Node(key, data);
//    tmp->next = node;
//    size++;
//    return true;
//}
//
//template<class Key, class Data>
//bool HashTable<Key, Data>::Chain::del(Key key) {
//    if (!head) return false;
//    Node *tmp = head;
//    Node *prev;
//    while (tmp) {
//        view_count++;
//        if (tmp->key == key)
//            break;
//        prev = tmp;
//        tmp = tmp->next;
//    }
//    if (!tmp) return false;
//    if (tmp == head)
//        head = head->next;
//    else
//        prev->next = tmp->next;
//    delete tmp;
//    size--;
//    return true;
//}
//
//template<class Key, class Data>
//Data HashTable<Key, Data>::Chain::get(Key key) {
//    if (!head) throw runtime_error("EXCEPTION");
//    Node *tmp = head;
//    while (tmp) {
//        view_count++;
//        if (tmp->key == key)
//            break;
//        tmp = tmp->next;
//    }
//    if (!tmp) throw runtime_error("EXCEPTION");
//    return tmp->data;
//}
//
//template<class Key, class Data>
//void HashTable<Key, Data>::Chain::show() {
//    if (!head) return;
//    Node *tmp = head;
//    while (tmp) {
//        cout << tmp->key << "(" << tmp->data << ") ";
//        tmp = tmp->next;
//    }
//    cout << endl;
//}
//
//template<class Key, class Data>
//HashTable<Key, Data>::Chain::Node::Node(Key key1, Data data1, HashTable::Chain::Node *node) {
//    key = key1;
//    data = data1;
//    next = node;
//}

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

//template<class Key, class Data>
//void HashTable<Key, Data>::selectChainMode(int _size) {
//    if (isChain == 1) {
//        cout << "Chain form already used!\n";
//        return;
//    }
//    if (!isChain) {
//        clear();
//    }
//    isChain = 1;
//    size = lowerPow2(_size);
//    arr = new Chain *[size];
//    for (int i = 0; i < size; ++i) {
//        arr[i] = nullptr;
//    }
//    count = 0;
//    view_count = 0;
//    cout << "Form changed! Select form is chain.\n";
//}
//
//template<class Key, class Data>
//void HashTable<Key, Data>::selectOpenMode(int _size) {
//    if (!isChain) {
//        cout << "Open form already used!\n";
//        return;
//    }
//    if (isChain == 1) {
//        clear();
//    }
//    isChain = 0;
//    size = upperPow2(_size);
//    array = new Cell[size];
//    for (int i = 0; i < size; ++i) {
//        array[i].status = FREE;
//    }
//    count = 0;
//    view_count = 0;
//    cout << "Form changed! Select form is open.\n";
//}
//
//template<class Key, class Data>
//int HashTable<Key, Data>::lowerPow2(int x) {
//    if (x == 0) return 1;
//    int res = 1;
//    while (x > 0) {
//        res <<= 1;
//        x >>= 1;
//    }
//    return res >>= 1;
//}
//
//template<class Key, class Data>
//int HashTable<Key, Data>::upperPow2(int x) {
//    x--;
//    for (int p = 1; p < 32; p <<= 1) x |= (x >> p);
//    return ++x;
//}
//
//template<class Key, class Data>
//void HashTable<Key, Data>::clear() {
//    if (isEmpty()) return;
//    if (isChain == 1) {
//        for (int i = 0; i < size; ++i) {
//            delete arr[i];
//        }
//        delete arr;
//        size = 0;
//        count = 0;
//    } else if (!isChain) {
//        for (int i = 0; i < size; i++) {
//            array[i].status = FREE;
//        }
//        count = 0;
//    }
//
//}
//
//template<class Key, class Data>
//bool HashTable<Key, Data>::insert(Key key, Data data) {
//    if (isChain == 1) {
//        int hashKey = hash(convert(key));
//        if (arr[hashKey] == nullptr) {
//            arr[hashKey] = new Chain();
//        }
//        bool flag = arr[hashKey]->add(key, data);
//        view_count = arr[hashKey]->getViewCount();
//        if (!flag) return flag;
//        count++;
//        return flag;
//    } else if (!isChain) {
//        for (int i = 0; i < size - 1; ++i) {
//            view_count++;
//            int hashKey = squadZond(convert(key), i);
//            if (array[hashKey].status == BUSY) break;
//            array[hashKey].key = key;
//            array[hashKey].data = data;
//            array[hashKey].status = BUSY;
//            count++;
//            return true;
//        }
//        return false;
//    } else if (isChain == -1) {
//        cout << "At first choose a form!\n";
//    }
//}
//
//template<class Key, class Data>
//bool HashTable<Key, Data>::remove(Key key) {
//    if (isChain == 1) {
//        if (isEmpty()) return false;
//        int hashKey = hash(convert(key));
//        if (arr[hashKey] == nullptr) return false;
//        bool flag = arr[hashKey]->del(key);
//        view_count = arr[hashKey]->getViewCount();
//        if (!flag) return flag;
//        if (!arr[hashKey]->getSize()) {
//            delete arr[hashKey];
//            arr[hashKey] = nullptr;
//        }
//        count--;
//        return flag;
//    } else if (!isChain) {
//        if (isEmpty()) return false;
//        for (int i = 0; i < size - 1; ++i) {
//            view_count++;
//            int hashKey = squadZond(convert(key), i);
//            if (array[hashKey].key == key) {
//                array[hashKey].status = DELECTED;
//                count--;
//                return true;
//            }
//        }
//        return false;
//    } else if (isChain == -1) {
//        cout << "At first choose a form!\n";
//    }
//}
//
//template<class Key, class Data>
//Data HashTable<Key, Data>::search(Key key) {
//    if (isChain == 1) {
//        if (isEmpty()) throw runtime_error("EXCEPTION");
//        int hashKey = hash(convert(key));
//        if (arr[hashKey] == nullptr) throw runtime_error("EXCEPTION");
//        try {
//            return arr[hashKey]->get(key);
//        } catch (runtime_error e) {
//            throw e;
//        }
//    } else if (!isChain) {
//        if (isEmpty()) throw runtime_error("EXCEPTION");
//        for (int i = 0; i < size - 1; ++i) {
//            view_count++;
//            int hashKey = squadZond(convert(key), i);
//            if (array[hashKey].key == key) {
//                return array[hashKey].data;
//            }
//        }
//        throw runtime_error("EXCEPTION");
//    } else if (isChain == -1) {
//        throw runtime_error("At first choose a form!\n");
//    }
//}
//
//template<class Key, class Data>
//void HashTable<Key, Data>::printHash() {
//    if (isChain == 1) {
//        if (isEmpty()) return;
//        for (int i = 0; i < size; ++i) {
//            if (arr[i]) {
//                cout << i << ") ";
//                arr[i]->show();
//            }
//        }
//    } else if (!isChain) {
//        if (isEmpty()) return;
//        for (int i = 0; i < size; ++i) {
//            if (array[i].status == BUSY) {
//                cout << i << ") " << array[i].key << "(" << array[i].data << ")\n";
//            }
//        }
//    } else if (isChain == -1) {
//        cout << "At first choose a form!\n";
//    }
//}
//
//template<class Key, class Data>
//int HashTable<Key, Data>::squadZond(int key, int i) {
//    float c1 = 0.5;
//    float c2 = 0.5;
//    return (int)(hash(key) + c1 * i + c2 * i * i) % size;
//}




#endif //ADS_LABA4_HASHTABLE_H
