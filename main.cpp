#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "RbTree.h"
using namespace std;

void cooldown(int seconds){
    clock_t start = clock();
    clock_t period = seconds * CLOCKS_PER_SEC;
    clock_t elapsed;

    do{
        elapsed = clock() - start;
    }while(elapsed < period);
}

int main() {
    RBTree* RB = new RBTree();
    while(1){
        int choice;
        system("CLS");
        cout <<"~~~~~~~~~~~~~Proiect sda - vizualizator RB tree si Heap~~~~~~~~~~~~~\n"
             <<"====================================================================\n"
             <<"1. Vizualizator RB;\n"
             <<"2. Vizualizator Heap;\n"
             <<"3. Inchide programul;\n"
             <<"====================================================================\n"
             <<"Selecteaza ce vrei sa faci: ";
        cin >> choice;

        if(choice == 1){
            system("CLS");
            cout <<"~~~~~~~~~~~~~Vizualizator RB tree~~~~~~~~~~~~~\n"
                 <<"==============================================\n"
                 <<"Te rog insereaza noduri:\n";
            cout <<"Acesta este arborele tau:\n";
            cout <<"==============================================\n"
                 <<"Mai apasa o data ca sa te intorci la meniu.\n";
            system("PAUSE");
        }

        else if(choice == 2){
            system("CLS");
            cout <<"~~~~~~~~~~~~~Vizualizator Heap tree~~~~~~~~~~~~~\n"
                 <<"==============================================\n"
                 <<"Te rog insereaza noduri:\n";
            cout <<"Acesta este arborele tau:\n";
            cout <<"==============================================\n"
                 <<"Mai apasa o data ca sa te intrci la meniu.\n";
            system("PAUSE");
        }

        else if(choice == 3){
            cout <<"\nSe inchide aplicatia...\n";
            cooldown(3);
            return 0;
        }

        else if(choice < 1 or choice > 3){
            cout <<"\nIntrodu un numar valid te rog\n";
            system("PAUSE");
        }
    }
}