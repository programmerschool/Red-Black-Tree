#pragma once
#include<iostream>
#include<fstream>
using namespace std;
template<typename T>

class RBT
{
	enum Color { RED, BLACK };
	struct Node
	{
		T Data;
		Color color;
		Node* Left;
		Node* Right;
		Node* Parent;
		int Count;
		bool DoubleBlack;
		bool DeleteDoubleBlack;
		// Constructor 
		Node(T D, Node* P, Color c = RED, int C = 1)
		{
			Data = D;
			Left = nullptr;
			Right = nullptr;
			Parent = P;
			color = c;
			Count = C;
			DoubleBlack = false;
			DeleteDoubleBlack = false;
		}

		Node(const Node &N)
		{
			Data = N.Data;
			Left = N.Left;
			Right = N.Right;
			Parent = N.Parent;
			color = N.color;
			Count = N.Count;
			DoubleBlack = N.DoubleBlack;
			DeleteDoubleBlack = N.DeleteDoubleBlack;
		}

		Node* sibling()
		{
			if (Parent)
			{
				if (this == Parent->Right)
					return Parent->Left;
				else
				{
					return Parent->Right;
				}
			}
			return nullptr;
		}

		Node* GrandParent(/*Node* N*/)
		{
			if (this && this->Parent)
			{
				if (this->Parent->Parent)
					return this->Parent->Parent;
			}
			return nullptr;
		}

		Node* Uncle(/*Node* N*/)
		{
			Node* G = this->GrandParent();
			if (!G)
				return nullptr; // No grandparent means no uncle
			if (this->Parent == G->Left)
			{
				if (G->Right)
					return G->Right;
			}
			else
			{
				if (G->Left)
					return G->Left;
			}
			return nullptr;
		}

		Node* operator++(int)
		{
			Node* tmp = this;
			this->Count++;
			return this;
		}

		void AlterColor()
		{
			if (color == RED)
				color = BLACK;
			else
				color = RED;
		}

		void operator = (const Node* &N)
		{
			Data = N->Data;
			Left = N->Left;
			Right = N->Right;
			Parent = N->Parent;
			color = N->color;
			Count = N->Count;
			isDoubleBlack = N->isDoubleBlack;
			DeleteDoubleBlack = N->DeleteDoubleBlack;
		}

		friend ostream& operator<< (ostream &, const Node &c)
		{
			for (int i = 0; i < c.Count; i++)
			{
				cout << c.Data << "-";
				if (c.color == 0)
					cout << "Red   ";
				else
					cout << "Black   ";
			}
			return cout;
		}
		
		
		// Functions used in Deletion:
		bool isLeafNode()
		{
			return !Right && !Left;
		}
		bool isOneChild()
		{
			return ((!Right && Left) || (Right && !Left));
		}
		Node* OneChild()
		{
			if (!Right)
				return Left;
			else
			if (!Left)
				return Right;
		} 
		void swapColor(Node* N)
		{
			Color tmp = color;
			color = N->color;
			N->color = tmp;
		}
		bool isBlackChildren()
		{
			return (((!Right || Right->color == BLACK) && (!Left || Left->color == BLACK)) || ((!Left || Left->color == BLACK) && (!Right || Right->color == BLACK)));
		}
		bool isBlackRightLineChild(Node* s)
		{
			if (Right && Right == s && (Right->Right == nullptr || Right->Right->color == BLACK))
			{
				return true;
			}
			return false;
		}
		bool isBlackLeftLineChild(Node* s)
		{
			if (Left && Left == s && (Left->Left == nullptr || Left->Left->color == BLACK))
			{
				return true;
			}
			return false;
		}

		bool isRedRightLineChild(Node* s)
		{
			if (Right && Right == s && Right->Right && Right->Right->color == RED)
			{
				return true;
			}
			return false;
		}
		bool isRedLeftLineChild(Node* s)
		{
			if (Left && Left == s && Left->Left && Left->Left->color == RED)
			{
				return true;
			}
			return false;
		}

		bool isRedRightTriangleChild(Node* s)
		{
			if (Right && Right == s && Right->Left && Right->Left->color == RED)
			{
				return true;
			}
			return false;
		}
		bool isRedLeftTriangleChild(Node* s)
		{
			if (Left && Left == s && Left->Right && Left->Right->color == RED)
			{
				return true;
			}
			return false;
		}
		bool HaveBothChild()
		{
			return Right && Left;
		}
		
