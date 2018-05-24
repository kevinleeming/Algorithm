#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class node{
public:
	node *left;
	node *right;
	node *parent;
	int key;
	int color; // 0:red, 1:black
	node(){
		left = NULL;
		right = NULL;
		parent = NULL;
	};

	friend class RBT;
};

class RBT{
public:
	node *root;
	node *neel;

	void leftRotate(node *x);
	void rightRotate(node *y);
	void InsertRBT(int key);
	void InsertRBTfixedup(node *current);
	void DeleteRBT(int key);
	void DeleteRBTfixedup(node *current);
	node* RBTsearch(int key);
    node* treeMax(node* current);
    void RBTtransplant(node *n1, node *n2);
    void InorderTraverse(node *r, ofstream& of);

    RBT(){
    	neel = new node;
    	neel->color = 1;
    	root = neel;
    	root->parent = neel;
		root->left = neel;
		root->right = neel;
    } 

};

void RBT::InsertRBT(int key){

	node *y = neel; // to store insertNode's parent
	node *x = root;	// pointer to traverse down
         
	node* i_Node = new node;
    i_Node->key = key;

	while(x != neel){
		y = x;
		if(key <  x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	i_Node->parent = y;

	if(y == neel){
		this->root = i_Node;
	}
	else if(i_Node->key < y->key){
		y->left = i_Node;
	}
	else{
		y->right = i_Node;
	}

	i_Node->left = neel;
	i_Node->right = neel;
	i_Node->color = 0;

	InsertRBTfixedup(i_Node);
}

void RBT::InsertRBTfixedup(node *current){
	while(current->parent->color == 0){
		// the parent is the leftchild of its grandparnt
		if(current->parent == current->parent->parent->left){
			node *uncle = current->parent->parent->right;
			// case 1 : uncle is red
			if(uncle->color == 0){
				current->parent->color = 1;
                uncle->color = 1;
                current->parent->parent->color = 0;
                current = current->parent->parent;
			}
			// case 2 & 3 : uncle is black
			else{
				// case 2
				if(current == current->parent->right){
					current = current->parent;
                    leftRotate(current);
				}
				// case 3
				current->parent->color = 1;
                current->parent->parent->color = 0;
                rightRotate(current->parent->parent);
			}
		}
		// the parent is the rightchild of its grandparnt
		else{
			node *uncle = current->parent->parent->left;
			// case 1 : uncle is red
			if(uncle->color == 0){
				current->parent->color = 1;
                uncle->color = 1;
                current->parent->parent->color = 0;
                current = current->parent->parent;
			}
			// case 2 & 3 : uncle is black
			else{
				// case2
				if (current == current->parent->left) {
                    current = current->parent;
                    rightRotate(current);
                }
                // case3
                current->parent->color = 1;
                current->parent->parent->color = 0;
                leftRotate(current->parent->parent);
			}
		}	
	}
	root->color = 1;
}

void RBT::leftRotate(node *x){
	node *y = x->right;

	x->right = y->left;
	if(y->left != neel){
		y->left->parent = x;
	}

	y->parent = x->parent;
	if(x->parent == neel){
		root = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;

}

void RBT::rightRotate(node *y){
	node *x = y->left;

    y->left = x->right;
    if(x->right != neel){
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == neel){
        root = x;        
    }              
    else if(y == y->parent->left){
        y->parent->left = x;
    }
    else{
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void RBT::InorderTraverse(node *r, ofstream& of){
	if(r == neel){
		return;
	}
	InorderTraverse(r->left, of);
	of << "key: " << r->key << " parent: ";
	if(r->parent == neel){
		of << " ";
	}
	else{
		of << r->parent->key;
	}
	of << " color: ";
	if(r->color == 0){
		of << "red" << endl;
	}
	else{
		of << "black" << endl;
	}
	InorderTraverse(r->right, of);
}

node* RBT::RBTsearch(int key){
	node *cur = root;
	while(cur != NULL && key != cur->key){
		if(key < cur->key){
			cur = cur->left;
		}
		else{
			cur = cur->right;
		}
	}
	return cur;
}

void RBT::DeleteRBT(int key){
	node *deletedNode = RBTsearch(key);

	node *y = 0; // node been deleted
	node *x = 0; // the child of node been deleted

	y = deletedNode;
	int originColor = y->color;

	if(deletedNode->left == neel){
		x = deletedNode->right;
    	RBTtransplant(deletedNode,deletedNode->right);
	}
  	else if(deletedNode->right == neel){
		x = deletedNode->left;
    	RBTtransplant(deletedNode,deletedNode->left);
	}
	else{ // have two children
		y = treeMax(deletedNode->left);
		originColor = y->color;
		x = y->left;

		if(y->parent == deletedNode){
			x->parent = y;
		}

		else{
			RBTtransplant(y, y->left);
			y->left = deletedNode->left;
			y->left->parent = y;
		}
		RBTtransplant(deletedNode, y);
		y->right = deletedNode->right;
        y->right->parent = y;
        y->color = deletedNode->color;


	}
	if(originColor == 1){
		DeleteRBTfixedup(x);
	}
	//delete y;
}

void RBT::RBTtransplant(node *n1, node *n2){
	if(n1->parent == neel){
		root = n2;
	}
	else if(n1 == n1->parent->left){
		n1->parent->left = n2;
	}
	else{
		n1->parent->right = n2;
	}

	n2->parent = n1->parent;
}

node* RBT::treeMax(node* current){
	while(current->right != neel){
		current = current->right;
	}
	return current;
}

void RBT::DeleteRBTfixedup(node *current){
	while(current != root && current->color == 1){

    if(current == current->parent->left){

        node* sibling = current->parent->right;

        if(sibling->color == 0){ // case 1 : sibling is red
        	sibling->color = 1;
            current->parent->color = 0;
            leftRotate(current->parent);
            sibling = current->parent->right;
        }

        // case 2.3.4 : sibling is black
        // case 2 : sibling has two black children
        if(sibling->left->color == 1 && sibling->right->color == 1){
			sibling->color = 0;
            current = current->parent;
        }

        else
        {
          if(sibling->right->color == 1){
	          sibling->left->color = 1;
	          sibling->color = 0;
	          rightRotate(sibling);
	          sibling = current->parent->right;
          }
          sibling->color = current->parent->color;
          current->parent->color = 1;
          sibling->right->color = 1;
          leftRotate(current->parent);
          current = root;
        }
    }
    else{

        node* sibling = current->parent->left;

        if(sibling->color == 0){
           sibling->color = 1;
           current->parent->color = 0;
           rightRotate(current->parent);
           sibling = current->parent->left;
        }

        if(sibling->right->color == 1 && sibling->left->color == 1){
           sibling->color = 0;
           current = current->parent;
        }
        else
        {
          if(sibling->left->color == 1){
          sibling->right->color = 1;
          sibling->color = 0;
          leftRotate(sibling);
          sibling = current->parent->left;
          }
          sibling->color = current->parent->color;
          current->parent->color = 1;
          sibling->left->color = 1;
          rightRotate(current->parent);
          current = root;
        }
    }
}
  current->color = 1;
}

int main(){
	int work, method;
	vector<int> keyVal, total;
	string s;
	ifstream fp("input.txt");
	ofstream ofp("output.txt");
	RBT rbt;

	fp >> work;
	for(int i = 0; i < work; i++){
		
		keyVal.clear();
		fp >> method;
		getline(fp, s);
		stringstream ss;
		getline(fp, s);
		ss << s;
		int temp;
		while(ss >> temp){
			keyVal.push_back(temp);
		}

		if(method == 1){
			ofp << "Insert: ";
			for(int j = 0; j < keyVal.size(); j++){
				if(j == keyVal.size()-1){
					ofp << keyVal[j] << endl;
				}
				else{
					ofp << keyVal[j] << ", ";
				}
				rbt.InsertRBT(keyVal[j]);
			}
		}
		else if(method == 2){
			ofp << "Delete: ";
			for(int j = 0; j < keyVal.size(); j++){
				if(j == keyVal.size()-1){
					ofp << keyVal[j] << endl;
				}
				else{
					ofp << keyVal[j] << ", ";
				}
				rbt.DeleteRBT(keyVal[j]);
			}
		}
		rbt.InorderTraverse(rbt.root, ofp);
	}
}
