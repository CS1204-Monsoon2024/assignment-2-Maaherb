#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int count;

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
        std::cout << "Resizing table from size " << size << " to size " << nextPrime(size * 2) << std::endl;
        int newSize = nextPrime(size * 2);
        std::vector<int> oldTable = table;
        table = std::vector<int>(newSize, -1);
        size = newSize;
        count = 0;
        for (int i = 0; i < oldTable.size(); i++) {
            if (oldTable[i] != -1 && oldTable[i] != -2) {
                table[i] = oldTable[i];
                count++;
            }
        }
    }

    void insertWithoutResize(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1 && table[(index + i * i) % size] != -2) {
            i++;
        }
        table[(index + i * i) % size] = key;
        count++;
    }

public:
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table = std::vector<int>(size, -1);
        count = 0;
    }

    void insert(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1 && table[(index + i * i) % size] != -2) {
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
        std::cout << "Inserted " << key << " at index " << (index + i * i) % size << std::endl;
        std::cout << "Current load factor: " << static_cast<float>(count) / size << std::endl;
        if (static_cast<float>(count + 1) / size > 0.8) {
            resize();
        }
    }

    void remove(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1) {
            if (table[(index + i * i) % size] == key) {
                table[(index + i * i) % size] = -2;
                count--;
                std::cout << "Removed " << key << " from index " << (index + i * i) % size << std::endl;
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
        while (table[(index + i * i) % size] != -1) {
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
            if (table[i] == -1) {
                std::cout << "- ";
            } else if (table[i] == -2) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
