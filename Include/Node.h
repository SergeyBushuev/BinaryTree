#ifndef _NODE_H
#define _NODE_H

template <class T>   
class TreeNode
{ 
	friend class Tree;
public:
	TreeNode(const T &);
	T get_key(); 
protected:
	TreeNode* left;           // указатель на левую ветку (ребёнка)
	TreeNode* right;          // указатель на правую ветку
	TreeNode* parent;         // указатель на родителя
	T key;            /* ключ */ 
};

template <class T>
class Tree
{ 
public:
	Tree();                                                     // Конструктор  
	int insert_node(const T &);                         // Вставляет узел  
	TreeNode<T>* delete_node(TreeNode<T> *);     // Удаляет узел  
	void inorder_walk(TreeNode<T>*);                    // Печатает все ключи в неубывающем порядке  
	TreeNode<T>* find_max(TreeNode<T>*);         // Находит узел с минимальным значением ключа и возвращает указатель на него  
	TreeNode<T>* find_min(TreeNode<T>*);
	TreeNode<T>* find_node(TreeNode<T>*, const T &);  // Находит элемент по ключу
	TreeNode<T>* find_succsessor(const T &);            // Находит следубщий за элементом с данным ключом элемент
	TreeNode<T> *get_root();                            // Возвращает указатель на корень дерева  
private:
	TreeNode<T> *root;                                  // Корень  
};
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
#endif
