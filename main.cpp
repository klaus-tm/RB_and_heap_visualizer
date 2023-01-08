#include <bits/stdc++.h>
#include "RBTree.cpp"
#include "Heap.cpp"
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
    cout<<"Insert keys: ";
    int key;
    while(cin>>key){
        keys.push_back(key);
    }
    cin.clear();
    cin.ignore();
}

int main() {
    while(1){
        int choice;
        system("CLS");
        cout<<"~~~~~~~~~~~~~Proiect sda - RB tree and Heap visualization~~~~~~~~~~~~~\n"
            <<"======================================================================\n"
            <<"1. RB tree visualization;\n"
            <<"2. Heap tree visualization;\n"
            <<"3. Close app;\n"
            <<"======================================================================\n"
            <<"Insert your choice: ";
        cin >> choice;

        if(choice == 1){
            system("CLS");
            RBTree tree;
            list<int> keys;
            cout<<"~~~~~~~~~~~~~RB tree visualization~~~~~~~~~~~~~\n"
                <<"===============================================\n"
                <<"In order to stop inserting try CTRL+Z or insert a letter\n"<<flush;
            getKeys(keys);
            for(auto i = keys.begin(); i != keys.end(); i++)
                tree.insert(*i);
            cout<<"\nThis is your tree:\n";
            tree.disp();
            cout<<"===============================================\n"
                <<"Press again in order to go back to the menu.\n";
            system("PAUSE");
        }

        else if(choice == 2){
            system("CLS");
            Heap tree;
            list<int> keys;
            int minMax;
            cout <<"~~~~~~~~~~~~~Heap tree visualization~~~~~~~~~~~~~\n"
                 <<"=================================================\n"
                 <<"In order to stop inserting try CTRL+Z or insert a letter\n"<<flush;
            getKeys(keys);
            while(minMax != 1 and minMax != 2){
                cout<<"What kind of Heap tree you want to see?\n"
                    <<"1. Min Heap\n"
                    <<"2. Max Heap\n"
                    <<"Insert your choice: ";
                cin >> minMax;
                if(minMax == 1 or minMax == 2)
                    for(auto i = keys.begin(); i != keys.end(); i++)
                        tree.insert(*i, minMax);
                else cout<<"Please insert 1 or 2. Try again.\n";
            }
            cout <<"This is your tree:\n";
            tree.displayHeap();
            cout <<"\n=================================================\n"
                 <<"Press again in order to go back to the menu.\n";
            system("PAUSE");
        }

        else if(choice == 3){
            cout<<"\nClosing the app";
            cooldown(1);
            cout<<".";
            cooldown(1);
            cout<<".";
            cooldown(1);
            cout<<".";
            cooldown(1);
            return 0;
        }

        else{
            cout <<"\nTry a valid input please.\n";
            cooldown(3);
        }
    }
}