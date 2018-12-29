//============================================================================
// Name        : main.cpp
// Author      : Alexander M. Westphal / Paul Schröder
// Version     : Alpha v0.1
// Copyright   : Alexander M. Westphal / Paul Schröder
// Description : Main-Program
//============================================================================

#include <iostream>
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
                insertObject();
                break;
            case 2:
                deleteObject();
                break;
            case 3:
                eraseAll();
                break;
            case 4:
                show();
                break;
            case 5:
                std::cout << std::boolalpha << "It the \'Trie\' empty? Answer: " <<  baum.empty() << std::noboolalpha << std::endl;
                break;
            case 6:
                eingabe = 0;
                break;
            default:
                std::cout << "wrong input, please enter another number" << std::endl;
                break;
        }
    }
    return 0;
}


int input() {
    using namespace std;
    int eingabe;
    cout << "Menu:" << endl;
    cout << "(1) Insert word " << endl;
    cout << "(2) Delete word " << endl;
    cout << "(3) Delete all " << endl;
    cout << "(4) Print tree " << endl;
    cout << "(5) Check whether the \'Trie\' is empty or not" << endl;
    cout << "(6) Done" << endl;
    cout << "Enter a number: " << endl;
    cin >> eingabe;
    return eingabe;
}

void insertObject() {

}

void deleteObject() {

}

void eraseAll() {

}

void show(){

}
