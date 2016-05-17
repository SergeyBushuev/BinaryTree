#include <Node.h>
#include <iostream>
#include <fstream>

template <class T> class Tree;
using namespace std;

template<class T>
TreeNode <T>::TreeNode(const T &a)
{
	key = a;
	left = 0;
	right = 0;
}
template <class T>
T TreeNode <T>::get_key()
{
	return key;
}

template<class T>
Tree<T>::Tree()
{
	root = 0;                      // Пустое дерево
}


/* возможны три случая - если у z нет детей, то помещаем 0 в соответствующее поле
  родителя z, если у z есть один ребенок, то можно вырезать z, соединив его родителя напрямую с
  его ребенком. Если же детей двое, то требуются некоторые приготовления: мы находим следующий
  (в смысле порядка на ключах) за z элемент y; у него нет левого ребенка (всегда). Теперь можно
  скопировать ключ и дополнительные данные из вершины y в вершину z, а саму вершину y удалить
  описанным выше способом */

template<class T>
TreeNode<T>* Tree<T>::delete_node(TreeNode<T> *z)
{
	TreeNode<T>* y;
	TreeNode<T>* x;
	if (z->left == 0 || z->right == 0)               // в этой и следующих двух строках ищем вершину y, которую мы потом вырежем из дерева. Это либо z, либо следующий за z  
		y = z;
	else
		y = find_succsessor(z->get_key());
	if (y->left != 0)                                  // x - указатель на существующего ребенка y или 0 если таковых нет  
		x = y->left;
	else
		x = y->right;
	if (x != 0)                                        // эта и следующие 9 строк - вырезание y  
		x->parent = y->parent;
	if (y->parent == 0)
		root = x;
	else
	{
		if (y == (y->parent)->left)
			(y->parent)->left = x;
		else
			(y->parent)->right = x;
	}
	if (y != z)                                        // если мы вырезали вершин, отличную от z, то ее данные перемещаем в z  
		z->key = y->get_key();
	return y;
}
template<class T>
TreeNode<T>* Tree<T>::find_max(TreeNode<T>* x)
{
	while (x->right != 0)                              // здесь все очевидно - самое максимальное значение у самого правого  
		x = x->right;
	return x;
}

template<class T>
TreeNode<T>* Tree<T>::find_min(TreeNode<T>* x)
{
	while (x->left != 0)
		x = x->left;
	return x;
}
template<class T>
TreeNode<T>* Tree<T>::find_succsessor(const T & val)
{
	TreeNode<T>* x = find_node(root, val);                     /* получим указатель на ноду с ключем val */
	TreeNode<T>* y;
	if (x == 0)
		return 0;
	if (x->right != 0)                                                /* если у нее есть правые дети, то следующий элемент - минимальный в правом поддереве */
		return find_min(x->right);
	y = x->parent;
	while (y != 0 && x == y->right)                                   /* иначе - идем вверх и ищем первый элемент, являющийся левым
																	  потомком своего родителя */
	{
		x = y;
		y = y->parent;
	}
	return y;
}
template<class T>
TreeNode<T>* Tree<T>::find_node(TreeNode<T>* n,
	const T & val)
{
	if (n == 0 || val == n->get_key())
		return n;
	if (val > n->get_key())
		return find_node(n->right, val);
	else
		return find_node(n->left, val);
}
template<class T>
void Tree<T>::inorder_walk(TreeNode<T>* n)
{
	if (n != 0)
	{
		inorder_walk(n->left);
		cout << n->get_key() << endl;
		inorder_walk(n->right);
	}
}

template<class T>
TreeNode<T>* Tree<T>::get_root()
{
	return root;
}
