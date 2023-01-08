#include <bits/stdc++.h>
using namespace std;

struct node{
    int key;
    node *left;
    node *right;
    node *parent;
    char color;
};
class RBTree{
private:
    node *root;
public:
    RBTree(){
        root = NULL;
    }

    void insert(int k){
        node *temp = root, *copy = NULL;
        node *t = new node;
        t->key = k;
        t->left = NULL;
        t->right = NULL;
        t->color = 'r';
        if(root == NULL)
        {
            root = t;
            t->parent = NULL;
        }
        else
        {
            while(temp != NULL)
            {
                copy = temp;
                if(temp->key < t->key)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            t->parent = copy;
            if(copy->key < t->key)
                copy->right = t;
            else
                copy->left = t;
        }
        insertFix(t);
    }

    void insertFix(node *n){
        node *uncle;
        if(root == n)
        {
            n->color = 'b';
            return;
        }
        while(n->parent!=NULL and n->parent->color == 'r')
        {
            node *grandparent = n->parent->parent;
            if(grandparent->left == n->parent)
            {
                if(grandparent->right != NULL)
                {
                    uncle = grandparent->right;
                    if(uncle->color == 'r')
                    {
                        n->parent->color = 'b';
                        uncle->color='b';
                        grandparent->color='r';
                        n = grandparent;
                    }
                }
                else
                {
                    if(n->parent->right == n)
                    {
                        n = n->parent;
                        leftRotate(n);
                    }
                    n->parent->color = 'b';
                    grandparent->color = 'r';
                    rightRotate(grandparent);
                }
            }
            else
            {
                if(grandparent->left != NULL)
                {
                    uncle = grandparent->left;
                    if(uncle->color == 'r')
                    {
                        n->parent->color = 'b';
                        uncle->color = 'b';
                        grandparent->color = 'r';
                        n = grandparent;
                    }
                }
                else
                {
                    if(n->parent->left == n)
                    {
                        n = n->parent;
                        rightRotate(n);
                    }
                    n->parent->color = 'b';
                    grandparent->color = 'r';
                    leftRotate(grandparent);
                }
            }
            root->color = 'b';
        }
    }

    void leftRotate(node *n) {
        if(n->right == NULL)
            return;
        else{
            node *y = n->right;
            if(y->left != NULL){
                n->right = y->left;
                y->left->parent = n;
            }
            else
                n->right = NULL;
            if(n->parent != NULL)
                y->parent = n->parent;
            if(n->parent == NULL)
                root = y;
            else
            {
                if(n == n->parent->left)
                    n->parent->left = y;
                else
                    n->parent->right = y;
            }
            y->left = n;
            n->parent = y;
        }
    }


    void rightRotate(node *n) {
        if(n->left == NULL)
            return;
        else
        {
            node *y = n->left;
            if(y->right != NULL)
            {
                n->left = y->right;
                y->right->parent = n;
            }
            else
                n->left = NULL;
            if(n->parent != NULL)
                y->parent = n->parent;
            if(n->parent == NULL)
                root = y;
            else
            {
                if(n == n->parent->left)
                    n->parent->left = y;
                else
                    n->parent->right = y;
            }
            y->right = n;
            n->parent = y;
        }
    }

    void disp(){
        display(root);
    }
    void display(node *p){
        if(root == NULL){
            cout << "\nEmpty Tree.";
            return;
        }
        if(p != NULL){
            cout << "\n\t NODE: "
                 << "\n Key: " << p->key
                 << "\n Colour: ";
            if(p->color == 'b')
                cout << "Black";
            else
                cout << "Red";
            if(p->parent != NULL)
                cout << "\n Parent: " << p->parent->key;
            else
                cout << "\n There is no parent of the node.  ";
            if(p->right != NULL)
                cout << "\n Right Child: " << p->right->key;
            else
                cout << "\n There is no right child of the node.  ";
            if(p->left != NULL)
                cout << "\n Left Child: "<< p->left->key;
            else
                cout << "\n There is no left child of the node.  \n";
            if(p->left){
                cout << "\n\nLeft:\n";
                display(p->left);
            }
            /*else
             cout<<"\nNo Left Child.\n";*/
            if(p->right){
                cout << "\n\nRight:\n";
                display(p->right);
            }
            /*else
             cout<<"\nNo Right Child.\n"*/
        }
    }
};