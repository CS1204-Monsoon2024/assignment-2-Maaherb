#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int count;
    static const int EMPTY = -1;
    static const int DELETED = -2;

    int hash(int key) {
        return key % size;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    void resize() {
        int newSize = nextPrime(size * 2);
        std::vector<int> oldTable = table;
        table = std::vector<int>(newSize, EMPTY);
        size = newSize;
        count = 0;
        for (int key : oldTable) {
            if (key != EMPTY && key != DELETED) {
                insert(key);
            }
        }
    }

public:
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table = std::vector<int>(size, EMPTY);
        count = 0;
    }

    HashTable(const HashTable& other) = delete;
    HashTable& operator=(const HashTable& other) = delete;

    void insert(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != EMPTY && table[(index + i * i) % size] != DELETED) {
            if (table[(index + i * i) % size] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
            if (i >= size) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
        }
        table[(index + i * i) % size] = key;
        count++;
        if (static_cast<float>(count) / size > 0.8) {
            resize();
        }
    }

    void remove(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != EMPTY) {
            if (table[(index + i * i) % size] == key) {
                table[(index + i * i) % size] = DELETED;
                count--;
                return;
            }
            i++;
            if (i >= size) {
                break;
            }
        }
        std::cout << "Element not found" << std::endl;
    }

    int search(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != EMPTY) {
            if (table[(index + i * i) % size] == key) {
                return (index + i * i) % size;
            }
            i++;
            if (i >= size) {
                break;
            }
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == EMPTY) {
                std::cout << "- ";
            } else if (table[i] == DELETED) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
