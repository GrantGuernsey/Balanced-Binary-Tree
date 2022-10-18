#ifndef TREE
#define TREE

#include <cmath>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class Tree {
public:
	/* CONSTRUCTOR AND NODE CLASS */
	Tree() {}
	class Node {
	public:
		T data;
		Node* prev;
		Node* left;
		Node* right;

		Node(T data, Node* prev = nullptr, Node* right = nullptr, Node* left = nullptr) {
			this->data = data;
			this->prev = prev;
			this->right = right;
			this->left = left;
		}
	};

	/* DESTRUCTOR AND EMPTY TREE METHOD */
	~Tree() {
		del(root);
	}
	void emptyTree() {
		del(root);
	}


	/* SIZE METHOD */
	int size() {
		return count;
	}

	/* TREE TO ARRAY CONVERSION */
	T* getAllAscending() {
		T* list = new T[count];
		int x = 0;
		int& itr = x;

		makeInc(root, list, itr);
		return list;
	}
	T* getAllDescending() {
		T* list = new T[count];
		int x = 0;
		int& itr = x;

		makeDec(root, list, itr);
		return list;
	}

	/* DISPLAY METHODS */
	void print() {
		if (isEmpty()) {
			cout << "Empty tree" << endl << endl;
			return;
		}

		dispTree(root);
		cout << endl;
	}
	void printInc() {
		if (isEmpty()) {
			cout << "Empty tree" << endl << endl;
			return;
		}

		T* lst = this->getAllAscending();
		for (int i = 0; i < count; i++) {
			cout << lst[i] << endl;
		}
		cout << endl;
	}
	void printDec() {
		if (isEmpty()) {
			cout << "Empty tree" << endl << endl;
			return;
		}

		T* lst = this->getAllDescending();
		for (int i = 0; i < count; i++) {
			cout << lst[i] << endl;
		}
		cout << endl;
	}

	/* TREE METHODS */
	void insert(T val) {
		//Non-empty tree insertion
		bool track = true;
		if (root != nullptr) {
			Node* cur = root;
			bool running = true;

			//Search for insertion point
			while (running) {
				if (val == cur->data) {
					cur->data++;
					running = false;
					track = false;
				}
				else if (val < cur->data) {
					if (cur->left == nullptr) {
						cur->left = new Node(val, cur);
						running = false;
					}
					else cur = cur->left;
				}
				else {
					if (cur->right == nullptr) {
						cur->right = new Node(val, cur);
						running = false;
					}
					else cur = cur->right;
				}
			}

			//Height call if the runHeight flag is true -> false for rebuilding subtrees
			if (runHeight) height(root, nullptr);
		}

		//Empty tree insertion
		else {
			root = new Node(val, nullptr);
		}

		//Updates count if the inserted node was unique and if the runHeight flag is enabled
		if (track && runHeight) {
			count += 1;
		}
	}
	Node* remove(T trgt) {
		/* CASE 0: Tree is empty */
		if (isEmpty()) throw "Empty tree";
		Node* cur = root;
		Node* end = nullptr;

		//Look for trgt
		while (cur != nullptr && cur->data != trgt) {
			if (trgt < cur->data) {
				cur = cur->left;
			}
			else cur = cur->right;
		}

		/* CASE 1: Trgt not found */
		if (cur == nullptr) return nullptr;

		//Locate smallest value larger than trgt
		else if (cur->right != nullptr) {
			end = cur->right;

			//Go as far left as possible
			while (end->left != nullptr) {
				end = end->left;
			}

			cur->data = end->data; //Transfer values

			/* CASE 2: Right child is smallest largest node... end couldn't move left */
			//Reroute any potnetial children of smallest larget node to the previous node's right
			if (end == cur->right) cur->right = end->right;

			/* CASE 3: Right child isn't smallest largest node... end moved left */
			//Reroute any right children of smallest largest node to the previous node's left
			else end->prev->left = end->right;

			cur = end; //Have cur point to end for deletion
		}

		/* CASE 4: Trgt doesn't have right children */
		//Locate largest value smaller than trgt
		else if (cur->left != nullptr) {
			end = cur->left;

			//Go as far right as possible
			while (end->right != nullptr) {
				end = end->right;
			}

			cur->data = end->data; //Transfer values

			/* CASE 5: Left child is largest smallest node... end couldn't move right */
			//Reroute any left children of largest smallest node to the previous node's left
			if (end == cur->left) cur->left = end->left;

			/* CASE 6: Left child isn't smallest largest node... end moved right */
			//Reroute any right children of largest smallest node to the previous node's right
			else end->prev->right = end->left;

			cur = end; //Have cur point to end for deletion
		}

		/* CASE 7: Trgt is a leaf and possibly root */
		else if (cur == root) root = nullptr;
		else if (cur->prev->right == cur) cur->prev->right = nullptr;
		else cur->prev->left = nullptr;

		/* Either the smallest largest or largest smallest have been found by this point, or trgt is a leaf */

		//Deletion step
		Node* res = new Node(cur->data, cur->prev, cur->right, cur->left);
		delete cur;
		count -= 1;

		//Height call if the runHeight flag is true -> false for rebuilding subtrees
		if (runHeight) height(root, nullptr);
		return res;
	}
	Node* find(T trgt) {
		/* CASE 0: Tree is empty */
		if (isEmpty()) throw "Empty tree";

		//Find trgt
		Node* cur = root;
		while (cur != nullptr && cur->data != trgt) {
			if (trgt < cur->data) {
				cur = cur->left;
			}
			else cur = cur->right;
		}

		return cur;
	}

