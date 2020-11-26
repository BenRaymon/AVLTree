/*
 * BST.hpp
 *
 *  Created on: Nov 1, 2020
 *      Author: Ben Raymon
 */

#include <iostream>
#include <stdlib.h>
using namespace std;
#include "BST.hpp"



BST::BST() {
	root = NULL;
}
BST::BST(string sarr[]) {
	root = new TNode(sarr);
}

bool BST::insert(string sarr[]){
	//empty tree set root to node
	if (root==NULL){
		root = new TNode(sarr);
		root->height = 1;
		return true;
	}
	else{
		TNode* n = root;
		while(n != NULL){
			string name = sarr[0];
			string compareName = n->student->last;
			//if the last names are the same, compare first names
			if(name == compareName){
				name = sarr[3];
				compareName = n->student->first;
			}
			if(name < compareName){ //new data less than current node (go left)
				if(n->left == NULL){
					n->left = new TNode(sarr); //n's left = new node
					n->left->parent = n; //new node parent points to n
					n->left->height = 1; //leaf height 1
					setHeight(n); //adjust heights
					return true;
				}
				else
					n = n->left; //if n is not null, move to next left child
			}
			else if(name > compareName){ //new data > than current node (go right)
				if(n->right == NULL){
					n->right = new TNode(sarr); //n's right is new node
					n->right->parent = n; //new parent points to n
					n->right->height = 1; //leaf height 1
					setHeight(n); //adjust heights
					return true;
				}
				else
					n = n->right; //if n is not null, move to next right child
			}
			else if(name == compareName){
				//they have the same first and last name
				return false;
			}
		}
	}
	return false;
}



void BST::printTreeIO(TNode *n){

	//go to the very left most node
	if(n->left != NULL){
		printTreeIO(n->left);
	}
	//can't go left any more, print that node
	//this also prints the parent node after printing all the left nodes (with recursion)
	n->printNode();
	//after printing left node and parent, check right node (go as left as you can with the right node)
	if(n->right != NULL){
		printTreeIO(n->right);
	}

}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}

void BST::printTreePre(TNode *n){

	n->printNode();
	//check left node first
	if(n->left != NULL){
		printTreePre(n->left);
	}
	//Check the right node after checking the left node
	//only if the right node exists
	if(n->right != NULL){
		printTreePre(n->right);
	}

}

void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}

void BST::printTreePost(TNode *n){

	//go to the very left most node
	if(n->left != NULL){
		printTreePost(n->left);
	}
	//can't go left anymore, go right
	if(n->right != NULL){
		printTreePost(n->right);
	}
	//can't go left or right, prints that node (prints left first, then right, then parent with recursion)
	n->printNode();

}

void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}



void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}


TNode* BST::removeNoKids(TNode *tmp){

	//this node is a left child
	if(tmp->parent->left == tmp){
		tmp->parent->left = NULL; //parent points to null as left child
		//only change heights if node does not have a sibling
		if(tmp->parent->right == NULL){
			tmp->parent->height = 1; //parent with no children is a leaf, height = 0
			setHeight(tmp->parent);
		}
	}
	//this node is a right child
	else if(tmp->parent->right == tmp){
		tmp->parent->right = NULL; //parent points to null as right child
		//only change heights if node does not have a sibling
		if(tmp->parent->left == NULL){
			tmp->parent->height = 1; //parent with no children is a leaf, height = 0
			setHeight(tmp->parent);
		}
	}
	return tmp;

}


TNode* BST::removeOneKid(TNode *tmp, bool leftFlag){

	//tmp has a left child
	if(leftFlag){
		//tmp is a left child
		if(tmp->parent->left == tmp){
			tmp->parent->left = tmp->left; //parent points to tmps left as left child
		}
		//tmp is a right child
		else if(tmp->parent->right == tmp){
			tmp->parent->right = tmp->left; //parent points to tmps left as right child
		}
	}

	//tmp has a right child
	else if(!leftFlag){
		//tmp is a left child
		if(tmp->parent->left == tmp){
			tmp->parent->left = tmp->right; //parent points to tmps right as left child
		}
		//tmp is a right child
		else if(tmp->parent->right == tmp){
			tmp->parent->right = tmp->right; //parent points to tmps right as right child
		}
	}

	//update heights
	setHeight(tmp->parent);

	return tmp;
}


