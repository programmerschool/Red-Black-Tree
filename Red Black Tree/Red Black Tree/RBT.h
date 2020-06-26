#pragma once
#include<iostream>
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
		}

		Node* sibling()
		{
			if (this == Parent->Right)
				return Parent->Left;
			else
			{
				return Parent->Right;
			}
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
		bool HaveBothChild()
		{
			return Right && Left;
		}
		bool isBlackChildren()
		{
			return (((!Right || Right->color == BLACK) && (!Left || Left->color == BLACK)) || ((!Left || Left->color == BLACK) && (!Right || Right->color == BLACK)));
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

	void copyTree(Node* Destination, Node* Source)
	{
		if (Source == nullptr)
		{
			Destination = nullptr;
		}
		else
		{
			Destination = new Node<T>(Source->Data, Source->Parent);
			copyTree(Destination->Left, Source->Left);
			copyTree(Destination->Right, Source->Right);
		}
	}

	void Clear(Node* RootNode)
	{
		if (RootNode)              // if BST is not empty
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

	void Delete(Node *NTD)
	{
		// Case 1: If NTD is Leaf Node and its Color is Red then simply delete it. 
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
		else //Case 2: If NTD is BLACK with one child in color RED then replace the Data of NTD with child and delete child.
		if (!NTD->isDoubleBlack() && NTD->color == BLACK && NTD->isOneChild() && NTD->OneChild()->color == RED) 
		{
			Node* X = NTD->OneChild();
			NTD->Data = X->Data;
			Delete(X);
		}
		else
		if (NTD->color == BLACK && NTD->HaveBothChild())
		{
			Node* X = predecessor(NTD);
			NTD->Data = X->Data;
			Delete(X);
			return;
		}
		else // If Root is Double Black then Change it's color to single black.
		if (NTD == Root && NTD->isDoubleBlack())
		{
			NTD->DoubleBlack = false;
			return;
		}
		else //Case : If NTD is Double Black and it's Parent is Red, it's sibling is Black and color of sibling's children is also Black then Change the color of both Parent and sibling.
		if (NTD->isDoubleBlack() && NTD->Parent->color == RED && NTD->sibling()->color == BLACK && NTD->sibling()->isBlackChildren())
		{
			NTD->DoubleBlack = false;
			NTD->Parent->AlterColor();
			NTD->sibling()->AlterColor();

			if (NTD == NTD->Parent->Right)
				NTD->Parent->Right = nullptr;
			else
				NTD->Parent->Left = nullptr;
			delete NTD;
			NTD = nullptr;
			return;
		}
		else
		if (NTD->isDoubleBlack() && NTD->Parent->color == BLACK && NTD->sibling()->color == RED && NTD->sibling()->isBlackChildren())
		{
			NTD->Parent->AlterColor();
			NTD->sibling()->AlterColor();
			if (NTD->Parent->Left && NTD == NTD->Parent->Left)
			{
				RotateLeft(NTD->Parent);
			}
			else
			{
				RotateRight(NTD->Parent);
			}
			Delete(NTD);
		}
		else
		if (NTD->isDoubleBlack() && NTD->sibling()->color == BLACK && !NTD->sibling()->isBlackChildren())
		{
			if (NTD->Parent->Left && NTD == NTD->Parent->Left)
			{
				NTD->sibling()->Right->AlterColor();
				RotateLeft(NTD->Parent);
			}
			else
			{
				NTD->sibling()->Left->AlterColor();
				RotateRight(NTD->Parent);
			}
			if (NTD == NTD->Parent->Right)
				NTD->Parent->Right = nullptr;
			else
				NTD->Parent->Left = nullptr;
			delete NTD;
			NTD = nullptr;
			return;
		}
		else
		if (NTD->isDoubleBlack() && NTD->Parent->color == BLACK && NTD->sibling()->color == BLACK && !NTD->sibling()->isSameChildren())
		{
			Node* X = NTD->sibling();
			//NTD on left and sbling child on left
			if (NTD == NTD->Parent->Left && NTD->sibling()->Left->color == RED)
			{
				NTD->sibling()->Left->AlterColor();
				NTD->sibling()->AlterColor();
				RotateRight(X);
			}
			else
			if (NTD == NTD->Parent->Right && NTD->sibling()->Right && NTD->sibling()->Right->color == RED)
			{
				NTD->sibling()->Right->AlterColor();
				NTD->sibling()->AlterColor();
				RotateLeft(X);
			}
			if (NTD == NTD->Parent->Left && NTD->sibling()->Right && NTD->sibling()->Right->color == RED)
			{
				RotateLeft(NTD->Parent);
				NTD->DoubleBlack = false;
				NTD->GrandParent()->Right->AlterColor();
				if (NTD == NTD->Parent->Right)
					NTD->Parent->Right = nullptr;
				else
					NTD->Parent->Left = nullptr;
				delete NTD;
				NTD = nullptr;
				return;
			}
			else
			if (NTD == NTD->Parent->Right && NTD->sibling()->Left->color == RED)
			{
				RotateRight(NTD->Parent);
				NTD->DoubleBlack = false;
				NTD->GrandParent()->Left->AlterColor();
				if (NTD == NTD->Parent->Right)
					NTD->Parent->Right = nullptr;
				else
					NTD->Parent->Left = nullptr;
				delete NTD;
				NTD = nullptr;
				return;
			}
			
		}
		else
		if (NTD->isDoubleBlack() && NTD->Parent->color == BLACK && NTD->sibling()->color == BLACK && NTD->sibling()->isBlackChildren())
		{
			NTD->DoubleBlack = false;
			Node *X = NTD->Parent;
			X->DoubleBlack = true;
			NTD->sibling()->AlterColor();
			if (NTD == NTD->Parent->Right)
				NTD->Parent->Right = nullptr;
			else
				NTD->Parent->Left = nullptr;
			delete NTD;
			NTD = nullptr;
			Delete(X);
		}
		else
		if (NTD->color == BLACK && NTD->isLeafNode())
		{
			NTD->DoubleBlack = true;
			Delete(NTD);
		}
	}

	void Delete(T Value)
	{
		Node* NTD = SEARCH(Value, Root); //Node To Delete
		if (NTD)
			Delete(NTD);
	}

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

