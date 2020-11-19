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
    ChainHash<TYPE, TYPE> CH(10);
    for (int i = 0; i < 5; ++i) {
        CH.insert(rand() % 200000000 + 100000000, i);
    }
    int x = rand() % 200000000 + 100000000;
    CH.insert(x, 111);
    CH.printHash();
    cout << endl;
    cout << CH.search(x) << endl;
    CH.remove(x);
    CH.printHash();
    return 0;
}
