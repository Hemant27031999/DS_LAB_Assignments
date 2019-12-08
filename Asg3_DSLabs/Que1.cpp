/**
 * @file Que1.cpp
 * @author Hemant
 * @brief This program works on different types of trees
 * @version 0.1
 * @date 2019-08-20
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
enum Color {RED, BLACK};

int a[1000];
int inorder[1000];

/**
 * @brief This is the node datastructure
 */
class Node
{
	public:
		int value;
		Node* left;
		Node* right;
		Node* parent;
		int height;
		bool color;

	public:
		Node(){};
		Node(int v){
			value = v;
			parent = left = right = NULL;
			color = RED;
		}
};

/**
 * @brief This is BST Tree datastructure
 *
 */
class Tree{
	public:
		Node* root;

	public:
		Tree(){};
};

/**
 * @brief find the leafs in a tree
 *
 * @param The root
 * @param Helping parameter
 * @return pointer to the leaf
 */
Node* findend(Node* current, int v){
	if(!current){
		return current;
	}
	else{
		if(v > current->value){
			if(!current->right){
				return current;
			}
			else{
				return findend(current->right, v);
			}
		}
		else{
			if(!current->left){
				return current;
			}
			else{
				return findend(current->left, v);
			}
		}
	}
}

/**
 * @brief find the height in a tree
 *
 * @param pointer to the root
 * @return height of the tree
 */
int getHeight(Node* node){
	if(node == NULL) return 0;
	else
		return node->height;
}

/**
 * @brief used to find height
 *
 * @param pointer to the root
 * @return height of the subtree
 */
int height(Node *N) {
    if (N == NULL)
        return 0;

    N->height = max(height(N->left), height(N->right))+1;
    return N->height;
}

/**
 * @brief print level wise identation og tree nodes
 *
 * @param pointer to the root
 * @param number of spaces
 */
void printTree(Node* node, int space){
	height(node);
	if(node == NULL) return;

	for (int i = 0; i < 4*space; i++){
		cout<<" ";
	}

	cout<<node->value<<"["<<getHeight(node->left)-getHeight(node->right)<<"]"<<endl;
	printTree(node->left, space+1);
	printTree(node->right, space+1);
}

/**
 * @brief used to make tree
 *
 * @param pointer to the tree
 * @param helper parameter
 * @return pointer to the root
 */
Node* maketree(Tree* tree, int v){
	Node* node = new Node(v);
	if(!tree->root){
		tree->root = node;
	}
	else{
		Node* last = findend(tree->root, v);
		if(v < last->value){
			last->left = node;
		}
		else{
			last->right = node;
		}
	}
}

/**
 * @brief used to print all paths of tree
 *
 * @param helper parameter
 * @return pointer to the root
 * @param helper parameter
 */
void printallpaths(int* number, Node* node, int level){
		if(node->value){
			a[level]=node->value;
		}

		if(node->left == NULL && node->right == NULL){
			cout<<"Path "<<*number<<" : ";
			for (int j = 0; j <= level; j++)
			{
				if(j!=0){
				cout<<"         ";}
				for (int i = j; i <= level; i++)
					{
					cout<<a[i]<<" ";
					}
					cout<<endl;
			}
			*number+=1;
			cout<<endl;
		}

		if((node->left)){
			printallpaths(number, node->left, level+1);
		}

		if((node->right)){
			printallpaths(number, node->right, level+1);
		}
	}

	/**
	 * @brief used to extract tree data inorder
	 *
	 * @param pointer to the root
	 * @param helper parameter
	 * @return number of nodes
	 */
int inorderExtract(Node* node, int* index){
	if(node->left){
		inorderExtract(node->left, index);
	}
	inorder[*index]=node->value;
	*index = *index + 1;
	if(node->right){
		inorderExtract(node->right, index);
	}
	return *index;
}

/**
 * @brief method to give maximum between two numbers
 *
 * @param para 1
 * @param para 2
 * @return maximum of two
 */
int max(int a, int b)  {  return (a > b)? a : b;  }


/**
 * @brief datastructure returning a node of tree with initialized values
 *
 */
Node* newNode(int value)
{
    Node* node = new Node();
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

/**
 * @brief used for RR rotation of AVL
 *
 * @param pointer to the rotating node
 * @return pointer to the  new base node
 */
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;
    y->parent = x;

    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    return x;
}

/**
 * @brief used for LL rotation of AVL
 *
 * @param pointer to the rotating node
 * @return pointer to the  new base node
 */
Node *leftRotate(Node *x){
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;
    x->parent = y;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    return y;
}

/**
 * @brief getting balance factor of a node
 *
 * @param pointer to the node
 * @return BalanceFactor
 */
