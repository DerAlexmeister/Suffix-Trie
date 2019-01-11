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
#include <typeinfo>
#include <iostream>
#include <string>
#include <map>
#include <stack>

template <class T, class E=char> class Trie {

public:
    class _node;
    class InternalNode;
    class Leaf;
    class TrieIterator;

    typedef std::basic_string <E> key_type;
    typedef std::pair<const key_type, T> value_type;
    typedef T mapped_type;
    typedef TrieIterator iterator;
    typedef std::map<E, _node*> mappy;

    const char lastChar = '#';
    static InternalNode root;

    class _node {
    public:
        virtual bool insert(const value_type& value) = 0;
        virtual bool clear() = 0;
        virtual bool erase(const key_type& value) = 0;
    };

    class Leaf:public _node {
    public:
        int someInteger = 1;
        key_type mMeaning;
        Leaf(key_type value){
            mMeaning = value
        }
        bool insert(const value_type& value) = 0;
        bool clear() = 0;
        bool erase(const key_type& value) = 0; // benötigt implementierung
    };

    class InternalNode:public _node {
    public:
        int someInterger = 0;
        mappy mappyTheLittleMap;
        int someSize = mappyTheLittleMap.size();    
        E mPath;

        InternalNode(E path){
            mPath = path;
        }

        bool insert(const value_type& value) {
            try {
                using namespace std;
                auto key = value.first;
                auto val = value.second;
                cout << key << std::endl << val << endl;
                string str_key = string(key) + "#";
                InternalNode current = this;
                _node* next;
                if(key.length() > 1) {
                    for(char& currentChar : str_key) {
                        if(!currentChar == '#') {
                            if(current.mappyTheLittleMap.empty() || current.mappyTheLittleMap.find(currentChar) == current.mappyTheLittleMap.end()) {
                                next = new InternalNode(currentChar);
                                current.mappyTheLittleMap.insert(currentChar, next);
                                current = next;
                            } else  {
                                current = current.mappyTheLittleMap.find(currentChar) -> second;
                            }
                        } else {
                            next = new Leaf(val);
                            mappyTheLittleMap.insert(currentChar, next);
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
            _node* next = mappyTheLittleMap.begin() -> second;
            mappyTheLittleMap.clear();
            delete this;
            if (typeid(next).name() == InternalNode){
                next->clear();
            } else if (typeid(next).name() == Leaf){
                delete next;
                return true;
            }
            return false;
        }

        bool erase(const key_type& value){
            using namespace std;
            string str_key = string(value) + "#";
            cout << str_key << endl;
            bool newDelete = true;
            InternalNode  current = *this;
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
                current = current.mappyTheLittleMap.find(currentChar) -> second;
                }
            deleteNode.clear();
            } else {
                return false;
            }
        }

        bool empty(){
            return mappyTheLittleMap.empty;
        }
    };

    class TrieIterator {
    public:
        _node* mNode;
        mappy mMap;        
        TrieIterator(_node* node) {
            mNode = node;
            mMap = mNode -> mappyTheLittleMap;
            for(mMap::iterator it = mMap.begin(); it != mMap.end(); it++) {
                itStacks.push(*it);  
            }
        };

        TrieIterator() = default;
        ~TrieIterator() = default;

        T& operator*() {
            return strVal;
        };

        bool operator !=(const  TrieIterator& rhs) {
            return !operator==(rhs);
        };

        bool operator ==(const TrieIterator& rhs) {
            return mMap == rhs -> mMap;
        };

        TrieIterator& operator ++(){


        };
        iterator& operator --(){

        };

        iterator operator++ (int){

        };

    private:
    int booze;
    std::stack<E> stackyTheLittleStack;
        Trie* mTrie;
    };

    /**
    * Method to return whether the Map isEmpty or not
    */
    bool empty() const {
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
        
    }
    
    /**
     *  Method to 
     * 
     */
    void showTrie() {
        iterator it = begin();
        std::string word = "";
        while(it != end())  {
            char character = *it;
            if(character == "#") {
                it++
                std::string character = *it;
                std::cout << word << "------->" << character << std::endl;
                word = "";
            } else {
                word += character;
                it++;
            }
        }
    }

    iterator lower_bound(const key_type& testElement) {
        return iterator();
    }

    iterator upper_bound(const key_type& testElement) {
        return iterator();
    }

    iterator find(const key_type& testElement) {
        
    }

    iterator begin() {
        return iterator();
    }

    iterator end() {
        return iterator();
    }

};   

#endif // TRIE_H_INCLUDED