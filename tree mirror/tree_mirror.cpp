#include <iostream>
using namespace std;
struct Tree{
    int value;
    Tree * left;
    Tree * right;
    Tree () : value(0), left(nullptr), right(nullptr) {}
    Tree (int value): value(value), left(nullptr), right(nullptr){}
    Tree (int value, Tree * left, Tree * right): value(value), left(left), right (right) {}
};
class Tree_Operator{
public:
    void mirror (Tree* t){
        Tree *x= new Tree;
        if (t){
            mirror(t->left);
            mirror(t->right);
            x = t->left;
            t->left = t->right;
            t->right = x;
        }
    }
    // preorder traversal to check the tree before and after mirroring
    void preorder(Tree* t){
        if (t){
            cout<<t->value<<endl;
            preorder(t->left);
            preorder(t->right);
        }
    }
};

int main(){
    // creating an example tree
    Tree * t = new Tree(1);
    t->left = new Tree(2);
    t->right = new Tree (3);
    t->right->left = new Tree (4);
    t->right->right = new Tree (5);
    // calling the tree operator class and checking the mirror method
    Tree_Operator x;
    cout << "preorder traversal:\n";
    x.preorder(t);
    x.mirror(t);
    cout << "preorder traversal after mirroring:\n";
    x.preorder(t);
}