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
    baum.insert(pair<const basic_string<char>,string> ("test#","#test#"));
    baum.insert(pair<const basic_string<char>,string> ("klaus#","#klaus#"));
    baum.insert(pair<const basic_string<char>,string> ("fack#","#fack#"));
    baum.insert(pair<const basic_string<char>,string> ("fuck#","#fuck#"));
    cout << baum.begin().operator *();


}

