#pragma once
#include <forward_list>
#include <string>
#include "sharedstruc.h"
using namespace std;

/*by tyler*/

struct TrieNode {
    TrieNode* children[26];
    bool endofWord;
    forward_list<linkedNode>* data;
    TrieNode() {
        endofWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class MyTrie {
private:
    TrieNode* root;
public:
    MyTrie() {
        root = new TrieNode();
    }
    bool insert(string name, int year, int m, int f) {
        TrieNode* curr = root;
        for (char c : name) {
            int i = c - 'a'; //gets index i from ascii value
            if (!curr->children[i]) {
                curr->children[i] = new TrieNode;
            }
            curr = curr->children[i];
        }
        if (curr->endofWord == true) { //if name already in, simply update its values
            bool newYear = true;
            if (curr->data->front().year == year) {
                newYear = false;
            }
            if (newYear) {
                curr->data->push_front(linkedNode(year, m, f));
            }
            else { //update data
                curr->data->front().mCount += m;
                curr->data->front().fCount += f;
            }
        }
        else { //name not in, need to create data list
            curr->endofWord = true;
            curr->data = new forward_list<linkedNode>;
            curr->data->push_front(linkedNode(year, m, f));
        }
        return true;
    }
    forward_list<linkedNode>* search(string name) {
        TrieNode* curr = root;
        for (char c : name) {
            int i = c - 'a'; //gets index i from ascii value
            if (!curr->children[i]) {
                return nullptr;
            }
            curr = curr->children[i];
        }
        if (curr->endofWord == true) { //name is found
            return curr->data;
        }
        else {
            return nullptr;
        }
    }
};