#include <string>
#include "BinaryTree.h"
#include "MyRectangle.h"
#include "Connect.h"

int parent=0;
int child=0;
int parentC = 0;
int childC = 0;
int i = 22;
int j = 17;


BinaryTree::BinaryTree()
{

}

void BinaryTree::SetRoot(int v, int x, int y)
{
	root = new Node(v, x, y);
}

BinaryTree::BinaryTree(int v, int x, int y)
{
	SetRoot(v, x, y);
}

void BinaryTree::PrintingInfo()
{
	gotoxy(0, 1);
	cout << "Value of Parent Nodes: ";
	gotoxy(0, 2);
	cout << "Value of Child Nodes: ";
	gotoxy(0, 3);
	cout << "Number of Parent nodes: " << parentC;
	cout << endl;
	cout << "Number of Child nodes: " << childC;
	cout << endl;


	parentC = 0;
	childC = 0;
	i = 22;
	j = 17;


}

void BinaryTree::PrintLNR(Node* ptr)
{

	if (ptr->left != nullptr)
		PrintLNR(ptr->left);
	cout << ptr->getValue();
	if (ptr->right != nullptr)
		PrintLNR(ptr->right);
}

void BinaryTree::PrintLRN(Node* ptr)
{
	if (ptr->left != nullptr)
		PrintLRN(ptr->left);
	if (ptr->right != nullptr)
		PrintLRN(ptr->right);
	cout << ptr->getValue();
}

void BinaryTree::PrintNLR(Node* ptr)
{
	cout << ptr->getValue();
	if (ptr->left != nullptr)
		PrintNLR(ptr->left);
	if (ptr->right != nullptr)
		PrintNLR(ptr->right);
}




void BinaryTree::Insert(int val)
{
	InsertAt(root, val,0);
//	cout << parent;
	if (parent == 1)
	{
		parentC = parentC + parent;
	}

	parent = 0;


}


void BinaryTree::InsertAt(Node* n, int val, int level)
{
	if (n == nullptr) //checks if root is null
	{
		root = new Node(val, x, y);


	}
	else if (val < n->getValue()) //if inserted value is less than the root
	{
		if (n->left != nullptr) //checks the left is null and recurses until it is 
		{
			level++;
			InsertAt(n->left, val, level);
			
		}
		else // creates left node
		{
			level++;

			int ycalc, xcalc;
			xcalc = n->x - (XPADDING -  (level * 3));
			ycalc = root->y + (level * 5);
			Node* t;
			t = new Node(val,xcalc,ycalc);
			n->left = t;


			if (n->left != nullptr)
			{
				childC++;
				gotoxy(i, 2);
				cout << n->left->getValue() << " ";

				if ((n != root)&&(n->right == nullptr))
				{
					gotoxy(j, 1);
					parent++;
					cout << n->getValue() << " ";
				}
			}
			i = i + 3;
			j = j + 3;

		}
	}
	else if (val > n->getValue()) //if inserted value is greater than the root
	{
		if (n->right != nullptr) //checks the right is null and recurses until it is (keeps going to right) 
		{
			level++;
			InsertAt(n->right, val, level);

		}
		else // creates right node
		{
			level++;
			int ycalc, xcalc;
			xcalc = n->x + (XPADDING - (level * 3));
			ycalc = root->y + (level * 5);
			Node* t;
			t = new Node(val, xcalc, ycalc);
			n->right = t;


			if (n->right != nullptr)
			{
				childC++;
				gotoxy(i, 2);
				cout << n->right->getValue() << "";
				if ((n != root)&&(n->left==nullptr))
				{
					parent++;
					gotoxy(j, 1);
					cout << n->getValue() << " ";
				}
			}


			i = i + 3;
			j = j + 3;


		}
	}




}

void BinaryTree::PrintTree()
{
	PrintAt(root);
}

void BinaryTree::PrintAt(Node *n, int xParent, int yParent)
{
	if (n == root)
	{
		n->setForeGroundAndBackGroundColor(10, 10);
	}

	else if (n->left != nullptr || n->right != nullptr)
	{
		n->setForeGroundAndBackGroundColor(12, 12);
	}
	else if (n->left == nullptr || n->right == nullptr)
	{
		n->setForeGroundAndBackGroundColor(14, 14);
	}

	string value;
	value = to_string(n->getValue());
	MyRectangle box;
	box.DrawSkelaton(n->x - 3, n->y-3, BOXWIDTH, BOXHEIGHT, value);
	
	// if the child has a parent, connect it to parent
	if (xParent != -1)
	{
		int x1, y1, // current child Axis
			x2, y2; // parent Axis
		x1 = n->x;
		y1 = n->y;
		x2 = xParent;
		y2 = yParent;

		Connect C;
		C.Link(x2, y2, x1, y1-BOXHEIGHT-1);
		// display up connector
		gotoxy(x1, y1 - BOXHEIGHT - 1);
	//	setcolor(14);
		cout << char(193);
		gotoxy(x2, y2-1);
	//	setcolor(12);
		cout << char(194);
//		setcolor(10);
	}



	/*gotoxy(n->x, n->y);
	cout << n->getValue();*/
	if (n->right != nullptr)
	{
		PrintAt(n->right,n->x,n->y);
	}
	if (n->left != nullptr)
	{
		PrintAt(n->left, n->x, n->y);
	}


}

void BinaryTree::DeleteTree()
{
	DeleteTreeAt(root);
	root = nullptr;
}

void BinaryTree::DeleteTreeAt(Node* n)
{
	if (n == nullptr)
		return;
	if (n->left != nullptr)
		DeleteTreeAt(n->left);
	if (n->right != nullptr)
		DeleteTreeAt(n->right);
	delete n;
}

bool BinaryTree::IsFull()
{
	return IsFullCalc(root);
}

bool BinaryTree::IsFullCalc(Node* ptr)
{
	if (ptr == nullptr)
		return true;
	if ((ptr->left == nullptr && ptr->right != nullptr) ||
		(ptr->left != nullptr && ptr->right == nullptr))
	{
		return false && IsFullCalc(ptr->right) && IsFullCalc(ptr->right);
	}
	else
		return true && IsFullCalc(ptr->right) && IsFullCalc(ptr->left);
}

bool BinaryTree::IsComplete()
{
	int  hasLeftOnly = 0;  // 0 no left found,  1: at least 1 left found  2: right found
	bool x = IsCompleteCalc(root, &hasLeftOnly);
	if (hasLeftOnly == 2)
		return false;
	else if (x == true && hasLeftOnly == 1)
		return true;
}

bool BinaryTree::IsCompleteCalc(Node* ptr, int* hasLeft)
{
	if (ptr == nullptr)
		return true;

	if (ptr->right != nullptr && ptr->left == nullptr)
		*hasLeft = 2;
	if (ptr->right == nullptr && ptr->left != nullptr)
	{
		if (*hasLeft != 2)
			*hasLeft = 1;
	}
	if (ptr->right != nullptr && ptr->left == nullptr)
	{
		return false;
	}
	return IsCompleteCalc(ptr->right, hasLeft);
	return IsCompleteCalc(ptr->left, hasLeft);
}

