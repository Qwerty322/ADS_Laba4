#include <iostream>
#include "HashTable.h"
#include "ChainHash.h"
#include "OpenHash.h"
#include <string>
#include <math.h>
#include <map>

using namespace std;

typedef int TYPE;
map<char, string> dict;


string randString() {
    string str;
    for (int i = 0; i < 5; ++i) {
        str += (char) (rand() % 26 + 97);
    }
    return str;
}

string cinKey() {
    while (1) {
        cout << "Enter a key (string, only lowercase a-z, lenght <= 6): ";
        string str;
        cin >> str;
        bool flag = true;
        if (str.length() > 6) {
            cout << "Lenght more then 6! Please repeat!\n";
            continue;
        }
        for (char i : str) {
            if (i >= 97 && i <= 122) {
                continue;
            } else {
                flag = false;
            }
        }
        if (flag) return str;
        cout << "Incorrect input! Please repeat!\n";
    }
}

void initMap() {
    dict.insert(pair<char, string>('a', "00001"));
    dict.insert(pair<char, string>('b', "00010"));
    dict.insert(pair<char, string>('c', "00011"));
    dict.insert(pair<char, string>('d', "00100"));
    dict.insert(pair<char, string>('e', "00101"));
    dict.insert(pair<char, string>('f', "00110"));
    dict.insert(pair<char, string>('g', "00111"));
    dict.insert(pair<char, string>('h', "01000"));
    dict.insert(pair<char, string>('i', "01001"));
    dict.insert(pair<char, string>('j', "01010"));
    dict.insert(pair<char, string>('k', "01011"));
    dict.insert(pair<char, string>('l', "01100"));
    dict.insert(pair<char, string>('m', "01101"));
    dict.insert(pair<char, string>('n', "01110"));
    dict.insert(pair<char, string>('o', "01111"));
    dict.insert(pair<char, string>('p', "10000"));
    dict.insert(pair<char, string>('q', "10001"));
    dict.insert(pair<char, string>('r', "10010"));
    dict.insert(pair<char, string>('s', "10011"));
    dict.insert(pair<char, string>('t', "10100"));
    dict.insert(pair<char, string>('u', "10101"));
    dict.insert(pair<char, string>('v', "10110"));
    dict.insert(pair<char, string>('w', "10111"));
    dict.insert(pair<char, string>('x', "11000"));
    dict.insert(pair<char, string>('y', "11001"));
    dict.insert(pair<char, string>('z', "11010"));
}

long long int Hash(string key, int size) {
    string str1;
    for (char &i : key) {
        str1 += dict[i];
    }
    long long int newKey = 0;
    for (double p = 0, i = str1.length() - 1; i >= 0; --i, p++) {
        if (str1[i] == '1') {
            newKey += (int) pow(2, p);
        }
    }
    return newKey % size;
}

void TestHashFunc(int size) {
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
        arr[i] = 0;
    for (int i = 0; i < 25 * size; i++) {
        string x = randString();
        int k = Hash(x, size);
        arr[k]++;
    }
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (arr[i] - 25) * (arr[i] - 25);
    }
    sum /= 25.0;

    cout << "m-sqrt(m) " << (double) (size - sqrt((double) size)) << endl;
    cout << sum << " " << rand() % (int) ((size + sqrt((double) size)) - (size - sqrt((double) size))) +
                          (double) (size - sqrt((double) size)) << endl;
    cout << "m+sqrt(m) " << (double) (size + sqrt((double) size)) << endl;
    delete[] arr;
}

void TestHashTable(double alpha, bool isChain, int size) {
    double ins, fnd, del;
    ins = fnd = del = 0;
    HashTable<string, int> *ht;
    if (isChain)
        ht = new ChainHash<>(size);
    else
        ht = new OpenHash<>(size);
    int count = (int) (alpha * ht->getSize());
    string *arr = new string[count];
    for (int i = 0; i < count; i++) {
        string key = randString();
        ht->insert(key, i);
        arr[i] = key;
    }
    ht->getViewCount();
    cout << "Size before " << ht->getCount() << endl;
    for (int i = 0; i < count / 2; i++) {
        if (i % 10 != 0) {
            int index = rand() % count;
            ht->remove(arr[index]);
            del += ht->getViewCount();
            string x = randString();
            arr[index] = x;
            ht->insert(x, 1);
            ins += ht->getViewCount();
            index = rand() % count;
            try {
                ht->search(arr[index]);
                fnd += ht->getViewCount();
            }
            catch (runtime_error) { fnd += ht->getViewCount(); }
        } else {
            string x = randString();
            ht->remove(x);
            del += ht->getViewCount();
            int index = rand() % count;
            ht->insert(arr[index], 1);
            ins += ht->getViewCount();
            x = randString();
            try {
                ht->search(x);
                fnd += ht->getViewCount();
            }
            catch (runtime_error) { fnd += ht->getViewCount(); }
        }
    }
    delete[] arr;
    cout << "Size after " << ht->getCount() << endl;
    if (isChain)
        cout << "Insert T " << 1 + alpha << endl;
    else
        cout << "Insert T " << 0.1 * (-log(1 - alpha) / alpha) + 0.9 * (1 / (1 - alpha)) << endl;
    cout << "Insert " << ins / (count / 2) << endl;
    if (isChain)
        cout << "Delete T " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    else
        cout << "Delete T " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "Delete " << del / (count / 2) << endl;
    if (isChain)
        cout << "Search T " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    else
        cout << "Search T " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "Search " << fnd / (count / 2) << endl;
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
                "15. Test menu                  |\n"
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


#define Main

#ifdef Main

int main() {
    srand(time(0));
    initMap();
    HashTable<string, int> *hashTable = nullptr;
    HashTable<string, int>::Iterator *iterator = nullptr;
    HashTable<string, int>::Iterator *iterator1 = nullptr;
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
                    string key = cinKey();
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
                    string key = cinKey();
                    int data;
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
                    string key = cinKey();
                    cout << boolalpha << hashTable->remove(key) << endl;
                } else {
                    cout << "At first choose a form!\n";
                }
                break;
            }
            case 8: {
                clearConsole();
                cout << "Enter a size of table: ";
                cin >> size;
                delete hashTable;
                hashTable = new ChainHash<>(size);
                break;
            }
            case 9: {
                clearConsole();
                cout << "Enter a size of table: ";
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
                                clearConsole();
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
            case 15: {
                clearConsole();
                bool test = true;
                int in;
                while (test) {
                    cout << "____________MENU_______________\n"
                            "1. Test hash function          |\n"
                            "2. Test hash table             |\n"
                            "0.  Exit                       |\n"
                            "-------------------------------\n"
                            "Input: ";
                    cin >> in;
                    switch (in) {
                        case 1: {
                            clearConsole();
                            cout << "Enter size: ";
                            cin >> size;
                            TestHashFunc(size);
                            break;
                        }
                        case 2: {
                            clearConsole();
                            cout << "Enter alpha: ";
                            double alpha;
                            cin >> alpha;
                            cout << "Choose form: chain(1) or open(0) : ";
                            bool form;
                            cin >> form;
                            cout << "Enter size: ";
                            cin >> size;
                            TestHashTable(alpha, form, size);
                            break;
                        }
                        case 0: {
                            clearConsole();
                            test = false;
                            break;
                        }
                        default: {
                            clearConsole();
                            cout << "Incorrect input! Please repeat.\n";
                            break;
                        }

                    }
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
                    hashTable->insert(randString(), i);
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
