//
//  trienode.cpp
//  Recursion
//
//  Created by Sergey Nikiforov on 19/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "trienode.hpp"

unsigned int TrieNode::counter = 0;

// default constructor
TrieNode::TrieNode()
: id(counter), letter('\0'), is_word(false), prefixes(0) { ++counter; }


// overloaded constructor
TrieNode::TrieNode(const char &l, const bool &iw)
: id(counter), letter(l), is_word(iw), prefixes(0) { ++counter; }


// string -> void
// recursively adds word
void TrieNode::addWord(const std::string &word) {
    if (word.empty()) {
        is_word = true;
    } else {
        ++prefixes;
        if (children.find(word.front()) != children.end()) {
            children[word.front()]->addWord(word.substr(1));
        } else {
            children[word.front()] = std::make_shared<TrieNode>(word.front());
            children[word.front()]->addWord(word.substr(1));
        }
    }
}


// string -> bool
// recursively traverses a trie using a given prefix
// if there's no such prefix in the trie the function returns false.
// as all the leaves in a trie denote valid words, if we could find a prefix ->
// -> there's certainly at least 1 valid word down the trie
bool TrieNode::containsPrefix(const std::string &prefix) const {
    if (prefix.empty()) {
        return true;
    } else {
        if (children.find(prefix.front()) != children.end()) {
            return children.at(prefix.front())->containsPrefix(prefix.substr(1));
        } else {
            return false;
        }
    }
}


// string -> TrieNode
// recursively traverses a trie and returns a shared_ptr to TrieNode denoted with a given non-empty prefix
// assumes the trie contains the prefix, otherwise throws out_of_range exception
std::shared_ptr<TrieNode> &TrieNode::getPrefixedNode(const std::string &prefix) {
    if (prefix.size() - 1 == 0) {
        return children.at(prefix.front());
    } else {
        return children.at(prefix.front())->getPrefixedNode(prefix.substr(1));
    }
}


// string, set<unsigned int>, shared_ptr<vector<string>> -> void
// assumes the trie contains the prefix, otherwise throws out_of_range exception
// recursively DFSes through the trie populating vector of valid words pointed by shared_ptr
void TrieNode::getValidWords(const std::string &prefix, std::set<unsigned int> &visited, std::shared_ptr<std::vector<std::string>> &words) {
    visited.insert(id);
    if (is_word) {
        words->push_back(prefix);
    }
    for (auto it = children.cbegin(); it != children.cend(); ++it) {
        if (visited.find(it->second->getId()) == visited.end()) {
            it->second->getValidWords(prefix + it->first, visited, words);
        }
    }
}