		bool isDoubleBlack()
		{
			return DoubleBlack;
		}
		bool isSameChildren()
		{
			if (!((!Right && (!Left || Left->color == BLACK)) || (!Left && (!Right || Right->color == BLACK))))
			{
				return Right && Left;
			}
			return  true;
		}
		bool isBothChildrenRed()
		{
			return Right && Right->color == RED && Left && Left->color == RED;
		}
	};
	
public:
	Node* MIN(Node *R)
	{
		if (!R->Left)
			return R;
		MIN(R->Left);
	}

	Node* MAX(Node *R)
	{
		if (!R->Right)
			return R;
		MAX(R->Right);
	}
	Node* successor(Node* N)
	{
		if (N->Right)
			return MIN(N->Right);
		Node* M = N->Parent;
		while (M && M->Right == N)
		{
			N = M;
			M = M->Parent;
		}
		return M;
	}

	Node* predecessor(Node* N)
	{
		if (N->Left)
			return MAX(N->Left);
		Node* M = N->Parent;
		while (M && M->Left == N)
		{
			N = M;
			M = M->Parent;
		}
		return M;
	}
	class iteratorLNR
	{
		Node* N;
	public:
		iteratorLNR()
		{
			N = nullptr;
		}

		iteratorLNR(Node* n)
		{
			N = n;
		}

		Node* MIN(Node *R)
		{
			if (!R->Left)
				return R;
			MIN(R->Left);
		}

		Node* MAX(Node *R)
		{
			if (!R->Right)
				return R;
			MAX(R->Right);
		}

		Node* successor(Node* N)
		{
			if (N->Right)
				return MIN(N->Right);
			Node* M = N->Parent;
			while (M && M->Right == N)
			{
				N = M;
				M = M->Parent;
			}
			return M;
		}

		Node* predecessor(Node* N)
		{
			if (N->Left)
				return MAX(N->Left);
			Node* M = N->Parent;
			while (M && M->Left == N)
			{
				N = M;
				M = M->Parent;
			}
			return M;
		}

		bool operator==(const iteratorLNR &li)const
		{
			return N == li.N;
		}

		bool operator!=(const iteratorLNR &li)const
		{
			return N != li.N;
		}

		iteratorLNR& operator++()
		{
			N = successor(N);
			return *this;
		}

		iteratorLNR& operator--()
		{
			N = predecessor(N);
			return *this;
		}

		T& operator*()
		{
			return N->Data;
		}
	};
private:
	Node *Root;
	int size;
	
	void RotateLeft(Node* &T)
	{
		Node* TR = T->Right;
		Node* X = T;
		if (T->Parent)
		{
			if (T == T->Parent->Left)
			{
				T->Parent->Left = TR;
			}
			else
			{
				T->Parent->Right = TR;
			}
		}
		T->Right = TR->Left;
		if (TR->Left)
		{
			T->Right->Parent = T;
		}
		TR->Parent = T->Parent;
		TR->Left = X;
		X->Parent = TR;
		if (X == Root)
			Root = TR;
	}
	void RotateRight(Node* &T)
	{
		Node* TL = T->Left;
		Node* X = T;
		if (T->Parent)
		{
			if (T == T->Parent->Left)
			{
				T->Parent->Left = TL;
			}
			else
			{
				T->Parent->Right = TL;
			}
		}

		T->Left = TL->Right;
		if (TL->Right)
		{
			T->Left->Parent = T;
		}
		TL->Parent = T->Parent;
		TL->Right = X;
		X->Parent = TL;
		if (X == Root)
			Root = TL;
	}

