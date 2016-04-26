#ifndef _NODE_H
#define _NODE_H

template <class T> class TreeNode
{
	friend class Tree<T>;
public:
	TreeNode(const T &);
	T get_key();
protected:
	TreeNode* left;           // указатель на левую ветку (ребёнка)
	TreeNode* right;          // указатель на правую ветку
	TreeNode* parent;         // указатель на родителя
	T key;            /* ключ */
};

template<class T>
TreeNode <T>::TreeNode(const T &a)
{
	key = a;
	left = right = 0;
}
template <class T>
T TreeNode <T>::get_key()
{
	return key;
}
#endif
