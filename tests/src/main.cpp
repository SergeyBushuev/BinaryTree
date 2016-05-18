
#include <Node.h>
#include <catch.hpp>
#include <fstream>
#include <iostream>
template<class T>
int Tree<T>::insert_node(const T &x)
{
	TreeNode<T>* n = new TreeNode<T>(x);  
	TreeNode<T>* ptr;
	TreeNode<T>* ptr1;

	n->parent = n->left = n->right = 0;           
	ptr = root;
	ptr1 = ptr;
	while (ptr != 0)                     
	{
		ptr1 = ptr;                 
		if (x < ptr->get_key())  
			ptr = ptr->left;
		else
			ptr = ptr->right;   
	};
	n->parent = ptr1;
	if (ptr1 == 0)                       // Если дерево пусто, то вставленный узел становиться корнем
		root = n;
	else
	{
		if (x < ptr1->get_key())
			ptr1->left = n;
		else
			ptr1->right = n;
	}
	return 0;
}
SCENARIO("insert_int", "[insert_node]") {
	Tree<int> intTree;
	REQUIRE(intTree.insert_node(1));
	REQUIRE(intTree.insert_node(2));
	REQUIRE(intTree.insert_node(3));
}
 
