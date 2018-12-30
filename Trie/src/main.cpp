//============================================================================
// Name        : main.cpp
// Author      : Alexander M. Westphal / Paul Schröder
// Version     : Alpha v0.1
// Copyright   : Alexander M. Westphal / Paul Schröder
// Description : Main-Program
//============================================================================

#include <iostream>
#include <thread>
#include <chrono>
#include "trie.h"

Trie<int,char> baum;

int input();
void insertObject();
void deleteObject();
void eraseAll();
void show();

int main() {
    int eingabe = -1;
    while (eingabe != 0){
        eingabe = input();
        switch(eingabe){
            case 1:
                using namespace std;
                cout << endl << endl;
                break;
            case 2:
                using namespace std;
                cout << endl << endl;
                break;
            case 3:
                baum.clear();
                using namespace std;
                cout << "You just cleared the \'Trie\'" << endl << endl;
                break;
            case 4:
                baum.showTrie();
                using namespace std;
                cout << "This is your \'Trie\'. Have fun!" << endl << endl;
                break;
            case 5:
                std::cout << std::boolalpha << "It the \'Trie\' empty? Answer: " <<  baum.empty() << std::noboolalpha << std::endl;
                break;
            case 6:
                using namespace std;
                cout << "Good by and see you later ...." << endl;
                this_thread::sleep_for (chrono::seconds(3));
                return 0;
            default:
                using namespace std;
                cout << "Wrong input, please enter another number between 1. - 6." << endl;
                cout << endl << endl;
                break;
        }
    }
    return 0;
}


int input() {
    using namespace std;
    int eingabe;
    cout << "================================= Menu ====================================" << endl;
    cout << "(1) Insert a word " << endl;
    cout << "(2) Delete a word " << endl;
    cout << "(3) Delete the hole \'Trie\' " << endl;
    cout << "(4) Print the hole \'Trie\' " << endl;
    cout << "(5) Check whether the \'Trie\' is empty or not" << endl;
    cout << "(6) Go home and do something else ...." << endl;
    cout << "===========================================================================" << endl;
    cout << "Enter a number: ";
    cin >> eingabe;
    return eingabe;
}