TNode* BST::find(string l, string f){
	TNode* n = root;
	int comparisons = 0;
	while(n != NULL){
		string findName = n->student->last;
		string name = l;
		//if the last name is the same, check for first name
		if(name == findName){
			name = f;
			findName = n->student->first;
		}
		//if current node > data to find (DTF), search left (all data left is less than n's data)
		if(findName > name){
			n = n->left;
			comparisons++;
		}
		//if current node < DTF, search right (all right data is > n's data)
		else if(findName < name){
			n = n->right;
			comparisons++;
		}
		//if the data is the same, return the node
		else if(findName == name){
			comparisons++;
			cout << n->student->last << ", " << n->student->first << " found in " << comparisons << " comparisons" << endl;
			return n;
		}
	}
	return NULL;
}


TNode* BST::remove(string l, string f){

	TNode* n = find(l, f);
	if(n == NULL)
		return NULL;

	//no children
	if(n->left == NULL && n->right == NULL){
		return removeNoKids(n);
	}
	//right child
	else if(n->left == NULL && n->right != NULL){
		return removeOneKid(n, false);
	}
	//left child
	else if(n->left != NULL && n->right == NULL){
		return removeOneKid(n, true);
	}
	//right and left child
	else{
		TNode* tmp = n->left; //tmp is the left child of the node we are removing
		//loop until reaches right most node
		while(tmp->right != NULL){
			tmp = tmp->right;
		} //now tmp is the right most node under n'f left child


		//if tmp has a left child, remove tmp first
		if(tmp->left != NULL){
			removeOneKid(tmp, true);
		}
		else
		{ //prevent tmps parent from pointing to tmp after it is moved and causing an infinite loop
			if(tmp->parent->left == tmp){
				tmp->parent->left = NULL;
			}
			if(tmp->parent->right == tmp){
				tmp->parent->right = NULL;
			}
		}

		if(n != root){
			//n is a left child
			if(n->parent->left == n){
				n->parent->left = tmp;  //parent points to tmp as left child
			}
			//n is a right child
			if(n->parent->right == n){
				n->parent->right = tmp; //parent points to tmp as right child
			}
		}

		if(n->left == tmp)
			n->left = NULL; //don't want it pointing to itself
		tmp->right = n->right; //tmp right now points to n's right child
		tmp->left = n->left; //tmp left now points to n's left child

		//removing the root
		if(n == root){
			root = tmp;
		}
		else{
			tmp->parent = n->parent;
		}

		setHeight(tmp);
		return n;
	}
	return NULL;
}


int BST::getBalance(TNode *n){

	int hLeft = 0, hRight = 0;
	//get height of both children
	if(n->left != NULL){
		hLeft = n->left->height;
	}
	if(n->right != NULL){
		hRight = n->right->height;
	}
	//balance = left height - right height
	return hLeft - hRight;

}


void BST:: setHeight(TNode *n){

	int rHeight = 0, lHeight = 0;
	//set values for both children nodes heights
	if(n->right != NULL){
		rHeight = n->right->height;
	}
	if(n->left != NULL){
		lHeight = n->left->height;
	}

	//compare heights, pick the greatest one
	if(lHeight > rHeight){
		n->height = lHeight+1;
	}
	else if(rHeight > lHeight){
		n->height = rHeight+1;
	}
	else if (rHeight == lHeight){
		n->height = rHeight + 1;
	}

	//check balances
	int balance = getBalance(n);
	if(balance != 0 && balance != 1 && balance != -1){
		//call the correct rotate method if node is left or right child

		if (balance == 2){ //if balance = 2
			if(getBalance(n->left) == 1|| getBalance(n->left) == 0){
				rotateRight(n);
			}
			else if(getBalance(n->left) == -1){
				rotateLeft(n->left);
				rotateRight(n);
			}
		}

		if (balance == -2){ //if balance = -2
			if(getBalance(n->right) == -1 || getBalance(n->right) == 0){
				rotateLeft(n);
			}
			else if(getBalance(n->right) == 1){
				rotateRight(n->right);
				rotateLeft(n);
			}
		}
	}
	//update height of every node above this one, recursive with parent
	if(n != root){
		setHeight(n->parent);
	}

}

