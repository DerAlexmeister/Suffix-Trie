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
    baum.insert(pair<const basic_string<char>,string> ("afg","Meaning:a"));
    baum.insert(pair<const basic_string<char>,string> ("b","Meaning:b"));
    baum.insert(pair<const basic_string<char>,string> ("c","Meaning:c"));
    baum.insert(pair<const basic_string<char>,string> ("d","Meaning:d"));

    //cout << baum.root->mappyTheLittleMap.size()<< endl;

    //basic_string<char> klaus = "afg";
    //std::cout << baum.find(klaus).operator*() << std::endl;;

    //for (auto it=baum.root->mappyTheLittleMap.begin(); it!=baum.root->mappyTheLittleMap.end(); ++it){
    //    std::cout << it->first << std::endl;
    //}


    //baum.clear();
    //cout << std::boolalpha << "Find a word " <<  baum.empty() << std::noboolalpha << std::endl;
    //cout << "a"<< baum.begin().operator *() << endl;
    //cout << "b"<< baum.begin().operator ++().operator *()<< endl;
    //cout << "c"<< baum.begin().operator ++().operator ++().operator *()<< endl;
    //cout << "d"<< baum.begin().operator ++().operator ++().operator ++().operator *()<< endl;

     baum.showTrie();
}

