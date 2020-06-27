//void Delete(Node *NTD)
//{
//	// Case 1: If NTD is Leaf Node and its Color is Red then simply delete it. 
//	/*if (NTD->color == RED && NTD->isLeafNode())
//	{
//		if (NTD == NTD->Parent->Right)
//			NTD->Parent->Right = nullptr;
//		else
//			NTD->Parent->Left = nullptr;
//		delete NTD;
//		NTD = nullptr;
//		return;
//	}*/
//	else //Case 2: If NTD is BLACK with one child in color RED then replace the Data of NTD with child and delete child.
//	if (!NTD->isDoubleBlack() && NTD->color == BLACK && NTD->isOneChild() && NTD->OneChild()->color == RED)
//	{
//		Node* X = NTD->OneChild();
//		NTD->Data = X->Data;
//		Delete(X);
//	}
//	/*else
//	if (NTD->HaveBothChild())
//	{
//		Node* X = predecessor(NTD);
//		NTD->Data = X->Data;
//		Delete(X);
//		return;
//	}*/
//	else // If Root is Double Black then Change it's color to single black.
//	if (NTD == Root && NTD->isDoubleBlack())
//	{
//		NTD->DoubleBlack = false;
//		return;
//	}
//	else
//	if (NTD->isDoubleBlack() && NTD->Parent->color == BLACK && NTD->sibling()->color == BLACK && !NTD->sibling()->isSameChildren())//
//	{
//		Node* X = NTD->sibling();
//		//NTD on left and sbling child on left
//		if (NTD == NTD->Parent->Left && NTD->sibling()->Left->color == RED)
//		{
//			NTD->sibling()->Left->AlterColor();
//			NTD->sibling()->AlterColor();
//			RotateRight(X);
//		}
//		else
//		if (NTD == NTD->Parent->Right && NTD->sibling()->Right && NTD->sibling()->Right->color == RED)
//		{
//			NTD->sibling()->Right->AlterColor();
//			NTD->sibling()->AlterColor();
//			RotateLeft(X);
//		}
//		if (NTD == NTD->Parent->Left && NTD->sibling()->Right && NTD->sibling()->Right->color == RED)
//		{
//			RotateLeft(NTD->Parent);
//			NTD->DoubleBlack = false;
//			NTD->GrandParent()->Right->AlterColor();
//			if (NTD == NTD->Parent->Right)
//				NTD->Parent->Right = nullptr;
//			else
//				NTD->Parent->Left = nullptr;
//			delete NTD;
//			NTD = nullptr;
//			return;
//		}
//		else
//		if (NTD == NTD->Parent->Right && NTD->sibling()->Left->color == RED)
//		{
//			RotateRight(NTD->Parent);
//			NTD->DoubleBlack = false;
//			NTD->GrandParent()->Left->AlterColor();
//			if (NTD == NTD->Parent->Right)
//				NTD->Parent->Right = nullptr;
//			else
//				NTD->Parent->Left = nullptr;
//			delete NTD;
//			NTD = nullptr;
//			return;
//		}
//
//	}
//	else //Case : If NTD is Double Black and it's Parent is Red, it's sibling is Black and color of sibling's children is also Black then Change the color of both Parent and sibling.
//	/*if (NTD->isDoubleBlack() && NTD->Parent->color == RED && NTD->sibling()->color == BLACK && NTD->sibling()->isBlackChildren())
//	{
//		NTD->DoubleBlack = false;
//		NTD->Parent->AlterColor();
//		NTD->sibling()->AlterColor();
//
//		if (NTD == NTD->Parent->Right)
//			NTD->Parent->Right = nullptr;
//		else
//			NTD->Parent->Left = nullptr;
//		delete NTD;
//		NTD = nullptr;
//		return;
//	}
//	else*/
//	if (NTD->isDoubleBlack() && NTD->sibling()->color == BLACK && !NTD->sibling()->isBlackChildren())
//	{
//		if (NTD->Parent->Left && NTD == NTD->Parent->Left)
//		{
//			NTD->sibling()->Right->AlterColor();
//			RotateLeft(NTD->Parent);
//		}
//		else
//		{
//			NTD->sibling()->Left->AlterColor();
//			RotateRight(NTD->Parent);
//		}
//		if (NTD == NTD->Parent->Right)
//			NTD->Parent->Right = nullptr;
//		else
//			NTD->Parent->Left = nullptr;
//		delete NTD;
//		NTD = nullptr;
//		return;
//	}
//	else
//	if (NTD->isDoubleBlack() && NTD->Parent->color == BLACK && NTD->sibling()->color == RED && NTD->sibling()->isBlackChildren())
//	{
//		NTD->Parent->AlterColor();
//		NTD->sibling()->AlterColor();
//		if (NTD->Parent->Left && NTD == NTD->Parent->Left)
//		{
//			RotateLeft(NTD->Parent);
//		}
//		else
//		{
//			RotateRight(NTD->Parent);
//		}
//		Delete(NTD);
//	}
//	else
//	if (NTD->isDoubleBlack() && NTD->Parent->color == BLACK && NTD->sibling()->color == BLACK && NTD->sibling()->isBlackChildren())
//	{
//		NTD->DoubleBlack = false;
//		Node *X = NTD->Parent;
//		X->DoubleBlack = true;
//		NTD->sibling()->AlterColor();
//		if (NTD == NTD->Parent->Right)
//			NTD->Parent->Right = nullptr;
//		else
//			NTD->Parent->Left = nullptr;
//		delete NTD;
//		NTD = nullptr;
//		Delete(X);
//	}
//	/*else
//	if (NTD->color == BLACK && NTD->isLeafNode())
//	{
//		NTD->DoubleBlack = true;
//		Delete(NTD);
//	}*/
//}