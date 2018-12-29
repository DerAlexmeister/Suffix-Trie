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
#include <map>

template <class T, class E=char> class Trie {

public:
    class trieIterator;
    typedef std::basic_string <E> key_type;
    typedef std::pair<const key_type, T> value_type;
    typedef T mapped_type;
    typedef trieIterator iterator;

    class _node {
    public:
        virtual bool insert() = 0;
        virtual bool clear() = 0;
        virtual bool erase(const key_type& value) = 0;
    };

    class Leaf:public _node {
    public:
        mapped_type& mWord;
        Leaf(mapped_type &value){
            mWord = value;
        }
        bool insert();
        bool clear();
        bool erase(const key_type& value);

    };

    class InternalNode:public _node {
    public:
        bool insert();
        bool clear();
        bool erase(const key_type& value);
        std::map<E, _node*> mappyTheLittleMap;
    };

    class TrieIterator {


    };

    /**
    * Constructor
    */
    Trie ();

    /**
    * Method to return whether the Map isEmpty or not
    */
    bool empty() const {
        return root.mappyTheLittleMap.size() == 0;
    }


    iterator insert(const value_type& value);

    /**
    *
    */
    void erase(const key_type& value) {
        root.erase(value);
    }


    void clear() {
        try {
            root = nullptr;
        } catch(...) {
            std::cout << "an error occurred" << std::endl;
        }
    }

    iterator lower_bound(const key_type& testElement);
    iterator upper_bound(const key_type& testElement);
    iterator find(const key_type& testElement);
    iterator begin();
    iterator end();

private:
    InternalNode root;
};



#endif // TRIE_H_INCLUDED
