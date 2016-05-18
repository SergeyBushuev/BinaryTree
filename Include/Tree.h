#include <iostream>
#include <fstream>
#include "Node.h"

using namespace std;
Exceptions::Exceptions(char* _err) : err(_err) {}
char* Exceptions::what() { return err; }
File_Not_Open::File_Not_Open() : Exceptions("Error1: Файл не открыт") {}
Empty_tree::Empty_tree() : Exceptions("Error#2: Пустое дерево") {}
template <typename T> class Tree;
template<typename T>
TreeNode <T>::TreeNode(const T &a)
{
	key = a;
	left = 0;
	right = 0;
}
template <typename T>
T TreeNode <T>::get_key()
{
	return key;
}

template<typename T>
Tree<T>::Tree()
{
	root = nullptr;                      // Пустое дерево
}
template <typename T>
Tree<T>::Tree(initializer_list<T> L) {
	root = nullptr;
	for (int i : L)
	{
		insert_node(i);
	}
}
template<typename T>
Tree<T>::~Tree()
{
	if (root) {
		del(root);
	}
}
template<typename T>
int Tree<T>::del(TreeNode<T>* z)
{
	if (z->left) {
		del(z->left);
	}
	if (z->right) {
		del(z->right);
	}

	delete z;
}
template<typename T>
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
/* возможны три случая - если у z нет детей, то помещаем 0 в соответствующее поле
родителя z, если у z есть один ребенок, то можно вырезать z, соединив его родителя напрямую с
его ребенком. Если же детей двое, то требуются некоторые приготовления: мы находим следующий
(в смысле порядка на ключах) за z элемент y; у него нет левого ребенка (всегда). Теперь можно
скопировать ключ и дополнительные данные из вершины y в вершину z, а саму вершину y удалить
описанным выше способом */
template <typename T>
bool Tree<T>::print_file(ofstream &fout) {
	if (root != nullptr) {
		if (fout.is_open()) {
			if (left != nullptr) left->print_file(fout);
			fout << k << " ";
			if (right != nullptr) right->print_file(fout);
		}
		return true;
	}
	return false;
}
template <typename T>
bool Tree<T>::print() {
	if (root != nullptr) {
		if (left != nullptr) left->print_console();
		cout << k << " ";
		if (right != nullptr) right->print_console();
		return true;
	}
	else return false;
}
template <typename T>
iterator Tree<T>::begin()
{
	return iterator(root);
}

template <typename T>
iterator Tree<T>::end()
{
	return iterator();
}
template<typename T>
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
	delete z;
	return y;
}
template<typename T>
TreeNode<T>* Tree<T>::find_max(TreeNode<T>* x)
{
	while (x->right != 0)                              // здесь все очевидно - самое максимальное значение у самого правого  
		x = x->right;
	return x;
}
template <typename T>
void Tree<T>::fillList(list<const TreeNode *> & list, const TreeNode * node) -> void
{
	if (node) {
		if (node->left != nullptr) {
			fillList(list, node->left);
		}

		listOfNodes.push_back(node);

		if (node->right != nullptr) {
			fillList(list, node->right);
		}
	}
}

template<typename T>
TreeNode<T>* Tree<T>::find_min(TreeNode<T>* x)
{
	while (x->left != 0)
		x = x->left;
	return x;
}
template<typename T>
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
template<typename T>
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
template<typename T>
void Tree<T>::inorder_walk(TreeNode<T>* n)
{
	if (n != 0)
	{
		inorder_walk(n->left);
		cout << n->get_key() << endl;
		inorder_walk(n->right);
	}
}

template<typename T>
TreeNode<T>* Tree<T>::get_root()
{
	return root;
}
template <typename T>
istream & operator >>(istream & fin, Tree<T> & tree) {
	if (!fin.is_open()) throw File_Not_Open();
	T x;
	while (!fin.eof()) {
		fin >> x;
		if (x != -1)tree.insert_node(x);
		else break;
	}
	return fin;
}
template <typename T>
ostream & operator <<(ostream & out, Tree<T> & tree) {
	if (tree.root->print()) return out;
	else throw Empty_tree();
}
template <typename T>
ofstream & operator <<(ofstream & fout, Tree<T> & tree) {
	if (tree.root->print_file(fout)) return fout;
	else throw Empty_tree();
}
template <typename T>
Tree<T>::TreeIt::TreeIt(const TreeNode * node) 
{
	fillList(history_, node);
}

template <typename T>
bool Tree<T>::TreeIt::operator == (const TreeInt & _iterator)
{
	return this->history_ == _iterator.history_;
}

template <typename T>
bool Tree<T>::TreeIt::operator != (const TreeInt & _iterator)
{
	return !this->operator==(_iterator);
}

template <typename T>
TreeIt Tree<T>::TreeIt::operator ++()
{
	history_.pop_front();
	return *this;
}

template <typename T>
const T & Tree<T>::TreeIt::operator *()
{
	return history_.front()->key;
}
