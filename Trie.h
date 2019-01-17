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

	Trie(){
		root = new InternalNode();
	};

	~Trie() = default;

	/**
	* Abstract Class Node 
	*/
	class _node {
	public:
		virtual bool insert(key_type, mapped_type , key_type) = 0;
		virtual bool erase(key_type& value) = 0;
		virtual void clear() = 0;

	};

	/**
	* Class Leaf extends abstract Class node.
	* Leaf implements all methods of the Class node.
	* Leaf represents a the last element of a branch containing the Translation of a word
	*/
	class Leaf: public _node {
	public:
		key_type mPath;
		T mMeaning;

		~Leaf()=default;
		Leaf(key_type path, mapped_type meaning) {
			mPath = path;
			mMeaning = meaning;
		}

		bool insert(key_type, mapped_type , key_type) {return false;}
		bool erase(key_type& value) {return false;}
		void clear() {}
	};

	/**
	* Class InternalNode implements Class node.
	* Internal Node reprecents a single Charactar.
	*/
	class InternalNode: public _node {
	public:
		mappy mappyTheLittleMap;
		~InternalNode()=default;
		InternalNode() = default;
		key_type viewTrie = "";
		
		/**
		* Insert will insert a Word into the Tree.
		* This method will create Nodes with charactars until the very end is reach reprecented by the '#' Charactar.
		* At the end a Leaf will be attached.
		*/
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

<<<<<<< HEAD
=======
		/**
		* Erase will erase a word form the tree.
		* It will erase the branch, the leaf and the terminate charactar.
		*
		*/
>>>>>>> 69ab81d68a943cb37da2f498fe92145b0b350242
		bool erase(key_type &value) {
			E curChar = value[0];
			auto mappyIt=mappyTheLittleMap.find(curChar);
			if (curChar != '#') { //Not a leaf
				if (!mappyTheLittleMap.empty() && mappyTheLittleMap.find(curChar) != mappyTheLittleMap.end()) {
					mappyTheLittleMap.erase(curChar);
					mappyIt.operator*().second->erase(value.erase(0, 1));
				}
			} else {
				if (mappyTheLittleMap.erase(curChar) == 1) {
					return true;
				}
			}
			return false;
		}

		/**
		* Clear will clear a branch.
		*   
		*/
		void clear() {
			if (!mappyTheLittleMap.empty()) {
				for (typename mappy::iterator clearIt=mappyTheLittleMap.begin(); clearIt!=mappyTheLittleMap.end(); clearIt++) {
					clearIt -> second -> clear();
					delete clearIt -> second;
				}
				mappyTheLittleMap.clear();
			}
		}

<<<<<<< HEAD
=======
		/**
		* Method to check whether the map is empty or not.
		*/
>>>>>>> 69ab81d68a943cb37da2f498fe92145b0b350242
		bool empty() {
			return mappyTheLittleMap.empty();
		}
	};

	/**
	* Class TrieIterator will represent a Iterator-Class for the Trie.
	*/
	class TrieIterator {
	public:
		TrieIterator()=default;
		std::stack<std::pair<typename mappy::iterator,typename mappy::iterator>> stackyTheLittleStack;
		key_type viewTrie = "";

		/**
		* Constructor for the TrieIterator.
		*/
		TrieIterator(std::stack<std::pair<typename mappy::iterator, typename mappy::iterator>> stacky) {
			stackyTheLittleStack = stacky;
		}

		/**
		* operator* will represent the meaning of a leaf in case it is called.
		*/
		T& operator*() {
			try {
				Leaf* last = static_cast<Leaf*>(stackyTheLittleStack.top().first->second);
				return last->mMeaning;
			} catch (...){
				std::cerr << "* kann nur auf ein Leaf angewendet werden" << std::endl;
			}
		};

		/**
		* Method to return mPath of this leaf.
		*/
		T& show() {
			try {
				Leaf* last = static_cast<Leaf*>(stackyTheLittleStack.top().first->second);
				return last->mPath;
			} catch (...){
				std::cerr << "* kann nur auf ein Leaf angewendet werden" << std::endl;
			}
		};

		/**
		* Is-Not-Equal for to TrieIterator.
		* Will return true in case the iterators are not equal.
		*/
		bool operator !=(const TrieIterator& rhs) {
			return !operator ==(rhs);
		};

		/**
		* Is-Equal for to TrieIterator.
		* Will return true in case the iterators are equal.
		*/
		bool operator ==(const iterator& rhs) const {
			return (stackyTheLittleStack.size() == rhs.stackyTheLittleStack.size() && stackyTheLittleStack.top().second == rhs.stackyTheLittleStack.top().second && stackyTheLittleStack.top().first == rhs.stackyTheLittleStack.top().first);
		}

		bool opCheck=false;

		/**
		* Increment operator.
		*/
		TrieIterator& operator ++() {
			popStack();
			if(opCheck){
				std::cout<< stackyTheLittleStack.top().first->first<<std::endl;
				slideLeft(static_cast<InternalNode*>(stackyTheLittleStack.top().first->second));
			}
			return *this;
		};

		/**
		*   Method to pop the top of the Stack.
		*   Method works recrusive.
		*/
		void popStack() {
			opCheck=false;
			typename mappy::iterator topIter = ++(stackyTheLittleStack.top().first);
			typename mappy::iterator topEnd = (stackyTheLittleStack.top().second);
			if (topIter == topEnd &&stackyTheLittleStack.size()>1 ) {
				stackyTheLittleStack.pop();
				popStack();
			}else if(topIter != topEnd){
				opCheck=true;
			}else{
				opCheck=false;
			}
		}
<<<<<<< HEAD
=======

		/**
		*   Method to pop the top of the Stack and erase.
		*   Method works recrusive.
		*/
		void popStackErase() {
			typename mappy::iterator topIter = ++(stackyTheLittleStack.top().first);
			typename mappy::iterator topEnd = (stackyTheLittleStack.top().second);
			if (topIter == topEnd &&stackyTheLittleStack.size()>1 ) {
				stackyTheLittleStack.pop();
				popStackErase();
			}else if(topIter != topEnd){
				--(stackyTheLittleStack.top().first);
			}
		}

		/**
		*   Method to add whitespaces.
		*   Method works recrusive.
		*/
		std::string addSpace(int stackSize){
			std::string result = "";
			while (stackSize > 0){
				result += " ";
				stackSize--;
			}
			return result;
		};
>>>>>>> 69ab81d68a943cb37da2f498fe92145b0b350242


		/**
		* Method to go straigth down leaf.
		*/		
		void slideLeft(InternalNode* node){
			int leer =0;
			int tmp;
			InternalNode* current = node;
			while(!current->mappyTheLittleMap.empty() && current->mappyTheLittleMap.begin()->first != '#'){
				tmp=leer;
				while(leer!=0){
					leer--;
					std::cout<<"_";
				}
				leer=tmp;
				std::cout<<current->mappyTheLittleMap.begin()->first<<std::endl;
				typename mappy::iterator ki = current->mappyTheLittleMap.begin();
				stackyTheLittleStack.push(std::pair<typename mappy::iterator,typename mappy::iterator> (ki,current->mappyTheLittleMap.end()));
				current = static_cast<InternalNode*>(current->mappyTheLittleMap.begin()->second);
				leer++;
			}

			if (!current->mappyTheLittleMap.empty()){
				if(current->mappyTheLittleMap.begin()->first=='#'){
					tmp=leer;
					while(leer!=0){
						leer--;
						std::cout<<"_";
					}
					leer=tmp;
				}else{
					std::cout << current->mappyTheLittleMap.begin()->first<<std::endl;
				}


				typename mappy::iterator ki = current->mappyTheLittleMap.begin();
				stackyTheLittleStack.push(std::pair<typename mappy::iterator,typename mappy::iterator>(ki,current->mappyTheLittleMap.end()));
				Leaf* lastL = static_cast<Leaf*>(current->mappyTheLittleMap.begin()->second);
				tmp=leer;
				while(leer!=0){
					leer--;
					std::cout<<"_";
				}
				leer=tmp;
				std::cout<< " : " <<lastL->mMeaning<<std::endl;
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


	void showTrie(){
		if(!empty()){
			std::cout <<"\n"<< "---ShowTrie---"<<std::endl;
			iterator showTrieIt=begin();
			while(showTrieIt!=end()){
				++showTrieIt;
			}
			std::cout <<"\n"<< "----------"<<std::endl;
		}else{
			std::cout <<"\n"<< "ein leerer baum wird nicht geprintet"<<std::endl;
		}

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

	/**
	* LowerBound of the trie.
	*/
	iterator lower_bound(const key_type& testElement) {
		iterator lowerBoundIt = begin();
		while(lowerBoundIt != end()){
			Leaf* last = static_cast<Leaf*>(lowerBoundIt.stackyTheLittleStack.top().first->second);
			key_type leafWord = last->mPath;
			if (leafWord.find(testElement) != std::string::npos){
				return lowerBoundIt;
			}
			++lowerBoundIt;
		}
		return end();
	}

	/**
	* UpperBound of the trie.
	*/
	iterator upper_bound(const key_type& testElement) {
		try {
			iterator upperBoundIt = begin();
			TrieIterator ab();
			while(upperBoundIt){
				Leaf* last = static_cast<Leaf*>(upperBoundIt.stackyTheLittleStack.top().first->second);
				key_type leafWord = last->mPath;
				if (leafWord.find(testElement) != std::string::npos){
					ab = upperBoundIt;
				}
				++upperBoundIt;
			}
			return ++ab();
		} catch (...){
			return end();
		}
	}

	/**
	* Method to find a word in the trie.
	*
	*/
	iterator find(key_type& word) {
		iterator findIt = begin();
		if(!empty()){
			while(findIt != end()){
				Leaf* last = static_cast<Leaf*>(findIt.stackyTheLittleStack.top().first->second);
				key_type leafWord = last->mPath;
				key_type wordToCheck = word + '#';

				if (leafWord == wordToCheck){
					return findIt;
				}
				++findIt;
			}
		}

		return end();
	}

	/**
	* Begin-Element for the Trie-Iterator.
	*/
	iterator begin() {
		try {
			iterator beginIt;
			beginIt.slideLeft(root);
			return beginIt;
		} catch(...) {
			return end();
		}
	}

	/**
	* End-Element of the Trie-Iterator.
	*/
	iterator end() {
		std::stack<std::pair<typename mappy::iterator,typename mappy::iterator>> endStack;
		endStack.push(std::pair<typename mappy::iterator,typename mappy::iterator>(root->mappyTheLittleMap.end(),root->mappyTheLittleMap.end()));
		TrieIterator endIt(endStack);
		return endIt;
	}

	/**
	* Erase a word of the trie.
	* will return true in case the word could be erased.
	*/
	bool erase(const key_type& value) {
		key_type tmp = value + "#";
		root->erase(tmp);
	}

};

#endif // TRIE_H_INCLUDED
