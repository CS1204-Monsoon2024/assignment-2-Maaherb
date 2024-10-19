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
        int newSize = nextPrime(size * 2);
        std::vector<int> oldTable = table;
        table = std::vector<int>(newSize, -1);
        size = newSize;
        count = 0;
        for (int key : oldTable) {
            if (key != -1 && key != -2) {
                insert(key);
            }
        }
    }

public:
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table = std::vector<int>(size, -1);
        count = 0;
    }

    HashTable(HashTable&& other) noexcept {
        size = other.size;
        count = other.count;
        table = std::move(other.table);
        other.size = 0;
        other.count = 0;
    }

    HashTable& operator=(HashTable&& other) noexcept {
        if (this != &other) {
            size = other.size;
            count = other.count;
            table = std::move(other.table);
            other.size = 0;
            other.count = 0;
        }
        return *this;
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
        if (static_cast<float>(count) / size > 0.8) {
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
