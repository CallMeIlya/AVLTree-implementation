#include <queue>
#include <stdio.h>
#include <iostream>

class TreeNode {
	public:
    int height;
		int num;
		TreeNode* left;
		TreeNode* right;
	TreeNode(int _num) {
		this->num=_num;
    this->height = 1;
    left = nullptr;
	}
};


bool isPowerOf2(int num) {
  return (num > 0 && ((num&(num-1)) == 0)) || num == 1;
}

class AVLTree {
	public:
		TreeNode* Root;

    AVLTree(int num) {
      this->Root = new TreeNode(num);
    }
    
    void LevelOrderTraversal(TreeNode* root) {
      std::queue<TreeNode*> nodes;
      nodes.push(root);
      TreeNode* node;
      while(!nodes.empty()) {
        int levelSize = nodes.size();
        for(int i = 0; i < levelSize; i++) {
          node = nodes.front();
          std::cout << node->num << " ";
          nodes.pop();
          if(node->left) {nodes.push(node->left);}
          if(node->right) {nodes.push(node->right);}
        }
        std::cout << std::endl;
      }
    }

    void InorderPrint(TreeNode* root) {
      if(!root) {
        return;
      }
      InorderPrint(root->left);
      std::cout << (root->num) << " " << root->height << "|";
      InorderPrint(root->right);
    }

    void PreOrderPrint(TreeNode* root) {
      if(!root) {
        return;
      }
      std::cout << root->num << " ";
      PreOrderPrint(root->left);
      PreOrderPrint(root->right);
    }

    int findMin(TreeNode* root) {
      while(root->left) {
        root = root->left;
      }
      return root->num;
    }

    int Height(TreeNode* root) {
        if(!root) {
          return 0;
        }
        return root -> height;
    }
    
    int GetBalance(TreeNode* root) {
      if(!root) {
        return 0;
      }
      return Height(root->left) - Height(root->right);
    }

    TreeNode* RightRotate(TreeNode* root) {
        TreeNode* newRoot = root->left;
        TreeNode* t2 = newRoot->right;

        newRoot->right=root;
        root->left=t2;

        root->height = max(Height(root->left), Height(root->right))+1;
        newRoot->height = max(Height(newRoot->left), Height(newRoot->right))+1;

        return newRoot;
    }
 
    TreeNode* LeftRotate(TreeNode* root) {
        TreeNode* newRoot = root->right;
        TreeNode* t2 = newRoot->left;

        newRoot->left=root;
        root->right=t2;

        root->height = max(Height(root->left), Height(root->right))+1;
        newRoot->height = max(Height(newRoot->left), Height(newRoot->right))+1;

        return newRoot;
    }

   
    TreeNode* Insert(TreeNode* root, int _num) {
        if(!root) {
          root = new TreeNode(_num);
          return root;
        }

        if(_num < root -> num) {
          root->left = Insert(root->left, _num);
        } else if(_num > root -> num) {
          root->right = Insert(root->right, _num);
        } else {
          return root;
        }


        //gets the larger of the two
        root->height = max(Height(root->left), Height(root->right))+1;

        //calc balance
        int balance = GetBalance(root);
        
        //left left case
        if(balance > 1 && _num < root->left->num) {
          return RightRotate(root);
        }
        //right right case
        if(balance < -1 && _num > root->right->num) {
          return LeftRotate(root);
        }

        //left right case
        if(balance > 1 && _num > root->left->num) {
          root->left = LeftRotate(root->left);
          return RightRotate(root);
        }
        //right left case
        if(balance < -1 && _num < root->right->num) {
          root->right = RightRotate(root->right);
          return LeftRotate(root);
        }

        //root->height = max(Height(root->left), Height(root->right))+1;
        return root;
    }

    TreeNode* Delete(TreeNode* root, int _num) {
        //base case
        if(!root) {
          return root;
        }
        
        if(_num < root->num) {
          root->left = Delete(root->left, _num);
        } else if(_num > root -> num) {
          root->right = Delete(root->right, _num);
        } else {

        //if no children
        if(root->left == nullptr && root->right == nullptr) {
          delete root;
          return nullptr;
        }


        //single child case
        if(!root->left) {
          return root->right;
        } else if(!root->right) {
          return root->left;
        }
        
        if(root->left && root->right) {
          int min = findMin(root->right);
          root->num = min;
          root->right = Delete(root->right, min);
        }
        }
        
        
        if(!root) {
          return root;
        }

        root->height = max(Height(root->left), Height(root->right))+1;

        //calc balance
        int balance = GetBalance(root);
        
        if(balance > 1) {
          //left-left case
          if(GetBalance(root->left) >= 0) {
            return RightRotate(root);
          } else {
          //left-right case
            root->left = LeftRotate(root->left);
            return RightRotate(root);
          }
        }
        if(balance < -1) {
          //right-right case
          if(GetBalance(root->right) <= 0) {
            return LeftRotate(root);
          } else {
          //right-left case
            root->right = RightRotate(root->right);
            return LeftRotate(root);
          }
        }
        //root->height = max(Height(root->left), Height(root->right))+1;
        return root;       
    }

    int max(int a, int b) {
        if(a > b) {return a;} else {return b;}
    }
};

int main() {
  AVLTree* tree = new AVLTree(15);
  tree->Root = tree->Insert(tree->Root, 18);
  tree->Root = tree->Insert(tree->Root, 16);
  tree->Root = tree->Insert(tree->Root, 14);
  tree->Root = tree->Insert(tree->Root, 9);
  tree->Root = tree->Insert(tree->Root, 6);
  tree->Root = tree->Insert(tree->Root, 12);
  tree->Root = tree->Insert(tree->Root, 3);
  tree->Root = tree->Insert(tree->Root, 7);

  /*
  tree->Delete(tree->Root, 14);
  tree->Delete(tree->Root, 16);
  tree->Delete(tree->Root, 6);
  */
  tree->InorderPrint(tree->Root);
        
  std::cout << std::endl << "--------------------------" << std::endl;

  tree->LevelOrderTraversal(tree->Root);
  std::cout << std::endl;
}

