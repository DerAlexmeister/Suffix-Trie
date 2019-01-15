/*
 * Trie.h
 *
 *  Created on: 29.11.2018
 *      Author: apfel
 */

#ifndef TRIE_H_
#define TRIE_H_
using namespace std;
#include <map>;
#include <stack>

template<class T, class E = char>
class Trie {

	class Node {
		typedef typename std::map<char, Node*>::iterator MapIterator;
		typedef std::stack<pair<MapIterator, MapIterator>> stackMapIterator;
	public:
		explicit Node() {
		}
		virtual void add(basic_string<char> child, T value) = 0;
		virtual stackMapIterator find(basic_string<char> child,
				stackMapIterator stack) = 0;
		virtual void print(int counter)=0;
		virtual ~Node() {

		}

	};
	class InnererKnoten: public Node {
		typedef typename std::map<char, Node*>::iterator MapIterator;
		typedef std::stack<pair<MapIterator, MapIterator>> stackMapIterator;
	public:

		InnererKnoten() :
				Node() {

		}

		void print(int counter) {
			typename std::map<char, Node*>::iterator itMap;

			for (itMap = map.begin(); itMap != map.end(); ++itMap) {
				if (itMap->first != '\n') {
					for (int i = 0; i < counter; ++i) {
						cout << " ";
					}
					cout << itMap->first << endl;
				}

				(*itMap->second).print(++counter);
				--counter;

			}

		}
		stackMapIterator find(basic_string<char> child,
				stackMapIterator stack) {
			int size = child.size();
			if (size != 0) {

				char firstChar = child.front();
				MapIterator itMap = map.find(firstChar);
				InnererKnoten* note1;
				if (itMap == map.end()) {
					stackMapIterator ende;

					return ende;
				} else {
					note1 = (InnererKnoten*) (itMap->second);

					pair<MapIterator, MapIterator> element(map.find(firstChar),
							map.end());

					stack.push(element);

					stack = (*note1).find(child.substr(1, size - 1), stack);
				}
			}
			return stack;
		}

		void add(basic_string<char> child, T value) {
			int size = child.size();
			if (size == 0) {
				Blatt* blatt = new Blatt();
				map.insert(
						std::pair<char, Node*>('\n',
								static_cast<Node*>(blatt)));
				(*blatt).add(child, value);
			} else {
				char firstChar = child.front();
				MapIterator itMap = map.find(firstChar);
				InnererKnoten* note1;
				if (itMap == map.end()) {
					note1 = new InnererKnoten();
					map.insert(std::pair<char, Node*>(firstChar, note1));
				} else {
					note1 = (InnererKnoten*) (itMap->second);
				}
				//	cout<<"firstChar"<<firstChar<<endl;
				(*note1).add(child.substr(1, size - 1), value);
				//	cout<<"groß"<<stack.size()<<endl;
			}

		}

		std::map<char, Node*> map;

	protected:
	private:

		//markierte Kindzeiger

	};
	class Blatt: public Node {
		typedef typename std::map<char, Node*>::iterator MapIterator;
		typedef std::stack<pair<MapIterator, MapIterator>> stackMapIterator;
	public:
		Blatt() :
				Node() {
			mValue = T();
		}
		void print(int counter) {
			for (int i = 0; i < counter; ++i) {
				cout << " ";
			}
			cout << ":" << mValue << endl;

		}
		stackMapIterator find(basic_string<char> child,
				stackMapIterator stack) {
			return stack;
		}
		void add(basic_string<char> child, T value) {

			mValue = value;

		}
		void setValue(T pValue) {

			mValue = pValue;
		}
		T& getValue() {
			return mValue;
		}
	private:
		T mValue;

	};
	class TrieIterator {
		typedef TrieIterator iterator;
		typedef typename std::map<char, Node*>::iterator MapIterator;

	public:

		TrieIterator(std::stack<pair<MapIterator, MapIterator>> mapStruct) {
			iteratorStack = mapStruct;

			if (iteratorStack.top().first == iteratorStack.top().second) {
				return;
			}
			char ch = iteratorStack.top().first->first;

			while (ch != '\n') {
				ch = runter();
			}
		}

		virtual ~TrieIterator() {
		}

