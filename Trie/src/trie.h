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
    class trieIterator;
    typedef std::basic_string <E> key_type;
    typedef std::pair<const key_type, T> value_type;
    typedef T mapped_type;
    typedef trieIterator iterator;
    const char lastChar = '#';

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

        E mPath;

        InternalNode(E path){
            mPath = path;
        }

        bool insert(const value_type& value) {
            try {
                using namespace std;
                auto key = get<0>(value);
                string str_key = string(key) + "#";
                auto val = std::get<1>(value);
                cout << key << std::endl << val << endl;
                _node* current = root;
                _node* next;

                // Wort hat mindestens die Laenge 1
                if(key.length() > 1) {
                    for(char& currentChar : str_key) {
                        // aktueller Buchstabe ist nicht das Endzeichen
                        if(!currentChar == '#') {
                            // aktueller Buchstabe ist in Map von current nicht enthalten. Fuege neue Node hinzu.
                            if(current.mappyTheLittleMap.find(currentChar) != current.mappyTheLittleMap.end()) {
                                next = InternalNode(currentChar);
                                current.mappyTheLittleMap.insert(std::pair<E, _node*>(currentChar,next);
                                current = next;
                                // aktueller Buchstabe ist bereits in Map von current enthalten. Setze current auf die Node des Buchstaben.
                            } else  {
                                current = current.mappyTheLittleMap.find(currentChar).get<1>(value);
                            }
                            // Ende des Baums (#) -> insert Leaf
                        } else {
                            current.mappyTheLittleMap.insert(pair<E, _node*>(currentChar,Leaf(value)));
                        }
                    }
                    return true;
                    // Wort hat die Laenge 1
                }else {
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
                root.mappyTheLittleMap.clear();
                return true;
            }catch(...) {
                using namespace std;
                cout << "Clear failed" << endl;
                return false;
            }
        }

        bool erase(const key_type& value){
            try {
                return true;
            }catch(...) {
                using namespace std;
                cout << "An internal error Occurred" << endl;
                return false;
            }
        }

    };

    class TrieIterator {
    public:

        ListIterator() {

        }

        T& operator *() {}

        iterator& operator = (const iterator& rhs){}

        bool operator != (const iterator& rhs) const{}

        bool operator == (const iterator& rhs) const{}

        iterator& operator ++(){}
    };

    /**
    * Method to return whether the Map isEmpty or not
    */
    bool empty() const {
        using namespace std;
        return root.mappyTheLittleMap.empty();
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
            root.mappyTheLittleMap.clear();
        } catch(...) {
            std::cout << "an error occurred" << std::endl;
        }
    }

    iterator lower_bound(const key_type& testElement);
    iterator upper_bound(const key_type& testElement);
    iterator find(const key_type& testElement);
    iterator begin();
    iterator end();

    void showTrie() {

    }

private:
    InternalNode root;
};

#endif // TRIE_H_INCLUDED