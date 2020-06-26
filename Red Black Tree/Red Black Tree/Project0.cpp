//#include<iostream>
//#include<fstream>
//using namespace std;
//int readRowSize(ifstream&);
//int readColSize(ifstream&);
//void readRowColSize(ifstream&, int&, int&);
//void read(ifstream&, char**, int, int);
//void display(char**, int, int);
//char** dynamicMemory(int, int);
//char* dynamicMemory1D(int);
//char** dynamicMemory2D(int);
//int main()
//{
//	char **ptr = nullptr, row = 0, col = 0;
//	ifstream fin("Board.txt");
//	if (!fin.is_open())
//	{
//		cout << "File not Open" << endl;
//		return 0;
//	}
//	else
//	{
//		row = readRowSize(fin);
//		col = readColSize(fin);
//		ptr = dynamicMemory(row, col);
//		read(fin, ptr, row, col);
//		display(ptr, row, col);
//		for (int r = 0; r < row; r++)
//		{
//			delete[]ptr[r];
//			ptr[r] = nullptr;
//		}
//		delete[] ptr;
//		ptr = nullptr;
//		fin.close();
//	}
//	return 0;
//}
//int readRowSize(ifstream& fin)
//{
//	int size = 0;
//	fin >> size;
//	return size;
//}
//int readColSize(ifstream& fin)
//{
//	int size = 0;
//	fin >> size;
//	return size;
//}
//void readRowColSize(ifstream&fin, int&r, int&c)
//{
//	fin >> r;
//	fin >> c;
//}
//void read(ifstream&fin, char **ptr, int row, int col)
//{
//	for (int r = 0; r < row; r++)
//	{
//		for (int c = 0; c < col; c++)
//		{
//			fin >> ptr[r][c];
//		}
//	}
//}
//void display(char** ptr, int row, int col)
//{
//	for (int r = 0; r < row; r++)
//	{
//		for (int c = 0; c < col; c++)
//		{
//			cout << ptr[r][c] << " ";
//		}
//		cout << endl;
//	}
//}
//char **dynamicMemory(int row, int col)
//{
//	char**temp = nullptr;
//	temp = dynamicMemory2D(row);
//	for (int r = 0; r < row; r++)
//	{
//		temp[r] = dynamicMemory1D(col);
//	}
//	return temp;
//}
//char* dynamicMemory1D(int size)
//{
//	char *temp = nullptr;
//	temp = new char[size];
//	return temp;
//}
//char** dynamicMemory2D(int row)
//{
//	char **temp = nullptr;
//	temp = new char *[row];
//	return temp;
//}