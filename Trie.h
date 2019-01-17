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

	class _node {
	public:
		virtual bool insert(key_type, mapped_type , key_type) = 0;
		virtual bool erase(key_type& value) = 0;
		virtual void clear() = 0;
	};

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
		bool erase(key_type &value) {
			E curChar = value[0];
			if (curChar != '#') { //Not a leaf
				if (!mappyTheLittleMap.empty() && mappyTheLittleMap.find(curChar) != mappyTheLittleMap.end()) { //key in map
					return mappyTheLittleMap.find(curChar).operator*().second->erase(value.erase(0, 1));
				}
				//Key not in map, return false
			} else {
				if (mappyTheLittleMap.erase(curChar) == 1) { //Erase value and return true if something was erased
					return true;
				}
			}
			return false;
		}

		void clear() {
			if (!mappyTheLittleMap.empty()) {
				for (typename mappy::iterator clearIt=mappyTheLittleMap.begin(); clearIt!=mappyTheLittleMap.end(); clearIt++) {
					clearIt -> second -> clear();
					delete clearIt -> second;
				}
				mappyTheLittleMap.clear();
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

		T& show() {
			try {
				Leaf* last = static_cast<Leaf*>(stackyTheLittleStack.top().first->second);
				return last->mPath;
			} catch (...){
				std::cerr << "* kann nur auf ein Leaf angewendet werden" << std::endl;
			}
		};

		bool operator !=(const TrieIterator& rhs) {
			return !operator ==(rhs);
		};

		bool operator ==(const iterator& rhs) const {
			return (stackyTheLittleStack.size() == rhs.stackyTheLittleStack.size() && stackyTheLittleStack.top().second == rhs.stackyTheLittleStack.top().second && stackyTheLittleStack.top().first == rhs.stackyTheLittleStack.top().first);
		}

		bool opCheck=false;
		TrieIterator& operator ++() {
			popStack();
			if(opCheck){
				std::cout<< stackyTheLittleStack.top().first->first<<std::endl;
				slideLeft(static_cast<InternalNode*>(stackyTheLittleStack.top().first->second));
			}
			return *this;
		};

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

		std::string addSpace(int stackSize){
			std::string result = "";
			while (stackSize > 0){
				result += " ";
				stackSize--;
			}
			return result;
		};

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
			//			std::cout<<current->mappyTheLittleMap.begin()->first<<std::endl;

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

	iterator begin() {
		try {
			iterator beginIt;
			beginIt.slideLeft(root);
			return beginIt;
		} catch(...) {
			return end();
		}
	}

	iterator end() {
		std::stack<std::pair<typename mappy::iterator,typename mappy::iterator>> endStack;
		endStack.push(std::pair<typename mappy::iterator,typename mappy::iterator>(root->mappyTheLittleMap.end(),root->mappyTheLittleMap.end()));
		TrieIterator endIt(endStack);
		return endIt;
	}

	bool erase(const key_type& value) {
		key_type tmp = value + "#";
		root->erase(tmp);
	}

};

#endif // TRIE_H_INCLUDED
