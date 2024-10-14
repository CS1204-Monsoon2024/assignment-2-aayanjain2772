#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;     // The hash table
    int size;                   // Current size of the table
    int count;                  // Number of elements in the table
    const int EMPTY = -1;       // Empty slots are denoted by -1
    const int DELETED = -2;     // Deleted slots are denoted by -2
    const double loadFactorThreshold = 0.8;

    // Function to calculate the next prime number >= n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Hash function
    int hashFunction(int key) {
        return key % size;
    }

    // Resize the hash table when the load factor exceeds the threshold
    void resize() {
        int oldSize = size;
        std::vector<int> oldTable = table;

        // Resize the table to a new prime size
        size = nextPrime(2 * oldSize);
        table = std::vector<int>(size, EMPTY);
        count = 0;

        // Rehash all the elements from the old table
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                insert(oldTable[i]);
            }
        }
    }

public:
    // Constructor to initialize the hash table with a size that's at least as big as 'initialSize'
    HashTable(int initialSize) {
        size = nextPrime(initialSize);  // Ensure the size is a prime number greater than or equal to 'initialSize'
        table = std::vector<int>(size, EMPTY);  // Initialize the hash table with 'EMPTY' values
        count = 0;  // No elements inserted initially
    }

    // Insert function
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
            if (i == size / 2 + 1) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
        }

        table[(idx + i * i) % size] = key;
        count++;
    }

    // Search function
    int search(int key) {
        int idx = hashFunction(key);
        int i = 0;

        while (table[(idx + i * i) % size] != EMPTY) {
            if (table[(idx + i * i) % size] == key) {
                return (idx + i * i) % size;
            }
            i++;
            if (i == size / 2 + 1) {
                break;
            }
        }
        return -1;  // Not found
    }

    // Remove function
    void remove(int key) {
        int idx = search(key);
        if (idx == -1) {
            std::cout << "Element not found" << std::endl;
            return;
        }
        table[idx] = DELETED;
        count--;
    }

    // Print the hash table
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
