#include <iostream>
#include <iomanip>
#include "tree.h"
using namespace std;
int main()
{
	setlocale(0, "RUS");
	Tree<int> intTree;           //Создание нового дерева, с Int-овым ключом
	int a;
	cout << "Введите 10 чисел:" << endl;   //Заполняем дерево значениями вручную
	for (int i = 0; i<10; i++)
	{
		cin >> a;
		intTree.insert_node(a);
	}
	cout << endl << "Обход:" << endl;              //Обход
	intTree.inorder_walk(intTree.get_root());       //Начинаем обход с начала корня
	cout << "Введите значение узла для удаления:";     //Удаление узла
	cin >> a;
	intTree.delete_node(intTree.find_node(intTree.get_root(), a));    //Удаляем узел с данным значением. Если их два, удалиться только первый
	cout << endl << "Ещё один обход:" << endl;
	intTree.inorder_walk(intTree.get_root());       //Завершающий обход
	system("pause");
}
