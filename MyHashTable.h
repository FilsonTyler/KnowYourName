#pragma once
#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <string>
#include "sharedstruc.h"

/*by Ibrahim edited for compatability by Tyler*/

class MyHashTable {
public:
    // Hash table type: key is a name, value is a forward list
    std::unordered_map<std::string, forward_list<linkedNode>*> hashTable;

    // Function to insert data into the hash table
    void insert(const std::string& name, int year, int countMale, int countFemale) {
        // Check if the name already exists
        auto it = hashTable.find(name);
        if (it == hashTable.end()) {
            // If name doesn't exist, create a new forward list with the data
            hashTable[name] = new forward_list<linkedNode>;
            hashTable[name]->push_front(linkedNode(year, countMale, countFemale));
        }
        else {
            // Append new data to the forward list
            if (hashTable[name]->front().year == year) {
                hashTable[name]->front().fCount += countFemale;
                hashTable[name]->front().mCount += countMale;
            }
            else {
                hashTable[name]->push_front(linkedNode(year, countMale, countFemale));
            }
        }
    }

    // Function to search for a name and display its forward list
    forward_list<linkedNode>* search(const std::string& name) {
        auto it = hashTable.find(name);
        if (it == hashTable.end()) {
            return nullptr;
        }
        else {
            return hashTable[name];
        }
    }
};