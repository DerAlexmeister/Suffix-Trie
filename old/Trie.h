//============================================================================
// Name        : Trie.h
// Author      :
// Version     : Version 1.0
// Copyright   :
// Description : Main Program
// Compiler and C++ Version: GNU GCC / C++14 Standard
//============================================================================



#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H
#include <iostream>

template <class T, class E=char> class Trie {

public:
    typedef std::basic_string <E> key_type;
    typedef std::pair<const key_type, T> value_type;
    typedef T mapped_type;
    typedef mapped_type iterator;

    template<mapped_type> class _node {

    public:

        _node(T value, _node* left = nullptr, _node* right = nullptr) : val(value), leftChild(left), rightChild(right) {}

        _node*& left() {
            return leftChild;
        }

        _node*& right() {
            return rightChild;
        }

        T& value() {
            return val;
        }

    private:
        T val;
        _node *leftChild, *rightChild;
    };

private:
    _node<T> root;

    /**
     * Method to check whether a Trie has no leaves or not.
     * @return will return true in case the trie has no leaves
     */
    bool empty() const {
        return true;
    }

    /**
     *
     * @param value
     * @return
     */
    iterator insert(const value_type &value) {

    }


    /**
     *
     * @param value
     */
    void erase(const key_type& value) {

    }

    /**
     *
     */
    void clear() {

    }

    /**
     *
     * @param testElement
     * @return
     */
    iterator lower_bound(const key_type& testElement) {

    }

    /**
     *
     * @param testElement
     * @return
     */
    iterator upper_bound(const key_type& testElement) {

    }

    /**
     *
     * @param testElement
     * @return
     */
    iterator find(const key_type& testElement) {

    }

    /**
     *
     * @return
     */
    iterator begin() {

    }


    /**
     *
     * @return
     */
    iterator end() {

    }
};

#endif //TRIE_TRIE_H
