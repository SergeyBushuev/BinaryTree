#ifndef _NODE_H
#define _NODE_H

template <class T>
ostream & operator<<(ostream & out, Tree<T> &tree);

template <class T>
ifstream & operator >> (ifstream & fin, Tree<T> &tree);

template <class T>
ofstream & operator<<(ofstream & fout, Tree<T> &tree);

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
public:
	Tree();    // Конструктор 
	Tree(initializer_list<T> L); // Списковый конструктор  
	~Tree();
	int insert_node(const T &);                         // Вставляет узел  
	void del(TreeNode<T>*)
	TreeNode<T>* delete_node(TreeNode<T> *);     // Удаляет узел  
	void inorder_walk(TreeNode<T>*);                    // Печатает все ключи в неубывающем порядке  
	frined ostream & operator<<(ostream & out, Tree<T> &tree);
	frined ifstream & operator >> (ifstream & fin, Tree<T> &tree);
	frined ofstream & operator<<(ofstream & fout, Tree<T> &tree);
	TreeNode<T>* find_max(TreeNode<T>*);         // Находит узел с минимальным значением ключа и возвращает указатель на него  
	TreeNode<T>* find_min(TreeNode<T>*);
	TreeNode<T>* find_node(TreeNode<T>*, const T &);  // Находит элемент по ключу
	TreeNode<T>* find_succsessor(const T &);            // Находит следубщий за элементом с данным ключом элемент
	TreeNode<T> *get_root();                            // Возвращает указатель на корень дерева  
private:
	TreeNode<T> *root;                                  // Корень  
};


#endif
