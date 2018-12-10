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


int input();

int main() {
    int eingabe = -1;
    while (eingabe != 0){
        eingabe = input();
        switch(eingabe){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
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
    cout << "(1) " << endl;
    cout << "(2) " << endl;
    cout << "(3) " << endl;
    cout << "(4) " << endl;
    cout << "(5) Fertig" << endl;
    cout << "Eingabe: ";
    cin >> eingabe;
    return eingabe;
}