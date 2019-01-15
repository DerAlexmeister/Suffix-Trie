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

	InternalNode* root;
	TrieIterator it;
    TrieIterator ab;
	Trie(){
		root = new InternalNode("");
	};

	class _node {
	public:
		T mPath;
		mappy mappyTheLittleMap;
		virtual bool insert(key_type, T) = 0;
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

		bool insert(key_type, T) {
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
		InternalNode() = default;
		bool insert(key_type key, T value) {
			try {
				using namespace std;
				E currentChar = value[0];
				InternalNode* next;
				if (!currentChar =='#') {
					if (mappyTheLittleMap.empty() || mappyTheLittleMap.find(currentChar) == mappyTheLittleMap.end()) {
						next = new InternalNode(mPath += currentChar);
						mappyTheLittleMap.insert(pair<E,_node*>(currentChar, static_cast<_node*>(next)));
					} else {
						next = static_cast<InternalNode*>(mappyTheLittleMap.find(currentChar)->second);
					}
				} else if (!mappyTheLittleMap.count(currentChar)) {
					Leaf *last = new Leaf(key, mPath += currentChar);
					mappyTheLittleMap.insert(pair<E,_node*>(currentChar, static_cast<_node*>(last)));
					return true;
				}
				next->insert(key, value.erase(0, 1));
				return true;
			} catch (...) {
				using namespace std;
				cout << "An error occurred" << endl;
				return false;
			}
		}

		void clearKlausi() {
			if (!mappyTheLittleMap.empty()) {
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
			InternalNode* current = this;
			InternalNode* deleteNode = current;
			if (!(current->mappyTheLittleMap.empty())) {
				for (char& currentChar : str_key) {
					if (current->mappyTheLittleMap.find(currentChar) != current->mappyTheLittleMap.end()) {
						if (current->mappyTheLittleMap.size() == 1 && newDelete) {
							deleteNode = current;
							newDelete = false;
						} else if (current->mappyTheLittleMap.size() > 1) {
							newDelete = true;
						}
					} else {
						return false;
					}
					current = static_cast<InternalNode*>(current->mappyTheLittleMap.find(currentChar)->second);
				}
				deleteNode->clear();
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
		std::stack<typename mappy::iterator> stackyTheLittleStack;
	public:
		TrieIterator()=default;
		T viewTrie = "";

		T& operator*() {
            Leaf* last = static_cast<Leaf*>(stackyTheLittleStack.top()->second);
            return last->mMeaning;
		};

		bool operator !=(const TrieIterator& rhs) {
			return !operator ==(rhs);
		};

		bool operator ==(const TrieIterator& rhs) {
            return this->stackyTheLittleStack == rhs.stackyTheLittleStack;
		};

		TrieIterator& operator ++() {
		    typename mappy::iterator ende = getEnd(*this);
            while(stackyTheLittleStack.top()++ == ende){
                stackyTheLittleStack.pop();
                ende = getEnd(*this);
            }
            viewTrie + '\n' + addSpace(stackyTheLittleStack.size()-1) + stackyTheLittleStack.top()++->first;
            slideLeft(static_cast<InternalNode*>(stackyTheLittleStack.top()++->second));
            return *this;
        };

        typename mappy::iterator getEnd(TrieIterator& copy){
            typename mappy::iterator l = copy.stackyTheLittleStack.top();
            copy.stackyTheLittleStack.pop();
            typename mappy::iterator result = static_cast<InternalNode*>(copy.stackyTheLittleStack.top()->second)->mappyTheLittleMap.end();
            copy.stackyTheLittleStack.push(l);
            return result;
        }

        std::string addSpace(int stackSize){
            std::string result = "";
            while (stackSize > 0){
                result += " ";
                stackSize--;
            }
            return result;
        };

        void slideLeft(InternalNode* node){
            InternalNode* current = node;
            while(!current->mappyTheLittleMap.empty() && current->mappyTheLittleMap.begin()->first != '#'){
                viewTrie + current->mappyTheLittleMap.begin()->first;
                typename mappy::iterator ki = current->mappyTheLittleMap.begin();
                stackyTheLittleStack.push(ki);
                current = static_cast<InternalNode*>(current->mappyTheLittleMap.begin()->second);
            }
            if (!current->mappyTheLittleMap.empty()){
                viewTrie + current->mappyTheLittleMap.begin()->first;
                typename mappy::iterator ki = current->mappyTheLittleMap.begin();
                stackyTheLittleStack.push(ki);
                Leaf* lastL = static_cast<Leaf*>(current->mappyTheLittleMap.begin()->second);
                viewTrie + " : " + lastL->mMeaning;
            }
        }
	};


	/**
	 * Method to return whether the Map isEmpty or not
	 */
	bool empty() {
		return root->empty();
	}

	/**
	 *   Insert a single InternalNode or Leaf.
	 */
	iterator insert(const value_type& value) {
		key_type a = value.first;
		T b = value.second + "#";
		root->insert(a,b);
		return find(a);
	}

	/**
	 *   Delete a single InternalNode or a Leaf.
	 */
	void erase(const key_type& value) {
		root->erase(value);
	}



	/**
	 * Method to clear the Tree.
	 * Except for the root.
	 */
	void clear() {
		try {
			root->clearKlausi();
		} catch(...) {
			std::cout << "Root has no children yet! \n";
		}
	}

	/**
	 *  fehlt noch
	 *
	 */
	void showTrie() {
		iterator cd = begin();
		while(cd != end())  {
		    ++cd;
		}
		std::cout << cd.viewTrie << std::endl;
        cd.viewTrie = "";
	}

	iterator lower_bound(const key_type& testElement) {
		return iterator(); //dont need
	}

	iterator upper_bound(const key_type& testElement) {
		return iterator(); //dont need
	}

	iterator find(key_type& testElement) {
		iterator it = begin();
		while(it != end()){
		    if (it.operator*() == testElement){
		        return it;
		    }
		    ++it;
		}
	}

	iterator begin() {
		it.slideLeft(root);
        return it;
    }

	iterator end() {
        return ab;
	}
};

#endif // TRIE_H_INCLUDED
