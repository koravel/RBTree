#include "stdafx.h"

int main()
{
	//Node* root = createRoot();
    return 0;
}

struct Node
{
	Node* parent;
	Node* left_child;
	Node* right_child;
	bool isBlack;
	int data;
};

Node* createLeaf(Node* _parent)
{
	Node* node;
	node->parent = _parent;
	node->left_child = NULL;
	node->right_child = NULL;
	node->isBlack = true;

	return node;
}

void modifyLeafToNode(Node* node, int _data)
{
	node->data = _data;
	node->left_child = createLeaf(node);
	node->right_child = createLeaf(node);
	node->isBlack = false;
}
void modifyNodeToLeaf(Node* node)
{
	node->data = NULL;
	node->left_child = NULL;
	node->right_child = NULL;
	node->isBlack = true;
}

Node* getUncle(Node* node)
{
	Node* parent = node->parent;
	Node* grandparent = parent->parent;

	if (parent == grandparent->left_child) return grandparent->right_child;
	else return grandparent->left_child;
}

Node* createRoot()
{
	return createLeaf(NULL);
}

bool isLeftChild(Node* node)
{
	if (node->parent->left_child == node) return true;
	return false;
}

bool isRightChild(Node* node)
{
	if (node->parent->right_child == node) return true;
	return false;
}

bool isHasChildren(Node* node)
{
	if (isLeaf(node->left_child) && isLeaf(node->right_child)) return false;
	return true;
}

bool isHasLeftChild(Node* node)
{
	if (isLeaf(node->left_child)) return false;
	return true;
}

bool isHasRightChild(Node* node)
{
	if (isLeaf(node->right_child)) return false;
	return true;
}

void leftRotate(Node* node)
{
	Node* parent = node->parent;
	Node* rightChild = node->right_child;
	Node* leftGrandChild = node->right_child->left_child;

	rightChild->parent = parent;
	node->parent = rightChild;

	if (parent->left_child == node) parent->left_child = rightChild;
	else if (parent->right_child == node) parent->right_child = rightChild;

	leftGrandChild->parent = node;
	node->right_child = leftGrandChild;

	rightChild->left_child = node;
}

void rightRotate(Node* node)
{
	Node* parent = node->parent;
	Node* leftChild = node->left_child;
	Node* rightGrandChild = node->left_child->right_child;

	leftChild->parent = parent;
	node->parent = leftChild;

	if (parent->left_child == node) parent->left_child = leftChild;
	else if (parent->right_child == node) parent->right_child = leftChild;

	rightGrandChild->parent = node;
	node->left_child = rightGrandChild;

	leftChild->right_child = node;
}

Node* searchElement(Node* root, int _data)
{
	Node* current_node = root;
	bool endSearch = false;

	while(!endSearch)
	{
		if (current_node->data > _data)
		{
			current_node = current_node->left_child;
		}
		else if (current_node->data < _data)
		{
			current_node = current_node->right_child;
		}
		else endSearch = true;
	}

	return current_node;
}

bool isLeaf(Node* node)
{
	if (node->data == NULL && node->isBlack) return true;
	else return false;
}

Node* insertElement(Node* root, int _data)
{
	Node* node = searchElement(root, _data);
	Node* parent = node->parent;
	Node* grandparent = parent->parent;

	if (node->data == _data) return NULL;
	if (isLeaf(node))
	{
		modifyLeafToNode(node, _data);
		while(node != root && !parent->isBlack)
		{
			Node* uncle = getUncle(node);

			if (!uncle->isBlack)
			{
				uncle->isBlack = true;
				parent->isBlack = true;
				grandparent->isBlack = false;

				node = grandparent;
			}
			else
			{
				if (isLeftChild(node) && isRightChild(parent)) rightRotate(parent);

				else if (isRightChild(node) && isLeftChild(parent)) leftRotate(parent);

				parent->isBlack = true;

				if (isLeftChild(node) && isLeftChild(parent)) rightRotate(grandparent);

				else if (isRightChild(node) && isRightChild(parent)) leftRotate(grandparent);
			}
		}

		if (!root->isBlack) root->isBlack = true;
	}
}

void deleteElement(Node* root, int _data)
{
	Node* node = searchElement(root, _data);

	if (!isHasChildren(node))
	{
		modifyNodeToLeaf(node);
		return;
	}

	Node* child;

	bool haveleftChild = isHasLeftChild(node);
	bool haverightChild = isHasRightChild(node);
	bool isBlackNode = node->isBlack;

	if (haveleftChild && !haverightChild) child = node->left_child;
	else if (haverightChild && !haveleftChild) child = node->right_child;
	
	if (node->parent->left_child == node) node->parent->left_child = child;
	else if (node->parent->right_child == node) node->parent->right_child= child;

	if (haveleftChild && haverightChild)
	{
		Node* temp = node->right_child;

		while (isHasLeftChild(temp))
		{
			temp = temp->left_child;
		}

		node->data = temp->data;

		bool isTempBlack = temp->isBlack;

		modifyNodeToLeaf(temp);

		if (isTempBlack)
		{
			bool exit = false;
			while (temp->parent != NULL && temp->isBlack && !exit)
			{
				Node* brother;
				bool isBrotherRightChild = false;

				if (isLeftChild(temp)) brother = temp->parent->right_child;
				else if (isRightChild(temp))
				{
					brother = temp->parent->left_child;
					isBrotherRightChild = true;
				}

				if (brother->isBlack)
				{
					bool sameRightChilrenBlack = (isRightChild(brother) && brother->right_child->isBlack);
					bool sameLeftChilrenBlack = ((isLeftChild(brother) && brother->left_child->isBlack));

					if (brother->left_child->isBlack && brother->right_child->isBlack)
					{
						brother->isBlack = false;
						temp = brother->parent;
					}
					else if (sameLeftChilrenBlack || sameRightChilrenBlack)
					{
						brother->isBlack = false;

						if (sameRightChilrenBlack && !brother->left_child->isBlack)
						{
							brother->left_child->isBlack = true;
							rightRotate(brother);
						}
						else if (sameLeftChilrenBlack && !brother->right_child->isBlack)
						{
							brother->right_child->isBlack = true;
							leftRotate(brother);
						}
					}
					else
					{
						brother->isBlack = brother->parent->isBlack;

						brother->parent->isBlack = true;

						if (isBrotherRightChild)
						{
							brother->right_child->isBlack = true;

							leftRotate(brother->parent);
						}
						else
						{
							brother->left_child->isBlack = true;

							rightRotate(brother->parent);
						}
					}
				}
				else
				{ 
					brother->isBlack = true;
					brother->isBlack = false;


					if (isBrotherRightChild)
					{
						leftRotate(brother->parent);
					}
					else
					{
						rightRotate(brother->parent);
					}

					exit = true;
				}

				if (!temp->isBlack)
				{
					temp->isBlack = true;
				}
			}
		}
	}
}