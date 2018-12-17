//============================================================================
// Name        : main.cpp
// Author      : Alexander M. Westphal / Paul Schröder
// Version     : Alpha v0.1
// Copyright   : Alexander M. Westphal / Paul Schröder
// Description : ..., Ansi-style
//============================================================================

#include <iostream>
#include "_node.h"
#include "Trie.h"

Trie<_node> test;

int input();
void insertObject();
void deleteObject();
void eraseAll();

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
                void show();
                break;
            case 5:
                eingabe = 0;
                break;
            default:
                std::cout << "falsche eingabe";
                break;
        }
    }
    return 0;
}


int input() {
    using namespace std;
    int eingabe;
    cout << "Menue:" << endl;
    cout << "(1) Wort einfuegen " << endl;
    cout << "(2) Wort loeschen" << endl;
    cout << "(3) Alles loeschen" << endl;
    cout << "(4) Baum ausgeben" << endl;
    cout << "(5) Fertig" << endl;
    cout << "Eingabe: ";
    cin >> eingabe;
    return eingabe;
}

void insertObject() {
    test.insert(value);
}

void deleteObject() {
test.erase(value);
}

void eraseAll() {
    test.clear();
}

void show(){

}