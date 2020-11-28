#include <iostream>
#include "HashTable.h"
#include "ChainHash.h"
#include "OpenHash.h"
#include <string>
#include <math.h>

using namespace std;

typedef int TYPE;

int cinKey() {
    while (1) {
        cout << "Enter a key in interval [100000000; 300000000]: ";
        int x;
        cin >> x;
        if (x >= 100000000 and x <= 300000000) return x;
        cout << "Incorrect value! Repeat please.\n";
    }
}

int Hash(int key, int size) {
    int pair1 = key / 1000000;
    int pair2 = key / 1000 % 1000;
    int pair3 = key % 1000;
    return (pair1 ^ 1 + pair2 ^ 2 + pair3 ^ 3) % 1000 % size;
}

void TestHashFunc(int size) {
    srand(time(0));
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
        arr[i] = 0;
    for (int i = 0; i < 25 * size; i++) {
        int x = rand() % 200000000 + 100000000;
        int k = Hash(x, size);
//        cout << x << "  " << k << endl;
        arr[k]++;
    }
    double sum = 0;
    //СКО
    for (int i = 0; i < size; i++) {
        sum += (arr[i] - 25) * (arr[i] - 25);
    }
    sum /= 25.0;

    cout << "m-sqrt(m) " << (double) (size - sqrt((double) size)) << endl;
    cout << sum << endl;
    cout << "m+sqrt(m) " << (double) (size + sqrt((double) size)) << endl;
    delete[] arr;
}

void TestHashTable(double alpha, bool isChain, int size) {
    srand(time(0));
    double ins, fnd, del;
    ins = fnd = del = 0;
    HashTable<TYPE, TYPE> *ht;
    if (isChain)
        ht = new ChainHash<>(size);
    else
        ht = new OpenHash<>(size);
    int count = (int) (alpha * ht->getSize());
    int *arr = new int[count];
    for (int i = 0; i < count; i++) {
        int key = rand() % 200000000 + 100000000;
        ht->insert(key, i);
        arr[i] = key;
    }
    ht->getViewCount();
    cout << "Размер до " << ht->getCount() << endl;
    for (int i = 0; i < count / 2; i++) {
        if (i % 10 != 0) {
            int index = rand() % count;
            ht->remove(arr[index]);
            del += ht->getViewCount();
            int x = rand() % 200000000 + 100000000;
            ht->insert(x, 1);
            ins += ht->getViewCount();
            index = rand() % count;
            try {
                ht->search(arr[index]);
                fnd += ht->getViewCount();
            }
            catch (runtime_error) { fnd += ht->getViewCount(); }
        } else {
            int x = rand() % 200000000 + 100000000;
            ht->remove(x);
            del += ht->getViewCount();
            int index = rand() % count;
            ht->insert(arr[index], 1);
            ins += ht->getViewCount();
            x = rand() % 200000000 + 100000000;
            try {
                ht->search(x);
                fnd += ht->getViewCount();
            }
            catch (runtime_error) { fnd += ht->getViewCount(); }
        }
    }
    delete[] arr;
    cout << "Размер после " << ht->getCount() << endl;
    if (isChain)
        cout << "Вставка T " << 1 + alpha << endl;
    else
        cout << "Вставка T " << 0.1 * (-log(1 - alpha) / alpha) + 0.9 * (1 / (1 - alpha)) << endl;
    cout << "Вставка " << ins / (count / 2) << endl;
    if (isChain)
        cout << "Удаление T " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    else
        cout << "Удаление T " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "Удаление " << del / (count / 2) << endl;
    if (isChain)
        cout << "Поиск T " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    else
        cout << "Поиск T " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "Поиск " << fnd / (count / 2) << endl;
    delete ht;
}


void clearConsole() {
    for (int i = 0; i < 20; ++i) {
        cout << endl;
    }
}

void showMenu(bool main = true) {
    if (main) {
        cout << "____________MENU_______________\n"
                "1. Get size a table            |\n"
                "2. Get count elems in table    |\n"
                "3. Is empty table?             |\n"
                "4. Clear table                 |\n"
                "5. Search by key               |\n"
                "6. Push by key                 |\n"
                "7. Remove by key               |\n"
                "8. Set chain form              |\n"
                "9. Set open form               |\n"
                "10. Which is form?             |\n"
                "11. Set begin                  |\n"
                "12. Set end                    |\n"
                "13. Print table                |\n"
                "14. Iterator menu              |\n"
                "0.  Exit                       |\n"
                "-------------------------------\n"
                "Input: ";
    } else {
        cout << "____________MENU_______________\n"
                "1. Init a second iterator      |\n"
                "2. Write access (*)            |\n"
                "3. Read access (*)             |\n"
                "4. Go to next (++)             |\n"
                "5. Check equality              |\n"
                "0.  Exit                       |\n"
                "-------------------------------\n"
                "Input: ";
    }
}

#define Test
//#define Main

#ifdef Test

int main() {
    srand(time(0));
    TestHashFunc(1000);
//    TestHashTable(0.75, false, 1000);
    return 0;
}

#endif

