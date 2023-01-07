#include <bits/stdc++.h>
#include "RBTree.cpp"
using namespace std;

void cooldown(int seconds){
    clock_t start = clock();
    clock_t period = seconds * CLOCKS_PER_SEC;
    clock_t elapsed;

    do{
        elapsed = clock() - start;
    }while(elapsed < period);
}
void getKeys(list<int>& keys){
    cout<<"Te rog insereaza chei: ";
    int cheie;
    while(cin>>cheie){
        keys.push_back(cheie);
    }
    cin.clear();
    cin.ignore();
}

int main() {
    while(1){
        int choice;
        system("CLS");
        cout<<"~~~~~~~~~~~~~Proiect sda - vizualizator RB tree si Heap~~~~~~~~~~~~~\n"
            <<"====================================================================\n"
            <<"1. Vizualizator RB;\n"
            <<"2. Vizualizator Heap;\n"
            <<"3. Inchide programul;\n"
            <<"====================================================================\n"
            <<"Selecteaza ce vrei sa faci: ";
        cin >> choice;

        if(choice == 1){
            system("CLS");
            RBTree tree;
            list<int> chei;
            cout<<"~~~~~~~~~~~~~Vizualizator RB tree~~~~~~~~~~~~~\n"
                <<"==============================================\n"
                <<"Pentru a te opri din citit incerca CTRL+Z sau introdu o litera\n"<<flush;
            getKeys(chei);
            for(auto i = chei.begin(); i != chei.end(); i++)
                tree.insert(*i);
            cout<<"\nAcesta este arborele tau:\n";
            tree.disp();
            cout<<"==============================================\n"
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

        else{
            cout <<"\nIntrodu un numar valid te rog\n";
            cooldown(3);
        }
    }
}