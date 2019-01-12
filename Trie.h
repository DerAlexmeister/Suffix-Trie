//============================================================================
// Name        : Trie.h
// Author      : Alexander M. Westphal / Paul Schroeder / Klaus Riedl
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
#include <cstring>
#include <stdlib.h>

template<class T, class E = char> class Trie {

public:	
	class _node;
	class InternalNode;
	class Leaf;
	class TrieIterator;
	typedef std::basic_string<E> key_type;
	typedef std::pair<const key_type, T> value_type;
	typedef T mapped_type;
	typedef TrieIterator iterator;
	typedef std::map<E, _node*> mappy;

	static InternalNode root;

	class _node {
	public:
		virtual bool insert(const value_type& value) = 0;
		virtual bool clear() = 0;
		virtual bool erase(const key_type& value) = 0;
		virtual void clearKlausi() = 0;
	};

	class Leaf: public _node {
	public:
		mappy mappyTheLittleMap;
		key_type mMeaning;
		T mPath;
		Leaf(key_type value, T path) {
			mMeaning = value;
			mPath = path;
		}

		bool insert(const value_type& value) {
			return false;
		}

		bool clear(){
			return false;
		}

		bool erase(const key_type& value) {
			return false;
		}

		void clearKlausi() {}
	};

	class InternalNode: public _node {
	public:
		mappy mappyTheLittleMap;
		T mPath;

		InternalNode(T path) {
			mPath = path;
		}

		bool insert(const value_type& value) {
    		try {
        		using namespace std;
        		E currentChar = value.first[0];
        		_node *next;
        		if (!currentChar == '#') {
	        		if (mappyTheLittleMap.empty() || mappyTheLittleMap.find(currentChar) == mappyTheLittleMap.end()) {
		       			next = InternalNode(mPath += currentChar);
		        		mappyTheLittleMap.insert(currentChar, next);
	        		} else {
                		next = mappyTheLittleMap.find(currentChar)->second;
	        		}
        		} else if (!mappyTheLittleMap.count(currentChar)) {
	        		next = Leaf(value.second, mPath += currentChar);
	        		mappyTheLittleMap.insert(currentChar, next);
       			}
        		next->insert(value.first.erase(0, 1), value);
       			return true;
    		} catch (...) {
        		using namespace std;
        		cout << "An error occurred" << endl;
        		return false;
    		}
		}

		void clearKlausi() {
			if (!root.mappyTheLittleMap.empty()) {
				for (typename mappy::iterator it=mappyTheLittleMap.begin(); it!=mappyTheLittleMap.end(); it++) {
					it -> second -> clearKlausi();
					delete it -> second;
				}
				mappyTheLittleMap.clear();
			}
		}

		bool clear() {
			_node* next = mappyTheLittleMap.begin()->second;
			mappyTheLittleMap.clear();
			delete this;
			if (std::strcmp(typeid(next).name(), "InternalNode") == 0) {
				next->clear();
			} else if (std::strcmp(typeid(next).name(), "Leaf") == 0) {
				delete next;
				return true;
			}
			return false;
		}

		void clearTrie() {
			auto iterator = mappyTheLittleMap.begin();
			while (iterator != mappyTheLittleMap.end()) {
				iterator->second->clear();
				delete iterator->second;
				iterator++;
			}
			mappyTheLittleMap.clear();
		}

		bool erase(const key_type& value) {
			using namespace std;
			string str_key = string(value) + "#";
			cout << str_key << endl;
			bool newDelete = true;
			InternalNode current = root;
			InternalNode deleteNode = current;
			if (!(current.mappyTheLittleMap.empty())) {
				for (char& currentChar : str_key) {
					if (current.mappyTheLittleMap.find(currentChar)
							!= current.mappyTheLittleMap.end()) {
						if (current.mappyTheLittleMap.size() == 1
								&& newDelete) {
							deleteNode = current;
							newDelete = false;
						} else if (current.mappyTheLittleMap.size() > 1) {
							newDelete = true;
						}
					} else {
						return false;
					}
					current = current.mappyTheLittleMap.find(currentChar)->second;
				}
				deleteNode.clear();
			} else {
				return false;
			}
			return false;
		}

		bool empty() {
			return mappyTheLittleMap.empty();
		}
	};

	class TrieIterator {
	private:
		std::stack<E> stackyTheLittleStack;
	public:
		_node* mNode;
		mappy mMap;
		TrieIterator(_node* node) {
			mNode = node;
			mMap = mNode -> mappyTheLittleMap;
			auto ki = mMap.begin();
			for (ki; ki != mMap.end(); ki++) {
				int a = *ki.length() - 1;
				E c = *ki(a);
				stackyTheLittleStack.push(c);
			}
		}

		T& operator*() {
			return mNode->mPath;
		};

		bool operator !=(const TrieIterator& rhs) {
			return !operator ==(rhs);
		};

		bool operator ==(const TrieIterator& rhs) {
			return mMap == rhs.mMap;
		};

		/*
		 * if (std::strcmp(typeid(next).name(),"InternalNode")==0){
		 */
		TrieIterator& operator ++() {
			if (std::strcmp(typeid(mNode).name(), "Leaf") == 0 || this->stackyTheLittleStack.empty()) {
				iterator ab;
				while (std::strcmp(typeid(mNode).name(), "Leaf") == 0 || this->stackyTheLittleStack.empty()) {
					ab = operator--();
				}
				iterator cb(mMap.find(stackyTheLittleStack.top())->second);
				stackyTheLittleStack.pop();
				return iterator(cb);
			} else {
				//stack holen -> naechste node -> entferne obersten eintrag von stack
				iterator cb(mMap.find(stackyTheLittleStack.top())->second);
				stackyTheLittleStack.pop();
				return cb;
			}
		};

		iterator& operator --() {
			key_type wo = mNode->mPath;
			key_type res = wo.substr(0, wo.size() - 1);
			return iterator(find(res));
		};

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
		value.first = value.first + "#";	
		return root.insert(value);
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
			root.clearKlausi();
		} catch(...) {
			std::cout << "Root has no children yet! \n";
		}
	}

	/**
	 *  Method to
	 *
	 */
	void showTrie() {
		iterator it = begin();
		std::string word = "";
		while(it != end())  {
			int a = *it.length() - 1;
			E character = *it(a);
			if(character == "#") {
				it++;
				T path = *it;
				std::cout << word << "------->" << path << std::endl;
				word = "";
			} else {
				word += character;
				it++;
			}
		}
	}
	
	iterator lower_bound(const key_type& testElement) {
		return iterator(); //dont need
	}

	iterator upper_bound(const key_type& testElement) {
		return iterator(); //dont need
	}

	iterator find(const key_type& testElement) {
		E currentChar = testElement[0];
		InternalNode current = root;
		while (currentChar != '\0') {
			current = current.mappyTheLittleMap.find(currentChar)->second;
			current->find(testElement.erase(0, 1));
		}
		return iterator(*current);
	}

	iterator begin() {
		return iterator(*root);
	}

	iterator end() {
		return iterator(nullptr);
	}
};

#endif // TRIE_H_INCLUDED
