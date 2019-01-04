//============================================================================
// Name        : Trie.h
// Author      :
// Version     : Version 1.0
// Copyright   :
// Description : Trie.h Template
// Compiler and C++ Version: GNU GCC / C++14 Standard
//============================================================================

#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED
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
    const char lastChar = '#';

    /**
    * Method to return whether the Map isEmpty or not
    */
    bool empty(){
        return root.empty();
    }

    /**
    *   Insert a single InternalNode or Leaf.
    */
    iterator insert(const value_type& value) {
        root.insert(value);
    }

    /**

    *   Delete a single InternalNode or a Leaf.
    */
    void erase(const key_type& value) {
        root.erase(value);
    }

    /**
    * Method to clear the Tree.
    * Except for the root.
    */
    void clear() {
        try {
            //root.clear();
        } catch(...) {
            std::cout << "an error occurred" << std::endl;
        }
    }

    class TrieIterator {

    };

    iterator lower_bound(const key_type& testElement);
    iterator upper_bound(const key_type& testElement);
    iterator find(const key_type& testElement);
    iterator begin();
    iterator end();

    void showTrie() {

    }

    /**
    * Method to generate a PAIR.
    */
    static std::pair<key_type, mapped_type> createPair(std::string word, std::string meaning) {
        return std::make_pair<key_type, mapped_type>(word, meaning);
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
        bool insert(const value_type& value) = 0;
        bool clear() = 0;
        bool erase(const key_type& value) = 0;
    };

    class InternalNode:public _node {
    public:
        std::map<E, _node*> mappyTheLittleMap;
        bool insert(const value_type& value) {
            try {
                using namespace std;
                auto key = get<0>(value);
                string str_key = string(key) + "#";
                auto val = std::get<1>(value);
                cout << key << std::endl << val << endl;
                InternalNode * current = this;
                InternalNode * next;
                if(key.length() > 1) {
                    for(char& currentChar : str_key) {
                        if(!currentChar == '#' || !current.mappyTheLittleMap.empty()) {
                            if(current.mappyTheLittleMap.find(currentChar) != current.mappyTheLittleMap.end()) {
                                next = InternalNode();
                                current.mappyTheLittleMap.insert(std::pair<E, _node*>(currentChar,next));
                                current = next;
                            } else  {
                                current = current.mappyTheLittleMap.find(currentChar).get<1>(value);
                            }
                        } else {
                            current.mappyTheLittleMap.insert(pair<E, _node*>(currentChar,Leaf(value)));
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

        bool erase(const key_type& value){
            using namespace std;
            auto key = get<0>(value);
            string str_key = string(key) + "#";
            auto val = std::get<1>(value);
            cout << key << std::endl << val << endl;
            bool newDelete = true;
            InternalNode* current = root;
            InternalNode* deleteNode;
            if (!current.mappyTheLittleMap.empty()) {
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
                    current = current.mappyTheLittleMap.find(currentChar).get<1>(value);
                }
                deleteNode -> clear();
            } else {
                return false;
            }
        }

        bool empty(){
            return this -> mappyTheLittleMap.empty();
        }

    };
};

#endif // TRIE_H_INCLUDED
