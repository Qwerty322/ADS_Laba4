#include <iostream>
#include "HashTable.h"
#include "ChainHash.h"
#include "OpenHash.h"
#include <string>

using namespace std;

typedef int TYPE;

int cinInt() {
    while (1) {
        cout << "Enter a key in interval [100000000; 300000000]: ";
        int x;
        cin >> x;
        if (x >= 100000000 and x <= 300000000) return x;
        cout << "Incorrect value!\n";
    }
}


int main() {
    srand(time(0));
    HashTable<> *hashTable = new OpenHash<>(20);
    HashTable<> *hashTable1 = new ChainHash<>(20);
//    hashTable.selectOpenMode(20);
    for (int i = 0; i < 5; ++i) {
        hashTable->insert(rand() % 200000000 + 100000000, i);
        hashTable1->insert(rand() % 200000000 + 100000000, i);
    }
//    hashTable.insert(123412455,31);
    hashTable->printHash();
    cout << endl << endl;
    hashTable1->printHash();
    HashTable<TYPE, TYPE>::Iterator *iterator = hashTable->begin();
    HashTable<TYPE, TYPE>::Iterator *iterator1 = hashTable1->end();
    cout << **iterator << endl;
    cout << **iterator1 << endl;
    ++*iterator1;
    cout << **iterator1 << endl;
//    cout << endl;
//    cout << hashTable.search(123412455) << endl;
//    hashTable.remove(123412455);
//    hashTable.printHash();



    return 0;
}