	void FollowAllRules(Node* &X)
	{
		/*
			4 - If parent of newNode is Red, then check the color of uncle node.
				a) If color is Black then do suitable rotations and recolor.
				b) If color is Red then recolor and also check if GrandParent node is noot root then recolor it and recheck.
		*/
		Node* N = X;
		while (N->Parent!=nullptr && N->Parent->color == RED)
		{
			if (N->Uncle()!=nullptr && N->Uncle()->color == RED)
			{
				N->Parent->AlterColor();
				N->Uncle()->AlterColor();
				if (N->GrandParent() != Root)
				{
					N->GrandParent()->AlterColor();
				}
				N = N->GrandParent();
			}
			else
			if (!N->Uncle() || N->Uncle()->color == BLACK)
			{
				if (N->Parent == N->GrandParent()->Left)
				{
					Node* T = N->GrandParent()->Right;
					if (N == N->Parent->Right)
					{
						N = N->Parent;
						RotateLeft(N);
					}
					N->Parent->AlterColor();
					N->GrandParent()->AlterColor();
					RotateRight(N->Parent->Parent);
				}
				else
				{
					Node* T = N->GrandParent()->Left;
					if (N == N->Parent->Left)
					{
						N = N->Parent;
						RotateRight(N);
					}
					N->Parent->AlterColor();
					N->GrandParent()->AlterColor();
					RotateLeft(N->Parent->Parent);
				}
			}
		}
	}
	void InsertRecursively(Node* &N, Node* P, T V) // R = Root , P = Parent , V = Value
	{
		/*
			1 - If tree is empty, create newNode as Root node with color Black.
			2 - If tree is not empty, create newNode as leaf node with color Red.
			2 - If parent of the newNode is Black then exit.
		*/
		if (N == nullptr)
		{
			if (!Root)  // Inserting First Value
			{
				N = new Node(V, P, BLACK);
			}
			else
			{
				N = new Node(V, P);

				if (N->Parent->color != BLACK) // if Parent of Inserting Node is Black
				{
					FollowAllRules(N);
				}
			}
			return;
		}
		if (V == N->Data)
		{
			(*N)++;
			return;
		}
		else
		if (V < N->Data)
		{
			InsertRecursively(N->Left, N, V);
		}
		else
		{
			InsertRecursively(N->Right, N, V);
		}
	}

	void PrintTreeRecursively(Node* X, int Distance)
	{
		if (X != nullptr)
		{
			PrintTreeRecursively(X->Right, Distance + 1);
			for (int i = 0; i <= Distance + 1; i++)
			{
				cout << "\t";
			}
			cout << X->Data << "-";
			if (X->color == RED)
				cout << "R";
			else
				cout << "B";
			cout << endl;
			PrintTreeRecursively(X->Left, Distance + 1);
		}
	}

	void LNR_Recursively(Node* X)
	{
		if (X != nullptr)
		{
			LNR_Recursively(X->Left);
			cout << *X;
			LNR_Recursively(X->Right);
		}
	}
	void RNL_Recursively(Node* X)
	{
		if (X != nullptr)
		{
			RNL_Recursively(X->Right);
			cout << *X;
			RNL_Recursively(X->Left);
		}
	}

	void NLR_Recursively(Node* X)
	{
		if (X != nullptr)
		{
			cout << *X;
			NLR_Recursively(X->Left);
			NLR_Recursively(X->Right);
		}
	}
	void NRL_Recursively(Node* X)
	{
		if (X != nullptr)
		{
			cout << *X;
			NRL_Recursively(X->Right);
			NRL_Recursively(X->Left);
		}
	}

	void LRN_Recursively(Node* X)
	{
		if (X != nullptr)
		{
			LRN_Recursively(X->Left);
			LRN_Recursively(X->Right);
			cout << *X;
		}
	}
	void RLN_Recursively(Node* X)
	{
		if (X != nullptr)
		{
			LRN_Recursively(X->Right);
			LRN_Recursively(X->Left);
			cout << *X;
		}
	}

	Node* SEARCH(T Value, Node* R)
	{
		while (R && Value != R->Data)
		{
			if (Value < R->Data)
				R = R->Left;
			else
				R = R->Right;
		}
		return R;
	}

	iteratorLNR min(Node *R)
	{
		if (!R->Left)
			return iteratorLNR(R);
		min(R->Left);
	}

	void DeleteDuplicates(Node *R)
	{
		if (!R)
			return;
		if (R->Count > 1)
			R->Count = 1;
		DeleteDuplicates(R->Left);
		DeleteDuplicates(R->Right);
	}

	void copyTree(Node* &Destination, Node* Source)
	{
		if (Source == nullptr)
		{
			Destination = nullptr;
		}
		else
		{
			Destination = new Node(Source->Data, Source->Parent, Source->color, Source->Count);
			copyTree(Destination->Left, Source->Left);
			copyTree(Destination->Right, Source->Right);
		}
	}

