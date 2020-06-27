#include <iostream>
#include"RBT.h"
using namespace std;

int main()
{
	RBT<int> Tree;
	Tree.Insert(7);
	Tree.Insert(3);
	Tree.Insert(18);
	Tree.Insert(10);
	Tree.Insert(22);
	Tree.Insert(8);
	Tree.Insert(11);
	Tree.Insert(26);
	Tree.Insert(2);
	Tree.Insert(6);
	Tree.Insert(13);

	Tree.PrintTree();

	Tree.Delete(10);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(8);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(7);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(6);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(3);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(18);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(22);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(26);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(11);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(2);
	cout << endl << endl << endl;
	Tree.PrintTree();

	Tree.Delete(13);
	cout << endl << endl << endl;
	Tree.PrintTree();

}
