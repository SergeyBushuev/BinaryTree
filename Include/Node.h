#ifndef _NODE_H
#define _NODE_H
#include <iostream>
#include <fstream>
template <class T>
ostream & operator<<(ostream & out, const Tree<T> &tree);

template <class T>
istream & operator >> (istream & fin, const Tree<T> &tree);

template <class T>
ofstream & operator << (ofstream & fout, const Tree<T> &tree);

class Exceptions {
	char* err;
public:
	Exceptions(char* _err);
	char* what();
};
class File_Not_Open : public Exceptions {
public:
	File_Not_Open();
};

class Empty_tree : public Exceptions {
public:
	Empty_tree();
};

template <class T>
class TreeNode
{
	friend class Tree;
public:
	TreeNode(const T &);
	T get_key();
private:
	TreeNode* left;           // указатель на левую ветку (ребёнка)
	TreeNode* right;          // указатель на правую ветку
	TreeNode* parent;         // указатель на родителя
	T key;            /* ключ */
};

template <class T>
class Tree
{
	class TreeIt;
	using iterator = TreeIt;
public:
	Tree();    // Конструктор 
	Tree(initializer_list<T> L); // Списковый конструктор  
	~Tree();
	int insert_node(const T &);                         // Вставляет узел  
		void inorder_walk(TreeNode<T>*);       // Печатает все ключи в неубывающем порядке  
	bool print_file(ofstream &fout);
	bool print();
	TreeNode<T>* delete_node(TreeNode<T> *);     // Удаляет узел  
	TreeNode<T>* find_node(TreeNode<T>*, const T &);  // Находит элемент по ключу
	TreeNode<T> *get_root();                            // Возвращает указатель на корень дерева  
	iterator begin();
	iterator end();
private:
	TreeNode<T> *root;                                  // Корень  
	TreeNode<T>* find_succsessor(const T &);            // Находит следубщий за элементом с данным ключом элемент
	TreeNode<T>* find_max(TreeNode<T>*);         // Находит узел с минимальным значением ключа и возвращает указатель на него  
	TreeNode<T>* find_min(TreeNode<T>*);
	friend ostream & operator<<(ostream & out, Tree<T> &tree);
	friend istream & operator >> (istream & fin, Tree<T> &tree);
	friend ofstream & operator<<(ofstream & fout, Tree<T> &tree);
	static void fillList(list<const TreeNode*> & list, const TreeNode *);
	class TreeIt {
	public:
		TreeIt() = default;
		TreeIt(const Node * );
		bool operator == (const TreeIt & _iterator) ;
		bool operator != (const TreeIt & _iterator) ;
		TreeIt operator ++();
		const T & operator *();
	private:
		list<const TreeNode *> history_;
	};
};


#endif
