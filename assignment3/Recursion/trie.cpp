//
//  trie.cpp
//  Recursion
//
//  Created by Sergey Nikiforov on 18/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "trie.hpp"


// default constructor
Trie::Trie()
: root(std::make_shared<TrieNode>('\0', false)) { }


// overloaded constructor from ifstream
Trie::Trie(std::ifstream &infile)
: root(std::make_shared<TrieNode>('\0', false)) {
    std::string word = "";
    int i = 0;
    while (std::getline(infile, word)) {
        addWord(word);
        ++i;
    }
    std::cout << i << " words were added to the trie" << std::endl;
}


// string -> void
// adds a given word to the trie
void Trie::addWord(const std::string &word) {
    root->addWord(word);
}


// string -> bool
// returns true if the trie contains at least one word with a given prefix; calls helper recursive function
bool Trie::containsPrefix(const std::string &prefix) const {
    return root->containsPrefix(prefix);
}


// string -> TrieNode
// returns ref to shared_ptr to the TrieNode defined  by the given prefix
std::shared_ptr<TrieNode> &Trie::getNode(const std::string &prefix) {
    return (prefix.empty()) ? root : root->getPrefixedNode(prefix);
}


// string -> shared_ptr<vector<string>>
// returns a shared_ptr to vector of valid words starting with a given prefix
std::shared_ptr<std::vector<std::string>> Trie::getWordsWithPrefix(const std::string &prefix) {
    auto start_node = this->getNode(prefix);
    std::set<unsigned int> visited{};
    auto words = std::make_shared<std::vector<std::string>>();
    start_node->getValidWords(prefix, visited, words);
    return words;
}