	void Clear(Node* RootNode)
	{
		if (RootNode)              // if RBT is not empty
		{
			Node *Parent = nullptr;        // Node Pointer to Store Parent 

			if (!RootNode->Parent)
			{
				Parent = RootNode->Parent; // Store Parent of RootNode
			}

			if (RootNode->Left)    // if Left Node of is not NULL
			{
				Clear(RootNode->Left);  // Destroy Left Node
				if (Parent)       // if Parent is not NULL  
					Parent->Left = nullptr;   // Store NULL in Parent
			}
			else if (RootNode->Right)       // if Right Node of is not NULL
			{
				Clear(RootNode->Right);    // Destroy Right Node
				if (Parent)                 // if Parent is not NULL  
					Parent->Right = nullptr; // Store NULL in Parent
			}

			delete RootNode;                 // Delete Current Node
			RootNode = nullptr;				// Store NULL in RootNode
		}
	}

	void RemoveDoubleBlack(Node* NTD)
	{
		if (NTD->isDoubleBlack() && NTD == Root)
		{
			NTD->DoubleBlack = false;
		}
		else
		if (NTD->isDoubleBlack() && NTD->sibling() && NTD->sibling()->color == RED)
		{
			NTD->Parent->swapColor(NTD->sibling());
			if (NTD == NTD->Parent->Left)
			{
				RotateLeft(NTD->Parent);
			}
			else
			{
				RotateRight(NTD->Parent);
			}
			RemoveDoubleBlack(NTD);
		}
		else
		if (NTD->isDoubleBlack() && (!NTD->sibling() || NTD->sibling()->color == BLACK) && (!NTD->sibling() || NTD->sibling()->isBlackChildren()))
		{
			NTD->DoubleBlack = false;
			if (!NTD->Parent || NTD->Parent->color == BLACK)
			{
				NTD->Parent->DoubleBlack = true;
				NTD->sibling()->AlterColor();
				Node* X = NTD->Parent;
				if (NTD->DeleteDoubleBlack)
				{
					if (NTD == NTD->Parent->Right)
						NTD->Parent->Right = nullptr;
					else
						NTD->Parent->Left = nullptr;
					delete NTD;
					NTD = nullptr;
				}
				RemoveDoubleBlack(X);
				return;
			}
			else
			{
				NTD->sibling()->AlterColor();
				NTD->Parent->color = BLACK;
			}

			if (NTD->DeleteDoubleBlack)
			{
				if (NTD == NTD->Parent->Right)
					NTD->Parent->Right = nullptr;
				else
					NTD->Parent->Left = nullptr;
				delete NTD;
				NTD = nullptr;
			}
			return;
		}
		else
		if (NTD->isDoubleBlack() && NTD->sibling() && NTD->sibling()->color == BLACK && (!NTD->sibling()->isSameChildren() || NTD->sibling()->isBothChildrenRed()))
		{
			if (!NTD->sibling()->isBothChildrenRed())
			{
				if (NTD->Parent->isBlackRightLineChild(NTD->sibling()) && NTD->Parent->isRedRightTriangleChild(NTD->sibling()))
				{
					NTD->sibling()->swapColor(NTD->Parent->Right->Left);
					Node* X = NTD->sibling();
					RotateRight(X);
				}
				else
				if (NTD->Parent->isBlackLeftLineChild(NTD->sibling()) && NTD->Parent->isRedLeftTriangleChild(NTD->sibling()))
				{
					NTD->sibling()->swapColor(NTD->Parent->Left->Right);
					Node* X = NTD->sibling();
					RotateLeft(X);
				}
			}

			if (NTD->sibling()->color == BLACK && NTD->Parent->isRedRightLineChild(NTD->sibling()))
			{
				NTD->Parent->swapColor(NTD->sibling());
				NTD->sibling()->Right->color = BLACK;
				RotateLeft(NTD->Parent);
				NTD->DoubleBlack = false;

			}
			else
			if (NTD->sibling()->color == BLACK && NTD->Parent->isRedLeftLineChild(NTD->sibling()))//*
			{
				NTD->Parent->swapColor(NTD->sibling());
				NTD->sibling()->Left->color = BLACK;
				RotateRight(NTD->Parent);
				NTD->DoubleBlack = false;

			}

			if (NTD->DeleteDoubleBlack)
			{
				if (NTD == NTD->Parent->Right)
					NTD->Parent->Right = nullptr;
				else
					NTD->Parent->Left = nullptr;
				delete NTD;
				NTD = nullptr;
			}
			return;
		}
	}

