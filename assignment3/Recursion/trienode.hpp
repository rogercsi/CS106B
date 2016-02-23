//
//  trienode.hpp
//  Recursion
//
//  Created by Sergey Nikiforov on 19/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#pragma once
#ifndef trienode_hpp
#define trienode_hpp

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <set>


class TrieNode {
public: // functions
    TrieNode(const char &l, const bool &iw = false);
    unsigned int inline getId() const { return id; }
    
    char inline getLetter() const { return letter; }
    void inline setLetter(const char l) { letter = l; }
    
    bool inline getIsWord() const { return is_word; }
    void inline setIsWord(const bool &iw) { is_word = iw; }
    
    unsigned int inline getPrefixes() const { return prefixes; }
    void inline incrPrefixes() { ++prefixes; }
    
    void addWord(const std::string &word);
    bool containsPrefix(const std::string &prefix) const;
    std::shared_ptr<TrieNode> &getPrefixedNode(const std::string &prefix);
    void getValidWords(const std::string &prefix, std::set<unsigned int> &visited, std::shared_ptr<std::vector<std::string>> &words);
private: // functions
    TrieNode();
private: // data
    const unsigned int id;
    char letter;
    bool is_word;
    unsigned int prefixes;
    std::map <char, std::shared_ptr<TrieNode>> children;
    static unsigned int counter;
};

#endif /* trienode_hpp */