		const T& operator *() {

			Blatt* bl = (Blatt*) iteratorStack.top().first->second;

			return ((*bl).getValue());

		}
		iterator& operator =(const iterator& rhs) {
			iteratorStack = rhs.iteratorStack;

			return *this;
		}
		bool operator !=(const iterator& rhs) const {

			return !(*this == rhs);

		}
		bool operator ==(const iterator& rhs) const {
			return (iteratorStack.size() == rhs.iteratorStack.size()
					&& iteratorStack.top().second
							== rhs.iteratorStack.top().second
					&& iteratorStack.top().first
							== rhs.iteratorStack.top().first);

		}

		iterator& operator ++() {
			weiter();
			return *this;

		}
		iterator operator ++(int) {

			TrieIterator copy(iteratorStack);
			weiter();

			return copy;

		}

	private:
		void weiter() {

			MapIterator topIter = ++(iteratorStack.top().first);
			MapIterator topEnd = (iteratorStack.top().second);
			if (topIter == topEnd) {
				if (iteratorStack.size() == 1) {

					return;

				}
				iteratorStack.pop();

				weiter();

			} else {
				char ch = topIter->first != '\n';

				while (ch != '\n') {
					//test();
					//cout <<"bh" <<ch << endl;
					ch = runter();
				}
			}
		}

		char runter() {

			std::pair<char, Node*> topA = (*iteratorStack.top().first);

			//cout << topA.first << endl;

			InnererKnoten* blatt = (InnererKnoten*) topA.second;

			pair<MapIterator, MapIterator> itStruct((*blatt).map.begin(),
					(*blatt).map.end());

			iteratorStack.push(itStruct);
			topA = (*iteratorStack.top().first);

			return topA.first;

		}

		std::stack<pair<MapIterator, MapIterator>> iteratorStack;
	};
public:
	Trie() {
		InnererKnoten root;
	}

	typedef basic_string<E> key_type; // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	typedef TrieIterator iterator;

	typedef typename std::map<char, Node*>::iterator MapIterator;

	bool empty() const {
		return root.map.empty();
	}
	iterator insert(const value_type& value) {
		key_type child = value.first;
		T val = value.second;
		root.add(child, val);
		return find(child);
	}

	void erase(const key_type& value) {

		stack<pair<MapIterator, MapIterator>> iteratorStack;
		iteratorStack = root.find(value + "\n", iteratorStack);
		eraseIterativ(iteratorStack);

	}
	void clear() {
		// erase all
		root.map.clear();
	}
	iterator lower_bound(const key_type& testElement) {
		// first element >= testElement

		stack<pair<MapIterator, MapIterator>> iteratorStack;
		iteratorStack = root.find(testElement, iteratorStack);
		if (iteratorStack.empty()) {
			return end();
		}
		TrieIterator it(iteratorStack);
		return it;
	}
	iterator upper_bound(const key_type& testElement) {
		// first element > testElement
		stack<pair<MapIterator, MapIterator>> iteratorStack;
		iteratorStack = root.find(testElement, iteratorStack);
		if (iteratorStack.empty()) {
			return end();
		}
		++iteratorStack.top().first;
		TrieIterator it(iteratorStack);
		return it;
	}
	iterator find(const key_type& testElement) { // first element == testElement
		return lower_bound(testElement + '\n');
	}

	iterator begin() {
		std::stack<pair<MapIterator, MapIterator>> iteratorStack;
		iteratorStack.push(
				pair<MapIterator, MapIterator>(root.map.begin(),
						root.map.end()));
		TrieIterator it(iteratorStack);
		return it;
	}

	iterator end() {
		std::stack<pair<MapIterator, MapIterator>> iteratorStack;
		iteratorStack.push(
				pair<MapIterator, MapIterator>(root.map.end(), root.map.end()));
		TrieIterator it(iteratorStack);
		return it;
	}
	void print() {
		root.print(0);
	}
private:
	void eraseIterativ(stack<pair<MapIterator, MapIterator>> stack) {

		char buchstabe = stack.top().first->first;
		stack.pop();
		InnererKnoten* blatter;
		if (stack.size() == 0) {
			blatter = &root;
		} else {
			blatter = (InnererKnoten*) stack.top().first->second;
		}

		blatter->map.erase(buchstabe);

		if (!stack.empty() && blatter->map.begin() == blatter->map.end()) {

			eraseIterativ(stack);
		}

	}
	InnererKnoten root;
};

#endif /* TRIE_H_ */
