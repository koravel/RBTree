#pragma once

#include <iostream>
public class RBTree
{
public: struct Node
{
	Node* parent;
	Node* left_child;
	Node* right_child;
	bool isBlack;
	int* data;
};

		Node* root;
		int* null;
		Node* nullNode;

		Node* makeEmpty(Node* t)
		{
			if (t == nullNode)
				return nullNode;
			{
				makeEmpty(t->left_child);
				makeEmpty(t->right_child);
				delete t;
			}
			return nullNode;
		}

		Node* createLeaf(Node* _parent)
		{
			Node* node = new Node;
			node->parent = _parent;
			node->left_child = nullNode;
			node->right_child = nullNode;
			node->data = null;
			node->isBlack = true;

			return node;
		}

		bool isLeaf(Node* node)
		{
			if (node->data == null && node->isBlack) return true;
			else return false;
		}

		void modifyLeafToNode(Node* node, int _data)
		{
			node->data = new int;
			*(node->data) = _data;
			node->left_child = createLeaf(node);
			node->right_child = createLeaf(node);
			node->isBlack = false;
		}
		void modifyNodeToLeaf(Node* node)
		{
			node->data = null;
			node->left_child = nullNode;
			node->right_child = nullNode;
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
			return createLeaf(nullNode);
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

			if (parent != nullNode)
			{
				if (parent->left_child == node) parent->left_child = rightChild;
				else if (parent->right_child == node) parent->right_child = rightChild;
			}

			leftGrandChild->parent = node;
			node->right_child = leftGrandChild;

			rightChild->left_child = node;

			if (node == root) root = rightChild;
		}

		void rightRotate(Node* node)
		{
			Node* parent = node->parent;
			Node* leftChild = node->left_child;
			Node* rightGrandChild = node->left_child->right_child;

			leftChild->parent = parent;
			node->parent = leftChild;
			if (parent != nullNode)
			{
				if (parent->left_child == node) parent->left_child = leftChild;
				else if (parent->right_child == node) parent->right_child = leftChild;
			}

			rightGrandChild->parent = node;
			node->left_child = rightGrandChild;

			leftChild->right_child = node;

			if (node == root) root = leftChild;
		}

		Node* searchElement(int _data)
		{
			if (!isLeaf(root))
			{
				Node* current_node;

				current_node = root;

				bool endSearch = false;

				while (!endSearch)
				{
					if (current_node->data == null || *(current_node->data) == _data)
					{
						endSearch = true;
					}
					else if (*(current_node->data) > _data)
					{
						current_node = current_node->left_child;
					}
					else if (*(current_node->data) < _data)
					{
						current_node = current_node->right_child;
					}
				}
				return current_node;
			}
			else return root;
		}

		Node* insertElement(int _data)
		{
			Node* node = searchElement(_data);

			if (isLeaf(node))
			{
				modifyLeafToNode(node, _data);
				while (node != root && !node->parent->isBlack)
				{
					Node* uncle = getUncle(node);
					Node* parent = node->parent;
					Node* grandparent = node->parent->parent;

					if (!uncle->isBlack)
					{
						uncle->isBlack = true;
						node->parent->isBlack = true;
						grandparent->isBlack = false;

						node = grandparent;
					}
					else
					{
						if (isLeftChild(node) && isRightChild(parent))
						{
							rightRotate(parent);
							parent = node;
						}
						else if (isRightChild(node) && isLeftChild(parent))
						{
							leftRotate(parent);
							parent = node;
						}

						parent->isBlack = true;
						grandparent->isBlack = false;

						if (isLeftChild(node) && isLeftChild(parent)) rightRotate(grandparent);

						else if (isRightChild(node) && isRightChild(parent)) leftRotate(grandparent);
					}
				}

				if (!root->isBlack) root->isBlack = true;
			}
			else
			{
				if (*(node->data) == _data) return nullNode;
			}
		}

		void deleteElement(int _data)
		{
			Node* node = searchElement(_data);

			if (node == nullNode || (node == root && isLeaf(root))) return;
		Node* temp;

		if (!isHasChildren(node))
		{
			modifyNodeToLeaf(node);
			return;
		}

		Node* child;

		bool haveleftChild = isHasLeftChild(node);
		bool haverightChild = isHasRightChild(node);
		bool isBlackNode;

		if (haveleftChild && haverightChild)
		{
			Node* toDeleteNode = node->right_child;

			while (isHasLeftChild(toDeleteNode))
			{
				toDeleteNode = toDeleteNode->left_child;
			}

			node->data = toDeleteNode->data;
			node->right_child = toDeleteNode->right_child;
			toDeleteNode->right_child->parent = node;

			isBlackNode = toDeleteNode->isBlack;

			temp = node->right_child;
		}
		else
		{
			if (haveleftChild && !haverightChild) child = node->left_child;
			else if (haverightChild && !haveleftChild) child = node->right_child;

			if (node != root)
			{
				if (node->parent->left_child == node) node->parent->left_child = child;
				else if (node->parent->right_child == node) node->parent->right_child = child;
			}

			child->parent = node->parent;

			isBlackNode = node->isBlack;
		}

		if (isBlackNode)
		{
			bool exit = false;
			while (temp->parent != nullNode && temp->isBlack && !exit)
			{
				Node* brother;
				bool isBrotherRightChild = false;

				if (isLeftChild(temp))
				{
					brother = temp->parent->right_child;
					isBrotherRightChild = true;
				}
				else if (isRightChild(temp)) brother = temp->parent->left_child;

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

						exit = true;
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
			}			
		}
		
		if (temp->parent != nullNode)
		{
			if (!temp->isBlack)
			{
				temp->isBlack = true;
			}
		}
	}

	public: RBTree()
	{
		null = NULL;

		nullNode = NULL;

		root = createRoot();
	}

	~RBTree()
	{
		root = makeEmpty(root);
	}
};
