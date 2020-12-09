#include <iostream>
#include "HashTable.h"
#include "ChainHash.h"
#include "OpenHash.h"
#include <string>
#include <math.h>

using namespace std;


double cinKey() {
    while (1) {
        cout << "Enter a key in interval [-10000.000; +10000.000]: ";
        double x;
        cin >> x;
        if (x >= -10000 and x <= 10000) return x;
        cout << "Incorrect value! Repeat please.\n";
    }
}

double Hash(double key, int size) {
    double A = (sqrt(5) - 1) / 2;
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
    return (int) (((A * newKey) - (int) (A * newKey)) * size);
}

void TestHashFunc(int size) {
    srand(time(0));
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
        arr[i] = 0;
    for (int i = 0; i < 25 * size; i++) {
        int x = rand() % 10000;
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
    srand(time(0));
    double ins, fnd, del;
    ins = fnd = del = 0;
    HashTable<double, int> *ht;
    if (isChain)
        ht = new ChainHash<>(size);
    else
        ht = new OpenHash<>(size);
    int count = (int) (alpha * ht->getSize());
    int *arr = new int[count];
    for (int i = 0; i < count; i++) {
        int key = rand() % 10000;
        ht->insert(key, i);
        arr[i] = key;
    }
    ht->getViewCount();
    cout << "размер до " << ht->getCount() << endl;
    for (int i = 0; i < count / 2; i++) {
        if (i % 10 != 0) {
            int index = rand() % count;
            ht->remove(arr[index]);
            del += ht->getViewCount();
            int x = rand() % 10000;
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
            int x = rand() % 10000;
            ht->remove(x);
            del += ht->getViewCount();
            int index = rand() % count;
            ht->insert(arr[index], 1);
            ins += ht->getViewCount();
            x = rand() % 10000;
            try {
                ht->search(x);
                fnd += ht->getViewCount();
            }
            catch (runtime_error) { fnd += ht->getViewCount(); }
        }
    }
    delete[] arr;
    cout << "размер после " << ht->getCount() << endl;
    if (isChain)
        cout << "вставка T " << 1 + alpha << endl;
    else
        cout << "вставка T " << 0.1 * (-log(1 - alpha) / alpha) + 0.9 * (1 / (1 - alpha)) << endl;
    cout << "вставка " << ins / (count / 2) << endl;
    if (isChain)
        cout << "удаление T " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    else
        cout << "удаление T " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "удаление " << del / (count / 2) << endl;
    if (isChain)
        cout << "поиск T " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    else
        cout << "поиск T " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "поиск " << fnd / (count / 2) << endl;
    delete ht;
}


void clearConsole() {
    for (int i = 0; i < 20; ++i) {
        cout << endl;
    }
}

void showMenu(bool main = true) {
    if (main) {
        cout << "меню\n"
                "1. показать размер таблицы\n"
                "2. показать кол-во элементов\n"
                "3. пустая ли таблица\n"
                "4. очистить таблицу\n"
                "5. искать по ключу\n"
                "6. вставить по ключу\n"
                "7. удалить по ключу\n"
                "8. установить цепочную форму\n"
                "9. установить открытую форму\n"
                "10. показать форму\n"
                "11. установить begin\n"
                "12. установить end\n"
                "13. вывести таблицу\n"
                "14. итератор меню\n"
                "15. тест меню\n"
                "0.  выход\n";
    } else {
        cout << "меню\n"
                "1. установить второй итератор\n"
                "2. запись\n"
                "3. чтение\n"
                "4. следующий\n"
                "5. равенство\n"
                "0.  выход\n";

    }
}

#define Main
#ifdef Main

int main() {
    srand(time(0));
    HashTable<double, int> *hashTable = nullptr;
    HashTable<double, int>::Iterator *iterator = nullptr;
    HashTable<double, int>::Iterator *iterator1 = nullptr;
    cout << "выберите форму цепочки(1) открытая(2)!\n";
    int ans, size;
    cin >> ans;
    if (ans == 1) {
        cout << "введите размер: ";
        cin >> size;
        hashTable = new ChainHash<>(size);
    } else if (ans == 2) {
        cout << "введите размер: ";
        cin >> size;
        hashTable = new OpenHash<>(size);
    } else {
        cout << "не установлено!\n";
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
                    cout << "выберите форму!\n";
                }
                break;
            }
            case 2: {
                clearConsole();
                if (hashTable) {
                    cout << hashTable->getCount() << endl;
                } else {
                    cout << "выберите форму!\n";
                }
                break;
            }
            case 3: {
                clearConsole();
                if (hashTable) {
                    cout << boolalpha << hashTable->isEmpty() << endl;
                } else {
                    cout << "выберите форму!\n";
                }
                break;
            }
            case 4: {
                clearConsole();
                if (hashTable) {
                    hashTable->clear();
                } else {
                    cout << "выберите форму!\n";
                }
                break;
            }
            case 5: {
                clearConsole();
                if (hashTable) {
                    double key = cinKey();
                    try {
                        cout << hashTable->search(key) << endl;
                    } catch (runtime_error e) {
                        cout << e.what() << endl;
                    }
                } else {
                    cout << "выберите форму!\n";
                }
                break;
            }
            case 6: {
                clearConsole();
                if (hashTable) {
                    double key = cinKey();
                    int data;
                    cout << "введите данные:";
                    cin >> data;
                    cout << boolalpha << hashTable->insert(key, data) << endl;
                } else {
                    cout << "выберите форму!\n";
                }
                break;
            }
            case 7: {
                clearConsole();
                if (hashTable) {
                    double key = cinKey();
                    cout << boolalpha << hashTable->remove(key) << endl;
                } else {
                    cout << "выберите форму!\n";
                }
                break;
            }
            case 8: {
                clearConsole();
                cout << "введите размер: ";
                int size;
                cin >> size;
                delete hashTable;
                hashTable = new ChainHash<>(size);
                break;
            }
            case 9: {
                clearConsole();
                cout << "введите размер: ";
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
                    cout << "выберите форму!\n";
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
                    cout << "выберите форму!\n";
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
                    cout << "выберите форму!\n";
                }
                break;
            }
            case 13: {
                clearConsole();
                if (hashTable) {
                    hashTable->printHash();
                } else {
                    cout << "выберите форму!\n";
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
                                    cout << "begin(1) или end(2): ";
                                    int value;
                                    cin >> value;
                                    if (value == 1) {
                                        iterator1 = hashTable->begin();
                                    } else if (value == 2) {
                                        iterator1 = hashTable->end();
                                    } else cout << "недопустимое значение.\n";
                                } catch (runtime_error error) {
                                    cout << error.what() << endl;
                                }
                                break;
                            }
                            case 2: {
                                clearConsole();
                                try {
                                    if (iterator1) {
                                        cout << "введите итератор первый(1) второй(2): ";
                                        int it;
                                        cin >> it;
                                        cout << "введите новое значение: ";
                                        int value;
                                        cin >> value;
                                        if (it == 1) {
                                            **iterator = value;
                                        } else if (it == 2) {
                                            **iterator1 = value;
                                        } else cout << "недопустимое значение!\n";
                                    } else {
                                        cout << "введите новое значение: ";
                                        int value;
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
                                        cout << "введите итератор первый(1) второй(2): ";
                                        int it;
                                        cin >> it;
                                        if (it == 1) {
                                            cout << **iterator << endl;
                                        } else if (it == 2) {
                                            cout << **iterator1 << endl;
                                        } else cout << "недопустимое значение!\n";
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
                                        cout << "введите итератор первый(1) второй(2): ";
                                        int it;
                                        cin >> it;
                                        if (it == 1) {
                                            ++*iterator;
                                        } else if (it == 2) {
                                            ++*iterator1;
                                        } else cout << "недопустимое значение!\n";
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
                                cout << "недопустимое значение!\n";
                                break;
                            }
                        }
                    }
                } else {
                    cout << "установите итератор!\n";
                }
                break;
            }
            case 15: {
                clearConsole();
                bool test = true;
                int in;
                while (test) {
                    cout << "меню\n"
                            "1. проверка хеш функции         |\n"
                            "2. проверка хеш таблицы        |\n"
                            "0.  выход                      |\n";
                    cin >> in;
                    switch (in) {
                        case 1: {
                            clearConsole();
                            cout << "введите размер: ";
                            int size;
                            cin >> size;
                            TestHashFunc(size);
                            break;
                        }
                        case 2: {
                            clearConsole();
                            cout << "введите коэффициент заполненности: ";
                            double alpha;
                            cin >> alpha;
                            cout << "введите форму: цепочки(1) или открытая(0): ";
                            bool form;
                            cin >> form;
                            cout << "введите размер: ";
                            int size;
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
                            cout << "недопустимое значение\n";
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
            default: {
                cout << "недопустимое значение\n";
                break;
            }
        }
    }
    return 0;
}

#endif
