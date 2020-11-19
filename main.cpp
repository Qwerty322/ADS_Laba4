#include <iostream>
#include "HashTable.h"
#include "ChainHash.h"
#include <string>

using namespace std;

typedef int TYPE;

int cinInt(){
    while (1) {
        cout << "Enter a key: ";
        int x;
        cin >> x;
        if (x >= 100000000 and x <= 300000000) return x;
        cout << "Incorrect value!\n";
    }
}





int main() {
    srand(time(0));
    HashTable<> hashTable;
    hashTable.selectOpenMode(20);
    for (int i = 0; i < 5; ++i) {
        hashTable.insert(rand() % 200000000 + 100000000, i);
    }
    hashTable.insert(123412455,31);
    hashTable.printHash();
    cout << endl;
    cout << hashTable.search(123412455) << endl;
//    hashTable.remove(123412455);
//    hashTable.printHash();

    return 0;
}
