/*
 * BST.hpp
 *
 *  Created on: Nov 1, 2020
 *      Author: Ben Raymon
 */

#ifndef BST_HPP_
#define BST_HPP_

#include "TNode.hpp"

class BST {
	TNode *root;

public:
	BST();
	BST(string sarr[]);
	bool insert(string sarr[]);
	TNode *find(string l, string f);
	void printTreeIO();
	void printTreeIO(TNode *n);
	void printTreePre();
	void printTreePre(TNode *n);
	void printTreePost();
	void printTreePost(TNode *n);
	void clearTree();
	void clearTree(TNode *tmp);
	TNode *removeNoKids(TNode *tmp);
	TNode *removeOneKid(TNode *tmp, bool leftFlag);
	TNode *remove(string s, string l);
	void setHeight(TNode *n);

	int getBalance(TNode *tmp);
	TNode *rotateRight(TNode *tmp);
	TNode *rotateLeft(TNode *tmp);
};






#endif /* BST_HPP_ */
