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

    // Resizing the hash table 
    void resize() {
        int oldSize = size;
        std::vector<int> oldTable = table;

        // Resize the table to a new prime size
        size = nextPrime(2 * oldSize);
        table = std::vector<int>(size, EMPTY);
        count = 0;

    
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                insert(oldTable[i]);
            }
        }
    }

public:
    HashTable(int initialSize)
        : EMPTY(-1), DELETED(-2), loadFactorThreshold(0.8) { 
        size = nextPrime(initialSize);  
        table = std::vector<int>(size, EMPTY);  
        count = 0;  // No elements are inserted 
    }

    // Insert function
    void insert(int key) {
        if ((double)count / size > loadFactorThreshold) {
            resize();
        }

        int idx = hashFunction(key);
        int i = 0;

        // Quadratic probing
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

        // Quadratic probing for search
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