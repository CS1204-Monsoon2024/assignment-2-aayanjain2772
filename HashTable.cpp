#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int count;
    int EMPTY;
    int DELETED;
    double loadFactorThreshold;

    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int hashFunction(int key) {
        return abs(key) % size;  // Added abs() to handle negative numbers
    }

    void resize() {
        std::vector<int> oldTable = table;
        int oldSize = size;
        
        size = nextPrime(2 * oldSize);
        table = std::vector<int>(size, EMPTY);
        count = 0;

        // Reinsert all valid elements
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                int key = oldTable[i];
                int idx = hashFunction(key);
                int j = 0;
                
                while (table[(idx + j * j) % size] != EMPTY) {
                    j++;
                }
                table[(idx + j * j) % size] = key;
                count++;
            }
        }
    }

public:
    HashTable(int initialSize) : EMPTY(-1), DELETED(-2), loadFactorThreshold(0.5) {
        size = nextPrime(initialSize);
        table = std::vector<int>(size, EMPTY);
        count = 0;
    }

    void insert(int key) {
        if ((double)count / size > loadFactorThreshold) {
            resize();
        }
        
        int idx = hashFunction(key);
        int i = 0;

        while (table[(idx + i * i) % size] != EMPTY && table[(idx + i * i) % size] != DELETED) {
            if (table[(idx + i * i) % size] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
            if (i >= size) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
        }
        table[(idx + i * i) % size] = key;
        count++;
    }

    int search(int key) {
        int idx = hashFunction(key);
        int i = 0;

        while (table[(idx + i * i) % size] != EMPTY) {
            if (table[(idx + i * i) % size] == key) {
                return (idx + i * i) % size;
            }
            i++;
            if (i >= size) break;
        }
        return -1;
    }

    void remove(int key) {
        int idx = search(key);
        if (idx == -1) {
            std::cout << "Element not found" << std::endl;
            return;
        }
        table[idx] = DELETED;
        count--;
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == EMPTY || table[i] == DELETED) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};