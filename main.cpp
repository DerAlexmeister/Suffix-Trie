//============================================================================
// Name        : main.cpp
// Author      : Alexander M. Westphal / Paul Schroeder / Klaus Riedl
// Version     : Alpha v0.1
// Copyright   :
// Description : Main-Program
//============================================================================

#include <iostream>
#include <typeinfo>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <stdlib.h>
#include "Trie.h"


Trie<std::string> baum;

/**
*  Main Method to work with the Trie.
*/
int main() {
using namespace std;
    basic_string<char> car = "klaus";
    baum.insert(pair<const basic_string<char>, string>("klau", "M_klau"));
    baum.insert(pair<const basic_string<char>, string>("klaus", "M_klaus"));
    baum.insert(pair<const basic_string<char>, string>("mario", "M_mario"));
    //baum.erase(car);
baum.erase(car);
    baum.showTrie();
//baum.erase(car);
//cout <<baum.root->mappyTheLittleMap.begin();
//    baum.showTrie();
//    baum.begin();
//cout <<"Wort: "<<baum.begin().show()<<endl;
//cout <<"�bersetzung: " <<baum.begin().operator *()<<endl;
//cout <<"Wort: "<<baum.begin().operator ++().show()<<endl;
//cout <<"�bersetzung: " <<baum.begin().operator ++().operator *()<<endl;
//cout <<"Wort: "<<baum.begin().operator ++().operator ++().show()<<endl;
//cout <<"�bersetzung: " <<baum.begin().operator ++().operator ++().operator *()<<endl;
}