int getBalance(Node *N){
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

/**
 * @brief method for AVL insertion
 *
 * @param pointer to the node
 * @param value to be inserted
 * @return pointer to the root
 */
Node* insertAVL(Node* node, int value){
    if (node == NULL)
        return(newNode(value));

    if (value < node->value)
        node->left = insertAVL(node->left, value);
    else if (value > node->value)
        node->right = insertAVL(node->right, value);
    else
        return node;

    node->height = 1 + max(height(node->left),
                        height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && value < node->left->value)
        return rightRotate(node);

    if (balance < -1 && value > node->right->value)
        return leftRotate(node);

    if (balance > 1 && value > node->left->value){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && value < node->right->value){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

/**
 * @brief datastructure for RBL tree
 *
 */
class RBTree {
public:
    Node *root;
protected:
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
    void fixViolation(Node *&, Node *&);
public:
    RBTree() { root = NULL; }
    void insert(const int &n);
};


/**
 * @brief preparing base BST for AVL
 *
 * @param pointer to the root
 * @param value to be node
 * @return pointer to the root
 */
Node* BSTInsert(Node* root, Node *pt)
{
    if (root == NULL)
       return pt;

    if (pt->value < root->value)
    {
        root->left  = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->value > root->value)
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }
    return root;
}


/**
 * @brief used for RR rotation of RBL
 *
 * @param pointer to the rotating node
 * @return pointer to the  new base node
 */
void RBTree::rotateLeft(Node *&root, Node *&pt) {
    Node *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != NULL)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

/**
 * @brief used for RR rotation of RBL
 *
 * @param pointer to the rotating node
 * @return pointer to the  new base node
 */
void RBTree::rotateRight(Node *&root, Node *&pt) {
    Node *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != NULL)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

/**
 * @brief fixes violations caused by BST insertion
 *
 * @param pointer to the root
 * @param value to be node
 */
void RBTree::fixViolation(Node *&root, Node *&pt){
    Node *parent_pt = NULL;
    Node *grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left) {
            Node *uncle_pt = grand_parent_pt->right;

            if (uncle_pt != NULL && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->right){
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        else{
            Node *uncle_pt = grand_parent_pt->left;

            if ((uncle_pt != NULL) && (uncle_pt->color == RED)){
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->left){
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }
    root->color = BLACK;
}

/**
 * @brief insertion in RBT
 *
 * @param value to be inserted
 */
void RBTree::insert(const int &value){
    Node *pt = new Node(value);
    root = BSTInsert(root, pt);
    fixViolation(root, pt);
}

/**
 * @brief the main driving function
 * @return 0
 */
int main()
{
		Tree* treeBST = new Tree();
		int number=1;

		Node *treeAVL = NULL;

    RBTree treeRBL;

		int haveCount=0;
		int onof=1;
		while(onof){
			cout<<"1. To insert a node in the BST and in the red-black tree\n2. To create AVL tree from the inorder traversal of the BST\n3. To print the inorder traversal of the BST/AVL/red-black tree\n4. To display all the paths in the BST/AVL tree/red-black tree\n5. To print the BST/AVL tree/red-black Tree in the terminal using level-wise indentation\n6. Exit\n";
			cout<<endl;
			cout<<"Enter the index : ";
			int ch;
			cin>>ch;
			cout<<endl;

			switch (ch)
			{
				case 1:
					int value;
					cout<<"Enter the value ";
					cin>>value;
					haveCount++;
					maketree(treeBST, value);
					treeRBL.insert(value);
					break;
				case 2:
					number=0;
					inorderExtract(treeBST->root, &number);
					treeAVL=NULL;
					for(int i=0;i<haveCount;i++){
						treeAVL = insertAVL(treeAVL, inorder[i]);
					}
					cout<<"AVL tree created."<<endl;
					break;
				case 3:
					cout<<"The inorder traversal of BST tree is:"<<endl;
					number=0;
					number = inorderExtract(treeBST->root, &number);
					for(int i=0;i<number;i++){
						cout<<inorder[i]<<" ";
					}
					cout<<endl;
					cout<<endl;
					cout<<"The inorder traversal of AVL tree is:"<<endl;
					number=0;
					number = inorderExtract(treeAVL, &number);
					for(int i=0;i<number;i++){
						cout<<inorder[i]<<" ";
					}
					cout<<endl;
					cout<<endl;
					cout<<"The inorder traversal of Red Black tree is:"<<endl;
					number=0;
					number = inorderExtract(treeRBL.root, &number);
					for(int i=0;i<number;i++){
						cout<<inorder[i]<<" ";
					}
					cout<<"\n\n";
					break;
				case 4:
	        cout<<"The complete path of BST Tree:"<<endl;
					number=0;
	        printallpaths(&number, treeBST->root, 0);
					cout<<endl;
	        cout<<"The complete path of AVL Tree"<<endl;
					number=0;
	        printallpaths(&number, treeAVL, 0);
					cout<<endl;
	        cout<<"The complete path of RED BLACK Tree:"<<endl;
					number=0;
	        printallpaths(&number, treeRBL.root, 0);
					cout<<endl;
	        break;
					cout<<endl;
				case 5:
	        cout<<"The level-wise indentation of BST Tree:"<<endl;
	        printTree(treeBST->root, 0);
					cout<<endl;
	        cout<<"The level-wise indentation of AVL Tree:"<<endl;
	        printTree(treeAVL, 0);
					cout<<endl;
	        cout<<"The level-wise indentation of RED BLACK Tree:"<<endl;
	        printTree(treeRBL.root, 0);
					cout<<endl;
	        cout<<endl;
	        break;
	      case 6:
	        exit(0);
	        break;
	       default:
	            break;
			}
		}

	return 0;
}