TNode* BST::rotateLeft(TNode* y){

	//swap nodes
	TNode* x = y->right;
	y->right = x->left;
	if(y->right != NULL)
		y->right->parent = y;
	x->left = y;

	//swap root if needed
	if(y == root){
		root = x;
	}
	else{ //attach the right parent to the node that was rotated in
		if(y->parent->right == y)
			y->parent->right = x;
		else
			y->parent->left = x;

		x->parent = y->parent;
	}

	//attach the right parent to the node that was rotated out
	y->parent = x;


	//Update the height of the node that was rotated out
	if(y->left == NULL || y->right == NULL){
		if(y->right == NULL && y->left==NULL){
			y->height = 1; //leaf node height = 1
		}
		else if(y->left == NULL){
			y->height = y->right->height+1; //only has a right child
		}
		else if (y->right == NULL){
			y->height = y->left->height+1; //only has a left child
		}
	}
	else{ //height = greatest child + 1
		if (y->left->height > y->right->height) {
			y->height = y->left->height + 1;
		}
		else {
			y->height = y->right->height + 1;
		}
	}


	//Update the height of the node that was rotated in
	if(x->left == NULL || x->right == NULL){
		if(x->right == NULL && x->left==NULL){
			x->height = 1; //leaf node height = 1
		}
		else if(x->left == NULL){
			x->height = x->right->height+1; //only has a right child
		}
		else if (y->right == NULL){
			x->height = x->left->height+1; //only has a left child
		}
	}
	else{ //greatest child + 1
		if (x->left->height > x->right->height) {
			x->height = x->left->height + 1;
		}
		else {
			x->height = x->right->height + 1;
		}
	}

	return x;
}

TNode* BST::rotateRight(TNode* y){

	//swap nodes
	TNode* x = y->left;
	y->left = x->right;
	if(y->left != NULL)
		y->left->parent = y;
	x->right = y;

	//swap root if needed
	if(y == root){
		root = x;
	}
	else{ //attach the right parent to the node that was rotated in
		if(y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;

		x->parent = y->parent;
	}

	//attach the right parent to the node that was rotated out
	y->parent = x;

	//Update the height of the node that was rotated out
	if(y->left == NULL || y->right == NULL){
		if(y->right == NULL && y->left==NULL){
			y->height = 1; //leaf node height = 1
		}
		else if(y->left == NULL){
			y->height = y->right->height+1; //only has a right child
		}
		else if (y->right == NULL){
			y->height = y->left->height+1; //only has a left child
		}
	}
	else{ //height = greatest child + 1
		if (y->left->height > y->right->height) {
			y->height = y->left->height + 1;
		}
		else {
			y->height = y->right->height + 1;
		}
	}

	//Update the height of the node that was rotated in
	if(x->left == NULL || x->right == NULL){
		if(x->right == NULL && x->left==NULL){
			x->height = 1; //leaf node height = 1
		}
		else if(x->left == NULL){
			x->height = x->right->height+1; //only has a right child
		}
		else if (y->right == NULL){
			x->height = x->left->height+1; //only has a left child
		}
	}
	else{ //greatest child + 1
		if (x->left->height > x->right->height) {
			x->height = x->left->height + 1;
		}
		else {
			x->height = x->right->height + 1;
		}
	}

	return x;
}
