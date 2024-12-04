#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <utility>
#include <chrono>
#include "MyTrie.h"
#include "MyHashTable.h"
#include "gnuplot-iostream.h"

/*
Skeleton written by Tyler
Gnuplot implementation written by Soraya
*/

void lineToData(string line, string& name, bool& isMale, int& count) {
    auto c = line.find(',');
    name = line.substr(0, c);
    if (line[c + 1] == 'F') {
        isMale = false;
    }
    else {
        isMale = true;
    }
    string temp = line.substr(c + 3);
    count = stoi(temp);
}

bool verifyNameInput(string& toParse) {
    string temp = "";
    for (char c : toParse) {
        if (isdigit(c)) {
            return false;
        }
        if (!isalpha(c)) {
            return false;
        }
        c = tolower(c);
        temp += c;
    }
    toParse = temp;
    return true;
}

int main()
{
    string input;
    cout << "Select the data structure you'd like to use: \n1. Trie \n2. Hash" << endl;
    bool waiting = true;
    int numDataPoints = 0;
    bool trieRoute;
    clock_t t;
    MyTrie newTrie;
    MyHashTable myHashTable;
    ifstream file("names/yob1880.txt");
    file.close();
    while (waiting) {
        cin >> input;
        if (input == "1" or input == "Trie" or input == "trie") { //LOADING TRIE
            t = clock();
            cout << "loading via Trie..." << endl;
            for (int i = 1880; i < 2024; i++) {
                string fileName = "names/yob";
                fileName += to_string(i);
                fileName += ".txt";
                file.open(fileName);
                string line;
                if (file.is_open()) {
                    while (getline(file, line)) {
                        numDataPoints++;
                        string name;
                        bool isMale;
                        int count;
                        lineToData(line, name, isMale, count);
                        name[0] = tolower(name[0]);
                        //cout << name << ", " << isMale << ", " << count << endl;
                        if (isMale) {
                            newTrie.insert(name, i, count, 0);
                        }
                        else {
                            newTrie.insert(name, i, 0, count);
                        }
                    }
                    file.close();
                }
            }
            t = clock() - t;
            cout << "insertion took " << t / CLOCKS_PER_SEC << " seconds for " << numDataPoints << " instances of data." << endl;
            trieRoute = true;
            waiting = false;
        }
        else if (input == "2" or input == "Hash" or input == "hash") { //LOADING HASH
            t = clock();
            cout << "loading via Hashtable..." << endl;
            for (int i = 1880; i < 2024; i++) {
                string fileName = "names/yob";
                fileName += to_string(i);
                fileName += ".txt";
                file.open(fileName);
                string line;
                if (file.is_open()) {
                    while (getline(file, line)) {
                        numDataPoints++;
                        string name;
                        bool isMale;
                        int count;
                        lineToData(line, name, isMale, count);
                        name[0] = tolower(name[0]);
                        //cout << name << ", " << isMale << ", " << count << endl;
                        if (isMale) {
                            myHashTable.insert(name, i, count, 0);//INSERT MEM COUNT
                        }
                        else {
                            myHashTable.insert(name, i, 0, count);//INSERT FEM COUNT
                        }
                    }
                    file.close();
                }
            }
            t = clock() - t;
            cout << "insertion took " << t / CLOCKS_PER_SEC << " seconds for " << numDataPoints << " instances of data." << endl;
            trieRoute = false;
            waiting = false;
        }
        else if (input == "end") {
            waiting = false;
        }
        else {
            cout << "bad input, please try again" << endl;
        }
    }
    Gnuplot gp;
    while (input != "end") {
        cout << "\nType a first name or type \"end\" to end the program" << endl;
        cin >> input;
        if (input != "end") {
            if (verifyNameInput(input)) {
                auto t = clock();
                forward_list<linkedNode>* searchedList;
                if (trieRoute) {
                    searchedList = newTrie.search(input);
                }
                else {
                    searchedList = myHashTable.search(input);
                }
                if (!searchedList) {
                    cout << "name not found!" << endl;
                }
                else {
                    t = clock() - t;
                    cout << "completed search in " << t << " clocks" << endl;

                    std::vector<std::pair<double, double>> male_data;
                    std::vector<std::pair<double, double>> female_data;

                    int maxFemaleCount = 0, maxMaleCount = 0;
                    int femaleYear = 0, maleYear = 0;

                    for (const auto& c : *searchedList) {
                        male_data.emplace_back(c.year, c.mCount);
                        female_data.emplace_back(c.year, c.fCount);

                        if (c.fCount > maxFemaleCount) {
                            maxFemaleCount = c.fCount;
                            femaleYear = c.year;
                        }

                        if (c.mCount > maxMaleCount) {
                            maxMaleCount = c.mCount;
                            maleYear = c.year;
                        }
                    }

                    cout << "\nMost popular year for females: " << femaleYear << " with " << maxFemaleCount << " people" << endl;
                    cout << "Most popular year for males: " << maleYear << " with " << maxMaleCount << " people\n" << endl;

                    gp << "set term qt font \"Arial,9\"\n";
                    gp << "set title 'Popularity of the name " << input << " over time'\n";
                    gp << "set xlabel 'Year'\n";
                    gp << "set ylabel 'Count'\n";
                    gp << "set xrange [*:*]\n";
                    gp << "set yrange [0:*]\n";
                    gp << "plot '-' with lines title 'Female', '-' with lines title 'Male'\n";

                    gp.send1d(female_data);
                    gp.send1d(male_data);
                }
            }
            else {
                cout << "invalid name." << endl;
            }
        }
    }
    return 0;
}