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
	Trie(){
		root = new InternalNode();
	};

	~Trie() = default;

	class _node {
	public:
		T mPath;
		mappy mappyTheLittleMap;
		virtual bool insert(key_type, mapped_type , key_type) = 0;
		virtual bool erase(const key_type& value) = 0;
		virtual void clear() = 0;
	};

	class Leaf: public _node {
	public:
		~Leaf()=default;
		mappy mappyTheLittleMap;
		key_type mPath;
		T mMeaning;
		Leaf(key_type path, mapped_type meaning) {
			mPath = path;
			mMeaning = meaning;
		}

		bool insert(key_type, mapped_type , key_type) {
			return false;
		}

		bool erase(const key_type& value) {
			return false;
		}

		void clear() {}
	};

	class InternalNode: public _node {
	public:
		mappy mappyTheLittleMap;
		~InternalNode()=default;
		InternalNode() = default;

		bool insert(key_type key, mapped_type value, key_type leafWord) {
			using namespace std;

			try {
				using namespace std;
				E currentChar = key[0];
				InternalNode* next;

				using namespace std;
				if (currentChar == '#') {
					if (!mappyTheLittleMap.count(currentChar)) {
						Leaf* last = new Leaf(leafWord, value);
						mappyTheLittleMap.insert(pair<E,_node*>(currentChar, static_cast<_node*>(last)));
						return true;
					}
				} else {
					if (mappyTheLittleMap.find(currentChar) == mappyTheLittleMap.end()) {
						next = new InternalNode();
						mappyTheLittleMap.insert(pair<E,_node*>(currentChar, static_cast<_node*>(next)));
					} else {
						next = static_cast<InternalNode*>(mappyTheLittleMap.find(currentChar)->second);
					}

					next->insert(key.erase(0, 1), value, leafWord);
				}
			} catch (...) {
				using namespace std;
				cout << "An error occurred" << endl;
				return false;
			}
		}

		void clear() {
			if (!mappyTheLittleMap.empty()) {
				for (typename mappy::iterator it=mappyTheLittleMap.begin(); it!=mappyTheLittleMap.end(); it++) {
					it -> second -> clear();
					delete it -> second;
				}
				mappyTheLittleMap.clear();
			}
		}

		bool erase(const key_type& word) {
			using namespace std;
			string str_key = string(word) + '#';
			char deleteChar;
			InternalNode* current = this;
			InternalNode* deleteNode = current;
			if (!(current->mappyTheLittleMap.empty())) {
				for (char& currentChar : str_key) {
					if (current->mappyTheLittleMap.find(currentChar) != current->mappyTheLittleMap.end()) {
                        if (current->mappyTheLittleMap.size() > 1) {
                            deleteNode = current;
                            deleteChar = currentChar;
                        } else {
                            current = static_cast<InternalNode *>(current->mappyTheLittleMap.find(currentChar)->second);
                        }
                    }
                }
                deleteNode->mappyTheLittleMap.find(deleteChar)->second->clear();
                deleteNode->mappyTheLittleMap.erase(deleteNode->mappyTheLittleMap.find(deleteChar));
			} else {
			    return false;
			}
		}


		bool empty() {
			return mappyTheLittleMap.empty();
		}
	};

	class TrieIterator {
	public:
		TrieIterator()=default;
		std::stack<std::pair<typename mappy::iterator,typename mappy::iterator>> stackyTheLittleStack;
		TrieIterator(std::stack<std::pair<typename mappy::iterator, typename mappy::iterator>> stacky) {
			stackyTheLittleStack = stacky;
		}


		key_type viewTrie = "";

		T& operator*() {
			try {
				Leaf* last = static_cast<Leaf*>(stackyTheLittleStack.top().first->second);
				return last->mMeaning;
			} catch (...){
				std::cerr << "* kann nur auf ein Leaf angewendet werden" << std::endl;
			}
		};

		bool operator !=(const TrieIterator& rhs) {
			return !operator ==(rhs);
		};

		bool operator ==(const TrieIterator& rhs) {
			return this->stackyTheLittleStack == rhs.stackyTheLittleStack;
		};

		TrieIterator& operator ++() {
					popStack();
					viewTrie += '\n' + addSpace(stackyTheLittleStack.size()) += stackyTheLittleStack.top().first->first;
					slideLeft(static_cast<InternalNode*>(stackyTheLittleStack.top().first->second));
					return *this;
				};

				void popStack() {
					typename mappy::iterator topIter = ++(stackyTheLittleStack.top().first);
					typename mappy::iterator topEnd = (stackyTheLittleStack.top().second);
					if (topIter == topEnd) {
						stackyTheLittleStack.pop();
						popStack();
					}
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
				stackyTheLittleStack.push(std::pair<typename mappy::iterator,typename mappy::iterator> (ki,current->mappyTheLittleMap.end()));
				current = static_cast<InternalNode*>(current->mappyTheLittleMap.begin()->second);
			}
			if (!current->mappyTheLittleMap.empty()){
				viewTrie + current->mappyTheLittleMap.begin()->first;
				typename mappy::iterator ki = current->mappyTheLittleMap.begin();
				stackyTheLittleStack.push(std::pair<typename mappy::iterator,typename mappy::iterator>(ki,current->mappyTheLittleMap.end()));
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
		key_type word = value.first + '#';
        key_type leafWord = value.first + '#';
        key_type findLeafWithWord = value.first;
		mapped_type meaning = value.second;
		root->insert(word,meaning,leafWord);
		return find(findLeafWithWord);
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
			root->clear();
		} catch(...) {
			std::cout << "Root has no children yet! \n";
		}
	}


	void showTrie() {
		iterator cd = begin();
		iterator ed = cd;
 		while(cd != end() && ++ed != end())  {
			++cd;
			ed=cd;
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

	iterator find(key_type& word) {
		iterator it = begin();

		while(it != end()){
            Leaf* last = static_cast<Leaf*>(it.stackyTheLittleStack.top().first->second);
            key_type leafWord = last->mPath;
            key_type wordToCheck = word + '#';
            std::cout << leafWord << " " << std::endl;
			if (leafWord == wordToCheck){
				return it;
			}
			++it;
		}
	}

	Leaf* getLeaf(TrieIterator& it){
		Leaf* result = static_cast<Leaf*>(it.stackyTheLittleStack.top().first->second);
		return result;
	}

	iterator begin() {
		try {
			it.slideLeft(root);
			return it;
		} catch(...) {
			return end();
		}
	}

	iterator end() {
		std::stack<std::pair<typename mappy::iterator,typename mappy::iterator>> st;
		st.push(std::pair<typename mappy::iterator,typename mappy::iterator>(root->mappyTheLittleMap.end(),root->mappyTheLittleMap.end()));
		TrieIterator i_t(st);
		return i_t;
	}
};

#endif // TRIE_H_INCLUDED
