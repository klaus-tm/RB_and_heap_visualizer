#ifndef RBNODE_H_
#define RBNODE_H_

#include <string>
#include <iostream>
#include <sstream>

using namespace std;


struct RBNode
{
    int key;       // key
    RBNode *parent;     // pointer to parent
    RBNode *left;  // pointer to left child
    RBNode *right; // pointer to right child
    enum color { RED, BLACK };
    color col;

    static RBNode* Nil; // sentinel leaf node

    RBNode(int k, RBNode *l = Nil, RBNode *r = Nil, RBNode *parent = Nil, color c = RBNode::BLACK) :
            key(k), parent(parent), left(l), right(r), col(c) { }

    string toString()
    {
        ostringstream os;
        os << key << ((col == RBNode::RED) ? ":r" : ":b");
        return os.str();
    }

    ~RBNode()
    {
        if (this != Nil)
        {
            if(left != Nil)
                delete left;
            if(right != Nil)
                delete right;
        }
    }

};

RBNode* RBNode::Nil = new RBNode(0);

struct RBTree
{
    RBNode* root;

    void LeftRotate(RBNode* x)
    {
        // Set y
        RBNode* y = x->right;
        // Turn y's left subtree into x's right subtree
        x->right = y->left;
        if (y->left != RBNode::Nil)
            y->left->parent = x;
        // link x's parent to y
        y->parent = x->parent;
        if (x->parent == RBNode::Nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        // Put x on y's left
        y->left = x;
        x->parent = y;
    }

    /**
     * RightRotate(y) also assumes that y is the right child of
     * an RBNode x
     */

    void RightRotate(RBNode* y)
    {
        // Set x
        RBNode* x = y->left;
        // Turn x's right subtree into y's left subtree
        y->left = x->right;
        if (x->right != RBNode::Nil)
            x->right->parent = y;
        // link y's parent to x
        x->parent = y->parent;
        if (y->parent == RBNode::Nil)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        // Put y on x's right
        x->right = y;
        y->parent = x;
    }

    RBTree()
    {
        root = RBNode::Nil;
    }
    ~RBTree()
    {
        delete root;
    }

    RBNode* createNode(int key)
    {
        return new RBNode(key);
    }

    bool isNil(RBNode* n)
    {
        return (n == RBNode::Nil);
    }

    RBNode* search(RBNode* w, int key)
    {
        if (isNil(w) || w->key == key)
            return w;
        return search( (key < w->key) ? w->left : w->right, key);
    }

    /**
     * maximum(w) returns the node with maximum key in the
     * RB-tree with root node w
     */
    RBNode* maximum(RBNode* w)
    {
        RBNode* x = w;
        while (!isNil(x->right))
            x = x->right;
        return x;
    }

    /**
     * minimum(w) returns the node with minimum key in the
     * RB-tree with root node w
     */
    RBNode* minimum(RBNode* w)
    {
        RBNode* x = w;
        while (!isNil(x->left))
            x = x->left;
        return x;
    }

    /**
     * successor(w) returns the successor of node w in the
     * RB-tree to which node w belongs
     */
    RBNode* successor(RBNode* w)
    {
        if(isNil(w)) return w;
        RBNode* x = w;
        if (!isNil(x->right))
            return minimum(x->right);
        RBNode* y = x->parent;
        while (!isNil(y) && x == y->right)
        {
            x = y;
            y = x->parent;
        }
        return y;
    }

    RBNode* predecessor(RBNode* w)
    {
        if(isNil(w)) return w;
        RBNode* x = w;
        if (!isNil(x->left))
            return maximum(x->left);
        RBNode* y = x->parent;
        while (!isNil(y) && x == y->left)
        {
            x = y;
            y = x->parent;
        }
        return y;
    }


    /**
     * RBInsert(z) inserts node z in this RB-tree
     */
    void RBInsert(RBNode* z)
    {
        // insert like in a binary search tree
        RBNode *y = RBNode::Nil;
        RBNode *x = root;
        while (!isNil(x))
        {
            y = x;
            x = (z->key < x->key) ? x->left : x->right;
        }
        z->parent = y;
        if (isNil(y))
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        z->left = z->right = RBNode::Nil;
        z->col = RBNode::RED;
        RBInsertFixup(z);
    }

    RBNode* del(RBNode* z)
    {
        RBNode *y = (isNil(z->left) || isNil(z->right)) ? z : successor(z);
        RBNode *x = !isNil(y->left) ? y->left : y->right;
        x->parent = y->parent;
        if(isNil(y->parent))
        {
            root = x;
        }
        else
        {
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        }
        if (y != z)
        {
            z->key = y->key;
            // copy y's satellite data into z
        }
        if (y->col == RBNode::BLACK)
            RBDeleteFixup(x);
        return y;
    }

    void RBDeleteFixup(RBNode* x)
    {
        RBNode* w;
        while ((x != root) && (x->col == RBNode::BLACK))
        {
            if (x == x->parent->left)
            {
                w = x->parent->right;
                if(w->col == RBNode::RED)
                {
                    w->col = RBNode::BLACK;
                    x->parent->col = RBNode::RED;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }
                if((w->left->col == RBNode::BLACK) && (w->right->col == RBNode::BLACK))
                {
                    w->col = RBNode::RED;
                    x = x->parent;
                }
                else
                {
                    if(w->right->col == RBNode::BLACK)
                    {
                        w->left->col = RBNode::BLACK;
                        w->col = RBNode::RED;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    w->col = x->parent->col;
                    x->parent->col = RBNode::BLACK;
                    w->right->col = RBNode::BLACK;
                    LeftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                // same as 'then' clause with 'right' and 'left' exchanged
                w = x->parent->left;
                if(w->col == RBNode::RED)
                {
                    w->col = RBNode::BLACK;
                    x->parent->col = RBNode::RED;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }
                if((w->left->col == RBNode::BLACK) && (w->right->col == RBNode::BLACK))
                {
                    w->col = RBNode::RED;
                    x = x->parent;
                }
                else
                {
                    if(w->left->col == RBNode::BLACK)
                    {
                        w->right->col = RBNode::BLACK;
                        w->col = RBNode::RED;
                        LeftRotate(w);
                        w = x->parent->left;
                    }
                    w->col = x->parent->col;
                    x->parent->col = RBNode::BLACK;
                    w->left->col = RBNode::BLACK;
                    RightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->col = RBNode::BLACK;
    }

    void RBInsertFixup(RBNode* z)
    {
        while(z->parent->col == RBNode::RED)
            if (z->parent == z->parent->parent->left)
            {
                RBNode* y = z->parent->parent->right;
                if (y->col == RBNode::RED)
                {
                    z->parent->col = RBNode::BLACK;
                    y->col = RBNode::BLACK;
                    z->parent->parent->col = RBNode::RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z==z->parent->right)
                    {
                        z = z->parent;
                        LeftRotate(z);
                    }
                    z->parent->col = RBNode::BLACK;
                    z->parent->parent->col = RBNode::RED;
                    RightRotate(z->parent->parent);
                }
            }
            else
            {
                /* same as 'then' clause,
                 * with 'left' and 'right' exchanged */
                RBNode* y = z->parent->parent->left;
                if (y->col == RBNode::RED)
                {
                    z->parent->col = RBNode::BLACK;
                    y->col = RBNode::BLACK;
                    z->parent->parent->col = RBNode::RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z==z->parent->left)
                    {
                        z = z->parent;
                        RightRotate(z);
                    }
                    z->parent->col = RBNode::BLACK;
                    z->parent->parent->col = RBNode::RED;
                    LeftRotate(z->parent->parent);
                }
            }
        root->col = RBNode::BLACK;
    }

    void inorder(RBNode* T)
    {
        if (!isNil(T))
        {
            inorder(T->left);
            cout << T->toString() << ' ';
            inorder(T->right);
        }
    }

    void inorder()
    {
        if (isNil(root))
        {
            cout << "empty";
        }
        else
            inorder(root);
    }

    void display(RBNode* w, int indent)
    {
        if (!isNil(w))
        {
            display(w->right, indent + 2);
            for (int i = 0; i < indent; i++) cout << ' ';
            cout << w->toString() << '\n';
            display(w->left, indent + 2);
        }
    }

    void indentedDisplay()
    {
        if (isNil(root))
            cout << "The RB tree is empty" <<endl;
        else
        {
            cout << "The RB tree is" <<endl;
            display(root, 0);
        }
    }

    // auxiliary method
    int bh(RBNode* x)
    {
        return (isNil(x) ? 0 : countBlacks(x->left));
    }

    // auxiliary method
    int countBlacks(RBNode* x)
    {
        int contor = 0;
        while(x != RBNode::Nil){
            if(x->col == RBNode::BLACK){
                contor++;
            }
            x = x->left;
        }
        return contor;
    }

    /**
     * Compute the black-height of this red-black tree
     */
    int bh()
    {
        RBNode *x = root;
        int contor = 0;
        while(!isNil(x)){
            if(x->col == RBNode::BLACK)
                contor++;
            x = x->left;
        }
        return contor;
    }

    // compute the depth of the tree with root *x
    int depth(RBNode* x)
    {
        if (isNil(x))
        {
            return -1;
        }
        else
        {
            int lDepth = depth(x->left);
            int rDepth = depth(x->right);
            return (lDepth<rDepth ? rDepth : lDepth)+1;
        }
    }

    /**
     * Compute the depth of this red-black tree
     */
    int depth()
    {
        return depth(root);
    }

    /* return the maximum key of black nodes.
     * If the tree is empty, return -1000 */
    int maxBlackKey()
    {
        RBNode *x = root;
        if(isNil(x))
            return -1000;
        while(!isNil(x))
            x = x->right;

        if(x->col == RBNode::BLACK)
            return x->key;
        else return x->parent->key;

    }

    /* return the maximum key of red nodes.
     * If the tree has no red nodes, return -1000 */
    int maxRedKey()
    {
        RBNode *x = root;
        if(isNil(x->right) or isNil(x->left))
            return -1000;
        int nr = -1000;
        while(!isNil(x)){
            if(x->col == RBNode::RED)
                nr = x->key;
            x = x->right;
        }
        if(nr == -1000){
            x = root;
            while(!isNil(x)){
                if(x->col == RBNode::RED)
                    nr = x->key;
                x = x->left;
            }
            return nr;
        }
        return nr;
    }
};

#endif /* RBNODE_H_ */