#ifdef Main
int main() {
    srand(time(0));
    HashTable<TYPE, TYPE> *hashTable = nullptr;
    HashTable<TYPE, TYPE>::Iterator *iterator = nullptr;
    HashTable<TYPE, TYPE>::Iterator *iterator1 = nullptr;
    cout << "Choose a form: chain(1) or open(2)!\n Input: ";
    int ans, size;
    cin >> ans;
    if (ans == 1) {
        cout << "Enter a size of table: ";
        cin >> size;
        hashTable = new ChainHash<>(size);
    } else if (ans == 2) {
        cout << "Enter a size of table: ";
        cin >> size;
        hashTable = new OpenHash<>(size);
    } else {
        cout << "Form doesn't set!\n";
    }
    bool exit = true;
    while (exit) {
        showMenu();
        int x;
        cin >> x;
        switch (x) {
            case 1: {
                clearConsole();
                if (hashTable) {
                    cout << hashTable->getSize() << endl;
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 2: {
                clearConsole();
                if (hashTable) {
                    cout << hashTable->getCount() << endl;
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 3: {
                clearConsole();
                if (hashTable) {
                    cout << boolalpha << hashTable->isEmpty() << endl;
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 4: {
                clearConsole();
                if (hashTable) {
                    hashTable->clear();
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 5: {
                clearConsole();
                if (hashTable) {
                    TYPE key = cinKey();
                    try {
                        cout << hashTable->search(key) << endl;
                    } catch (runtime_error e) {
                        cout << e.what() << endl;
                    }
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 6: {
                clearConsole();
                if (hashTable) {
                    TYPE data, key = cinKey();
                    cout << "Enter a data:";
                    cin >> data;
                    cout << boolalpha << hashTable->insert(key, data) << endl;
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 7: {
                clearConsole();
                if (hashTable) {
                    TYPE key = cinKey();
                    cout << boolalpha << hashTable->remove(key) << endl;
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 8: {
                clearConsole();
                cout << "Enter a size of table: ";
                int size;
                cin >> size;
                delete hashTable;
                hashTable = new ChainHash<>(size);
                break;
            }
            case 9: {
                clearConsole();
                cout << "Enter a size of table: ";
                int size;
                cin >> size;
                delete hashTable;
                hashTable = new OpenHash<>(size);
                break;
            }
            case 10: {
                clearConsole();
                if (hashTable) {
                    hashTable->showMode();
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 11: {
                clearConsole();
                if (hashTable) {
                    try {
                        iterator = hashTable->begin();
                    } catch (runtime_error error) {
                        cout << error.what() << endl;
                    }
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 12: {
                clearConsole();
                if (hashTable) {
                    try {
                        iterator = hashTable->end();
                    } catch (runtime_error error) {
                        cout << error.what() << endl;
                    }
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 13: {
                clearConsole();
                if (hashTable) {
                    hashTable->printHash();
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 14: {
                clearConsole();
                if (iterator) {
                    bool exit1 = true;
                    while (exit1) {
                        showMenu(false);
                        int xx;
                        cin >> xx;
                        switch (xx) {
                            case 1: {
                                clearConsole();
                                try {
                                    cout << "Enter a setting: begin(1) or end(2): ";
                                    int value;
                                    cin >> value;
                                    if (value == 1) {
                                        iterator1 = hashTable->begin();
                                    } else if (value == 2) {
                                        iterator1 = hashTable->end();
                                    } else cout << "Incorrect input! Repeat please.\n";
                                } catch (runtime_error error) {
                                    cout << error.what() << endl;
                                }
                                break;
                            }
                            case 2: {
                                clearConsole();
                                try {
                                    if (iterator1) {
                                        cout << "Enter a iterator: first(1) or second(2): ";
                                        int it;
                                        cin >> it;
                                        cout << "Enter a new value: ";
                                        TYPE value;
                                        cin >> value;
                                        if (it == 1) {
                                            **iterator = value;
                                        } else if (it == 2) {
                                            **iterator1 = value;
                                        } else cout << "Incorrect input! Repeat please.\n";
                                    } else {
                                        cout << "Enter a new value: ";
                                        TYPE value;
                                        cin >> value;
                                        **iterator = value;
                                    }
                                } catch (runtime_error error) {
                                    cout << error.what() << endl;
                                }
                                break;
                            }
                            case 3: {
                                clearConsole();
                                try {
                                    if (iterator1) {
                                        cout << "Enter a iterator: first(1) or second(2): ";
                                        int it;
                                        cin >> it;
                                        if (it == 1) {
                                            cout << **iterator << endl;
                                        } else if (it == 2) {
                                            cout << **iterator1 << endl;
                                        } else cout << "Incorrect input! Repeat please.\n";
                                    } else {
                                        cout << **iterator << endl;
                                    }
                                } catch (runtime_error error) {
                                    cout << error.what() << endl;
                                }
                                break;
                            }
                            case 4: {
                                clearConsole();
                                try {
                                    if (iterator1) {
                                        cout << "Enter a iterator: first(1) or second(2): ";
                                        int it;
                                        cin >> it;
                                        if (it == 1) {
                                            ++*iterator;
                                        } else if (it == 2) {
                                            ++*iterator1;
                                        } else cout << "Incorrect input! Repeat please.\n";
                                    } else {
                                        ++*iterator;
                                    }
                                } catch (runtime_error error) {
                                    cout << error.what() << endl;
                                }
                                break;
                            }
                            case 5: {
                                clearConsole();
                                try {
                                    cout << boolalpha << (*iterator == iterator1) << endl;
                                } catch (runtime_error error) {
                                    cout << error.what() << endl;
                                }
                                break;
                            }
                            case 0: {
                                exit1 = false;
                                break;
                            }
                            default: {
                                cout << "Incorrect value!\n";
                                break;
                            }
                        }
                    }
                } else {
                    cout << "At first set a iterator!\n";
                }
                break;
            }
            case 0: {
                exit = false;
                break;
            }
            case 777: {
                clearConsole();
                for (int i = 0; i < 5; ++i) {
                    hashTable->insert(rand() % 200000000 + 100000000, i);
                }
                break;
            }
            default: {
                cout << "Incorrect value!\n";
                break;
            }

        }
    }
    return 0;
}
#endif
