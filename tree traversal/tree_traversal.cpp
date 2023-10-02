#include <iostream>
#include <queue>
using namespace std;
struct Tree{
    int value;
    Tree * left;
    Tree * right;
    Tree () : value(0), left(nullptr), right(nullptr) {}
    Tree (int value): value(value), left(nullptr), right(nullptr){}
    Tree (int value, Tree * left, Tree * right): value(value), left(left), right (right) {}
};

class Traversal{
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

    vector<vector<int>> bfs(Tree* root){
        vector<vector<int>> ans;
        if (!root) return ans;
        queue <TreeNode*> nodes_q;
        nodes_q.push(root);
        nodes_q.push(NULL);
        vector <int> single_level;
        while (!nodes_q.empty()){
            TreeNode* node = nodes_q.front();
            nodes_q.pop();
            if (node == NULL){
                ans.push_back(single_level);
                single_level.resize(0);
                if (nodes_q.size()!=0) nodes_q.push(NULL);
            }
            else{
                single_level.push_back(node->val);
                if(node->left) nodes_q.push(node->left);
                if(node->right) nodes_q.push(node->right);
            }

        }
        return ans;
    }
};

int main(){
    Tree * t = new Tree(1);
    t->left = new Tree(2);
    t->right = new Tree (3);
    t->right->left = new Tree (4);
    t->right->right = new Tree (5);
    Traversal x;
    cout << "preorder traversal:\n";
    x.preorder(t);
    cout << "inorder traversal:\n";
    x.inorder(t);
    cout << "postorder traversal:\n";
    x.postorder(t);
    cout << "level order traversal (BFS):";
    vector<vector<int>> ans = x.bfs(t);
    for (int i=0;i<ans.size();++i){
        cout<<"\n Tree level "<<(i+1)<<" nodes:\n";
        for (auto j:ans[i]) cout<<j<<", ";
    }
}
