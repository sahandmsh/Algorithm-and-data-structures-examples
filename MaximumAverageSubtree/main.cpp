class Treenode{
  int val;
  TreeNode* left;
  TreeNode* right;
public:
  TreeNode():val(0),left(nullptr),right(nullptr){}
  TreeNode(int val):val(val),left(nullptr),right(nullptr){}
};

class maximumAverageSubtree {
    double ans;
    pair<int,int> postorder(TreeNode* root){
        if (!root) return make_pair(0,0);
        auto [lCount,lSum] = postorder(root->left);
        auto [rCount,rSum] = postorder(root->right);
        int nodesCount = lCount+rCount+1;
        int sum = lSum+rSum+root->val;
        ans = max(ans,(double)sum/nodesCount);
        return make_pair(nodesCount,sum);
    }
public:
    double findMaximumAverageSubtree(TreeNode* root) {
        ans=0;
        postorder(root);
        return ans;
    }
};
