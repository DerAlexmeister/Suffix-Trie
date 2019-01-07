//============================================================================
// Name        : Trie.h
// Author      :
// Version     : Version 1.0
// Copyright   :
// Description : Trie.h Template
// Compiler and C++ Version: GNU GCC / C++14 Standard
//============================================================================

#ifndef TRIE_ALGO_TRIE_H
#define TRIE_ALGO_TRIE_H

#include <iostream>
#include <string>
#include <map>

template <class T, class E=char> class Trie {

public:
    class _node;
    class InternalNode;
    class Leaf;
    class trieIterator;
    static InternalNode root;

    typedef std::basic_string <E> key_type;
    typedef std::pair<const key_type, T> value_type;
    typedef T mapped_type;
    typedef trieIterator iterator;

    /**
    * Method to return whether the Map isEmpty or not
    */
    bool empty(){
        return root.empty();
    }

    /**
    *   Insert a single InternalNode or Leaf.
    */
    iterator insert(const value_type& value);

    /**

    *   Delete a single InternalNode or a Leaf.
    */
    void erase(const key_type& value);

    /**
    * Method to clear the Tree.
    * Except for the root.
    */
    void clear();

    class TrieIterator {

    };

    //iterator lower_bound(const key_type& testElement);
    //iterator upper_bound(const key_type& testElement);
    //iterator find(const key_type& testElement);
    //iterator begin();
    //iterator end();

    void showTrie();

    /**
    * Method to generate a PAIR.
    */
    static std::pair<key_type , T> createPair(std::string word, T meaning) {
        std::basic_string<E> wor  = word;
        return std::make_pair<const key_type, T>(wor, meaning);
    }

    class _node {
    public:
        virtual bool insert(const value_type& value) = 0;
        virtual bool clear() = 0;
        virtual bool erase(const key_type& value) = 0;
    };

    class Leaf:public _node {
    public:
        mapped_type& mWord;
        Leaf(mapped_type &value){
            mWord = value;
        }
        bool insert(const value_type& value);
        bool clear();
        bool erase(const key_type& value);
    };

    class InternalNode:public _node {
    public:
        std::map<E, _node*> mappyTheLittleMap;
        bool insert(const value_type& value) {
            try {
                using namespace std;
                auto key = value.first;
                string str_key = string(key) + "#";
                auto val = value.second;
                cout << key << std::endl << val << endl;
                InternalNode current = this;
                InternalNode next;
                if(key.length() > 1) {
                    for(char& currentChar : str_key) {
                        if(!currentChar == '#' || !current.mappyTheLittleMap.empty()) {
                            if(current.mappyTheLittleMap.find(currentChar) != current.mappyTheLittleMap.end()) {
                                next = InternalNode();
                                current.mappyTheLittleMap.insert(currentChar, *next);
                                current = next;
                            } else  {
                                current = *current.mappyTheLittleMap.find(currentChar).Second;
                            }
                        } else {
                            mappyTheLittleMap.insert(currentChar,Leaf(value));
                        }
                    }
                    return true;
                } else {
                    cout << "Word cant have a length of zero" << endl;
                    return false;
                }
            } catch (...) {
                using namespace std;
                cout << "An error occurred" << endl;
                return false;
            }
        }

        bool clear(){
            try {
                mappyTheLittleMap.clear();
                return true;
            }catch(...) {
                using namespace std;
                cout << "Clear failed" << endl;
                return false;
            }
        }

        bool erase(const key_type& value);

        bool empty(){
            return this -> mappyTheLittleMap.empty();
        }

    };
};

template<class T, class E>
bool Trie<T, E>::Leaf::insert(const Trie::value_type &value) {
    return false;
}

template<class T, class E>
bool Trie<T, E>::Leaf::clear() {
    return false;
}

template<class T, class E>
bool Trie<T, E>::Leaf::erase(const Trie::key_type &value) {
    return false;
}

template<class T, class E>
bool Trie<T, E>::InternalNode::erase(const Trie::key_type &value) {
    using namespace std;
    string str_key = string(value) + "#";
    cout << str_key << endl;
    bool newDelete = true;
    InternalNode  current = this;
    InternalNode deleteNode;
    if (!(current.mappyTheLittleMap.empty())) {
        for(char& currentChar : str_key) {
            if(current.mappyTheLittleMap.find(currentChar) != current.mappyTheLittleMap.end()) {
                if (current.mappyTheLittleMap.size() == 1 && newDelete) {
                    deleteNode = current;
                    newDelete = false;
                } else if (current.mappyTheLittleMap.size() > 1) {
                    newDelete = true;
                }
            } else {
                return false;
            }
            current = *current.mappyTheLittleMap.find(currentChar).second;
        }
        deleteNode.mappyTheLittleMap.clear();
    } else {
        return false;
    }
}

template<class T, class E>
typename Trie<T, E>::iterator Trie<T, E>::insert(const Trie::value_type &value) {
    root.insert(value);
}

template<class T, class E>
void Trie<T, E>::erase(const Trie::key_type &value) {
    root.erase(value);
}

template<class T, class E>
void Trie<T, E>::clear() {
    try {
        clear();
    } catch(...) {
        std::cout << "an error occurred" << std::endl;
    }
}

template<class T, class E>
void Trie<T, E>::showTrie() {

}

#endif //TRIE_ALGO_TRIE_H
