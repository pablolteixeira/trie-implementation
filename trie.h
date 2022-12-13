// C++ implementation of search and insert
// operations on Trie
#include <bits/stdc++.h>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int length;
    int position;
    bool isEndOfWord = false;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *trie_getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void trie_insert(struct TrieNode *root, string key, int position, int length)
{
    struct TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = trie_getNode();
        pCrawl = pCrawl->children[index];
    }
    // mark last node as leaf
    pCrawl->position = position;
    pCrawl->length = length;
    pCrawl->isEndOfWord = true;
    
}

int trie_count_prefix(struct TrieNode *node) {
    int counter_prefix = 0;

    struct TrieNode *pCrawl = node;
    
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (pCrawl->children[i]) {
            counter_prefix += trie_count_prefix(pCrawl->children[i]);


            if (pCrawl->children[i]->isEndOfWord) {
                counter_prefix++;
            }

        }
    }   

    return counter_prefix;
}

// Returns true if key presents in trie, else
// false
void trie_search(struct TrieNode *root, string key)
{   
    struct TrieNode *pCrawl = root;
    bool exit = false;
    int value;

    for (int i = 0; i < key.length(); ++i)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]) {
            exit = true;
            break;
        } 

        pCrawl = pCrawl->children[index];
    }
    
    if (exit) {
        cout << key << " is not prefix" << endl;
    } else if (pCrawl->isEndOfWord) {

        value = trie_count_prefix(pCrawl) + 1;
        
        cout << key << " is prefix of " << value << " words" << endl;

        std::cout << key << " is at (" << pCrawl->position << "," << pCrawl->length << ")" << std::endl;
    } else {
        value = trie_count_prefix(pCrawl);

        if (value == 0) {
            cout << key << " is not prefix" << endl;
        } else {
            cout << key << " is prefix of " << value << " words" << endl;
        }
    }

    
}

