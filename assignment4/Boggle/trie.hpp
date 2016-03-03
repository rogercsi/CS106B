//
//  trie.hpp
//  Recursion
//
//  Created by Sergey Nikiforov on 18/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#pragma once
#ifndef trie_hpp
#define trie_hpp

#include "trienode.hpp"
#include <fstream>

class Trie {
public: // functions
    Trie();
    Trie(std::ifstream &infile);
    std::unique_ptr<TrieNode> &getRoot() { return root; }
    void addWord(const std::string &word);
    bool containsPrefix(const std::string &prefix) const;
    bool containsWord(const std::string &word) const;
    std::shared_ptr<std::vector<std::string>> getWordsWithPrefix(const std::string &prefix);
    std::unique_ptr<TrieNode> &getNode(const std::string &prefix);
private: // data
    std::unique_ptr<TrieNode> root;
};

#endif /* trie_hpp */
