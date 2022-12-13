#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "trie.h"

int main() {
    string entrada;
    getline(cin, entrada);

    vector<string> vetor;

    string word = "";
    
    for (int i = 0; i < entrada.length(); i++) {
        if (entrada[i] == ' ') {
            if (word != "0") {
                vetor.push_back(word);
            }
            word.clear();
        } else {
            word += entrada[i];
        }
    }

    fstream myfile;

    struct TrieNode *root = trie_getNode();
    int position = 0, length = 0, position_input = 0;
    word.clear();

    myfile.open(vetor[0]);
    char c;

    if (myfile.is_open()) {
        bool open_word = false, open_phrase = false;

        while (!myfile.eof()) {
            myfile.get(c);

            if (c == '[' && open_phrase == false) {
                open_word = true;
                word.clear();
                position_input = position;
                length = 1;

            } else if (c == '\n') {
                trie_insert(root, word, position_input, length - 1);
                open_phrase = false;
            } else if (c == ']') {
                open_word = false;
                open_phrase = true;
            } else if (open_word) {
                word += c;
            }
            length++;
            position++;
        }
    }
    // Para inserir a ultima palavra
    trie_insert(root, word, position_input, length - 3);

    for (int i = 1; i < vetor.size(); ++i) {
        trie_search(root, vetor[i]);
    } 

    return 0;
}