//============================================================================
// Name        : main.cpp
// Author      : Alexander M. Westphal / Paul Schroeder / Klaus Riedl
// Version     : Alpha v0.1
// Copyright   :
// Description : Main-Program
//============================================================================

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include "Trie.h"
#include <stdlib.h>
#include <utility>      // std::pair, std::make_pair
using namespace std;
Trie<string> baum;

/**
*  Main Method to work with the Trie.
*/
int main() {
baum.empty();
baum.insert(pair<basic_string<char>,string> ("hallo","test"));
baum.insert(pair<basic_string<char>,string> ("lha","tesscsdcscdt"));
baum.insert(pair<basic_string<char>,string> ("ao","tedcsdcsdcdst"));
cout << baum.root->mappyTheLittleMap.size() << endl;

}
