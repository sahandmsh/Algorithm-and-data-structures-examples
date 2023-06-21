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

class traversal{
public:
    void preorder(Tree * t){
        if (t){
            cout<<t->value<<endl;
            preorder(t->left);
            preorder(t->right);
        }
    }
    void inorder(Tree * t){
        if (t){
            inorder(t->left);
            cout<<t->value<<endl;
            inorder(t->right);
        }
    }
    void postorder(Tree * t){
        if (t){
            postorder(t->left);
            postorder(t->right);
            cout<<t->value<<endl;
        }
    }
};

int main(){
    Tree * t = new Tree(1);
    t->left = new Tree(2);
    t->right = new Tree (3);
    t->right->left = new Tree (4);
    t->right->right = new Tree (5);
    traversal x;
    cout << "preorder traversal:\n";
    x.preorder(t);
    cout << "inorder traversal:\n";
    x.inorder(t);
    cout << "postorder traversal:\n";
    x.postorder(t);
}