	void Delete(Node *NTD)
	{
		if (NTD->HaveBothChild())
		{
			Node* X = predecessor(NTD);
			NTD->Data = X->Data;
			Delete(X);
		}
		else
		if (NTD->isOneChild())
		{
			Node* X = nullptr;
			if (NTD->Right == nullptr)
			{
				X = predecessor(NTD);
			}
			else
			{
				X = successor(NTD);
			}
			NTD->Data = X->Data;
			Delete(X);

		}
		else // Case 1: If NTD is Leaf Node and its Color is Red then simply delete it. 
		if (NTD->color == RED && NTD->isLeafNode())
		{
			if (NTD == NTD->Parent->Right)
				NTD->Parent->Right = nullptr;
			else
				NTD->Parent->Left = nullptr;
			delete NTD;
			NTD = nullptr;
			return;
		}
		else
		if (NTD->color == BLACK && NTD->isLeafNode())
		{

			if (NTD != Root)
			{
				NTD->DoubleBlack = true;
				NTD->DeleteDoubleBlack = true;
				RemoveDoubleBlack(NTD);
			}
			return;
		}
	}

	void SaveRBT(Node *Root, ofstream& fout)
	{
		if (Root != NULL)
		{
			fout << Root->Data << " ";
			if (Root->Left)
			{
				SaveBST(Root->Left, fout);
			}
			if (Root->Right)
			{
				SaveBST(Root->Right, fout);
			}
		}
		else return;
	}

public:
	RBT()
	{
		Root = nullptr;
		size = 0;
	}

	RBT(const RBT<T> &RBT_B)
	{
		if (RBT_B.Root == nullptr)
		{
			this->Root = nullptr;
		}
		else
		{
			copyTree(this->Root, RBT_B.Root);
		}
	}

	void Insert(T Value)
	{
		InsertRecursively(Root, nullptr, Value);
	}
	//InOrder
	void Print_LNR()
	{
		LNR_Recursively(Root);
	}
	void Print_RNL()
	{
		RNL_Recursively(Root);
	}
	//PreOrder
	void Print_NLR()
	{
		NLR_Recursively(Root);
	}
	void Print_NRL()
	{
		NRL_Recursively(Root);
	}
	//PostOrder
	void Print_LRN()
	{
		LRN_Recursively(Root);
	}
	void Print_RLN()
	{
		RLN_Recursively(Root);
	}

	//Print Tree in Tree Order
	void PrintTree()
	{
		int Distance = 0;
		PrintTreeRecursively(Root, Distance);
	}

	iteratorLNR TREE_SEARCH(T Value)
	{
		return iteratorLNR(SEARCH(Value, Root));
	}

	iteratorLNR ParentOfNode(iteratorLNR i)
	{
		return iteratorLNR(SEARCH(*i, Root)->Parent);
	}
	
	void DeleteAllDuplicate()
	{
		DeleteDuplicates(Root);
	}

	void destroyTree()
	{
		if (Root)
		{
			Clear(Root);
			Root = nullptr;
		}
	}

	RBT& operator= (const RBT &B)
	{
		copyTree(this->Root, B.Root);
	}

	void Delete(T Value)
	{
		Node* NTD = SEARCH(Value, Root); //Node To Delete
		if (NTD == Root && !NTD->Right && !NTD->Left)
		{
			delete NTD;
			NTD = nullptr;
			Root = nullptr;
		}
		else
		{
			if (NTD)
				Delete(NTD);
		}
	}

	void SaveBST(string FileName)
	{
		ofstream fout(FileName);
		SaveBST(this->Root, fout);
		fout.close();
	}

	void LoadBST(string FileName)
	{
		ifstream fin(FileName);
		T Value;
		while (fin >> Value)
		{
			this->Insert(Value);
		}
	}

	//Node* DeleteValuesGreaterThenX(Node* N,T X)
	//{
	//	if (N == nullptr)
	//	{
	//		return N;
	//	}
	//	if (N->Data > X)
	//	{
	//		Node* L = N->Left;
	//		//cout << N->Data << " ";
	//		Delete(N->Data);
	//		return L;
	//	}
	//	N->Left = DeleteValuesGreaterThenX(N->Left, X);
	//	N->Right = DeleteValuesGreaterThenX(N->Right, X);
	//	return N;
	//}

	//void DeleteValuesGreaterThenX(T X)
	//{
	//	DeleteValuesGreaterThenX(Root, X);
	//}
	iteratorLNR begin()
	{
		return iteratorLNR(min(Root));
	}
	iteratorLNR end()
	{
		return nullptr;
	}
	~RBT()
	{
		destroyTree();
	}
};