private:
	//Shared attributes for tree
	Node* root = nullptr;
	bool runHeight = true;
	int count = 0;

	//Helper functions
	bool isEmpty() {
		return root == nullptr;
	}
	void makeInc(Node* cur, T* lst, int& idx) {
		if (cur == nullptr) return;

		makeInc(cur->left, lst, idx);

		lst[idx] = cur->data;
		idx += 1;

		makeInc(cur->right, lst, idx);
	}
	void makeDec(Node* cur, T* lst, int& idx) {
		if (cur == nullptr) return;

		makeDec(cur->right, lst, idx);

		lst[idx] = cur->data;
		idx += 1;

		makeDec(cur->left, lst, idx);
	}
	void dispTree(Node* cur) {
		//Recurion handling
		if (cur == nullptr) return;

		//Parent
		cout << "(" << cur->data << ") -> (";

		//Left
		if (cur->left != nullptr) cout << cur->left->data << ") + (";
		else cout << " ) + (";

		//Right
		if (cur->right != nullptr) cout << cur->right->data << ")" << endl;
		else cout << " )" << endl;

		dispTree(cur->left);
		dispTree(cur->right);
	}
	void del(Node* cur) {
		if (cur == nullptr) return;

		//Recurse through subtree
		del(cur->left);
		del(cur->right);

		//Dereference pointer
		if (cur != root) {
			if (cur->prev->right == cur) cur->prev->right = nullptr;
			else cur->prev->left = nullptr;
		}
		else root = nullptr;

		//Delete data pointer is refrencing
		delete cur;
	}

	void sum(Node* cur, int& itr) {
		if (cur == nullptr) return;

		itr++;
		sum(cur->left, itr);
		sum(cur->right, itr);
	}
	void build(T* x, int idx, int lBound, int rBound) {
		this->insert(x[idx]);

		int l = idx - ((idx - lBound) / 2);
		int r = idx + ((rBound - idx) / 2);

		if (r != idx && l != idx) {
			build(x, l, lBound, idx);
			build(x, r, idx, rBound);
		}
		else if (l != idx) {
			build(x, l, lBound, idx);
		}
		else if (r != idx) {
			build(x, r, idx, rBound);
		}
	}
	void balance(Node* cur) {
		//Make iterator for recursive calls
		int x = 0;
		int& itr = x;

		//Make List
		sum(cur, itr);
		int len = itr;
		T* buffer = new T[len];
		itr = 0;

		//Populate list and delete subtree
		makeInc(cur, buffer, itr);
		del(cur);

		//Rebuild list w/ height checks off
		runHeight = false;
		build(buffer, len / 2, -1, len);
		runHeight = true;
	}
	int height(Node* cur, Node* parent) {
		if (cur == nullptr) return 0;

		int l = height(cur->left, cur);
		int r = height(cur->right, cur);

		if (abs(l - r) > 1) {
			balance(cur);
			l = 0;
			r = 0;
		}

		if (l > r) return l + 1;
		return r + 1;
	}
};

#endif