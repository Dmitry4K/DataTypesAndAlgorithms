#include<vld.h>
//#include<random>
#include<iostream>
#include<fstream>
#include<ctype.h>
#include<string.h>

template<typename T, int P> class BTree {
	template<typename, int> struct BTreeNode {
		int n;//n кол-во ключей в узле
		T* keys;//упорядоченные n ключей
		BTreeNode<T, P>** nodes;//n+1 указателей на след узлы
		bool leaf; //является ли узел листом 
		BTreeNode() : n(0), leaf(true) {
			keys = new T[2 * P - 1];
			nodes = new BTreeNode<T, P> * [2 * P];
			for (int i = 0; i < 2 * P; ++i)
				nodes[i] = nullptr;
		}
		~BTreeNode() {
			if (keys) {
				delete[] keys;
				keys = nullptr;
			}
			if (nodes) {
				delete[] nodes;
				nodes = nullptr;
			}
			n = 0;
		}
		T* BTreeSearch(T k) {
			if (this) {
				int i = 0;
				while ((i < n) && (k > keys[i])) {
					++i;
				}
				if ((i < n) && k == keys[i]) {
					return (keys + i);
				}
				if (leaf) {
					return nullptr;
				}
				else {
					return nodes[i]->BTreeSearch(k);
				}
			}
			else
				return nullptr;
		}
		void BTreeSplitChild(BTreeNode<T, P>* y, int i) {
			BTreeNode<T, P>* z = new BTreeNode<T, P>();
			z->leaf = y->leaf;
			z->n = P - 1;
			for (int j = 0; j < P - 1; ++j) {
				z->keys[j] = y->keys[j + P];
			}
			if (!(y->leaf)) {
				for (int j = 0; j < P; ++j) {
					z->nodes[j] = y->nodes[j + P];
				}
			}
			y->n = P - 1;
			for (int j = n; j >= i + 1; --j) {
				nodes[j + 1] = nodes[j];
			}
			nodes[i + 1] = z;
			for (int j = n - 1; j >= i; --j) {
				keys[j + 1] = keys[j];
			}
			keys[i] = y->keys[P - 1];
			++n;
		}
		void BTreeInsertNonfull(T k) {
			int i = n - 1;
			if (leaf) {
				while ((i >= 0) && (k < keys[i])) {
					keys[i + 1] = keys[i];
					--i;
				}
				keys[i + 1] = k;
				++n;
			}
			else {
				while ((i >= 0) && (k < keys[i])) {
					--i;
				}
				++i;
				if (nodes[i]->n == (2 * P - 1)) {
					BTreeSplitChild(nodes[i], i);
					if (k > keys[i]) {
						++i;
					}
				}
				nodes[i]->BTreeInsertNonfull(k);
			}
		}
		int BTreeFindKey(T k) {
			int index = 0;
			while (index < n && keys[index] < k) {
				++index;
			}
			return index;
		}
		void BTreeDeleteFromLeaf(int index) {
			for (int i = index + 1; i < n; ++i) {
				keys[i - 1] = keys[i];
			}
			--n;
		}
		void BTreeDeleteFromNonLeaf(int index) {
			T k = keys[index];
			if (nodes[index]->n >= P) {
				T pred = BTreeNodeGetPred(index);
				keys[index] = pred;
				nodes[index]->BTreeDeleteNode(pred);
			}
			else if (nodes[index + 1]->n >= P) {
				T succ = BTreeNodeGetSucc(index);
				keys[index] = succ;
				nodes[index + 1]->BTreeDeleteNode(succ);
			}
			else {
				BTreeMerge(index);
				nodes[index]->BTreeDeleteNode(k);
			}
		}
		T BTreeNodeGetPred(int index) {
			BTreeNode<T, P>* current = nodes[index];
			while (!current->leaf) {
				current = current->nodes[current->n];
			}
			return current->keys[current->n - 1];
		}
		T BTreeNodeGetSucc(int index) {
			BTreeNode<T, P>* current = nodes[index + 1];
			while (!current->leaf) {
				current = current->nodes[0];
			}
			return current->keys[0];
		}
		void Fill(int index) {
			if (index != 0 && nodes[index - 1]->n >= P) {
				BTreeBorrowFromPrev(index);
			}
			else if (index != n && nodes[index + 1]->n >= P) {
				BTreeBorrowFromNext(index);
			}
			else {
				if (index != n) {
					BTreeMerge(index);
				}
				else {
					BTreeMerge(index - 1);
				}
			}
		}
		void BTreeBorrowFromPrev(int index) {
			BTreeNode<T, P>* child = nodes[index];
			BTreeNode<T, P>* sibling = nodes[index - 1];
			for (int i = child->n - 1; i >= 0; --i) {
				child->keys[i + 1] = child->keys[i];
			}
			if (!child->leaf) {
				for (int i = child->n; i >= 0; --i) {
					child->nodes[i + 1] = child->nodes[i];
				}
			}
			child->keys[0] = keys[index - 1];
			if (!child->leaf) {
				child->nodes[0] = sibling->nodes[sibling->n];
			}
			keys[index - 1] = sibling->keys[sibling->n - 1];
			child->n += 1;
			sibling->n -= 1;
		}
		void BTreeBorrowFromNext(int index) {
			BTreeNode<T, P>* child = nodes[index];
			BTreeNode<T, P>* sibling = nodes[index + 1];
			child->keys[child->n] = keys[index];
			if (!child->leaf) {
				child->nodes[child->n + 1] = sibling->nodes[0];
			}
			keys[index] = sibling->keys[0];
			for (int i = 1; i < sibling->n; ++i) {
				sibling->keys[i - 1] = sibling->keys[i];
			}
			if (!sibling->leaf) {
				for (int i = 1; i <= sibling->n; ++i) {
					sibling->nodes[i - 1] = sibling->nodes[i];
				}
			}
			child->n += 1;
			sibling->n -= 1;
		}
		void BTreeMerge(int index) {
			BTreeNode<T, P>* child = nodes[index];
			BTreeNode<T, P>* sibling = nodes[index + 1];
			child->keys[P - 1] = keys[index];
			for (int i = 0; i < sibling->n; ++i) {
				child->keys[i + P] = sibling->keys[i];
			}
			if (!child->leaf) {
				for (int i = 0; i <= sibling->n; ++i) {
					child->nodes[i + P] = sibling->nodes[i];
				}
			}
			for (int i = index + 1; i < n; ++i) {
				keys[i - 1] = keys[i];
			}
			for (int i = index + 2; i <= n; ++i) {
				nodes[i - 1] = nodes[i];
			}
			child->n += sibling->n + 1;
			--n;
			delete sibling;
			sibling = nullptr;
		}
		void BTreeDeleteNode(T k) {
			int index = BTreeFindKey(k);
			if (index < n && keys[index] == k) {
				if (leaf) {
					BTreeDeleteFromLeaf(index);//?
				}
				else {
					BTreeDeleteFromNonLeaf(index);
				}
			}
			else {
				if (leaf) {
					std::cout << "not found" << std::endl;
					return;
				}
				bool flag = ((index == n) ? true : false);
				if (nodes[index]->n < P) {
					Fill(index);//?
				}
				if (flag && index > n) {
					nodes[index - 1]->BTreeDeleteNode(k);
				}
				else {
					nodes[index]->BTreeDeleteNode(k);
				}
			}
			return;
		}
		void BTreePrint(std::ostream& out, int c) {
			for (int i = 0; i < c; ++i)
				std::cout << '\t';
			for (int i = 0; i < n; ++i) {
				out << keys[i]<< ' ' ;
			}
			out << std::endl;
			for (int i = 0; i <= n; ++i) {
				if (nodes[i]) {
					nodes[i]->BTreePrint(out, c + 1);
				}
			}
		}
		void BTreeDestroy() {
			for (int i = 0; i <= n; ++i) {
				if (nodes[i]) {
					nodes[i]->BTreeDestroy();
					delete nodes[i];
					nodes[i] = nullptr;
				}
			}
		}
		
		void BTreeLoad(std::fstream& in) {
			in.read((char*)&(this->n), sizeof(int));
			in.read((char*)&(this->leaf), sizeof(bool));
			for (int i = 0; i < n; ++i) {
				in.read((char*)&(this->keys[i]), sizeof(T));
			}
			if(!leaf){
				for (int i = 0; i <= n; ++i) {
					nodes[i] = new BTreeNode<T, P>();
					nodes[i]->BTreeLoad(in);
				}
			}
		}
		void BTreeSave(std::fstream& out) {
			out.write((char*)&(this->n), sizeof(int));
			out.write((char*)&(this->leaf), sizeof(bool));
			for (int i = 0; i < n; ++i) {
				out.write((char*)&(this->keys[i]), sizeof(T));
			}
			if (!leaf) {
				for (int i = 0; i <= n; ++i) {
					nodes[i]->BTreeSave(out);
				}
			}
		}
	};
public:
	BTreeNode<T, P>* root;
public:
	BTree() {
		root = new BTreeNode<T, P>();
	}
	~BTree() {
		if (root) {
			root->BTreeDestroy();
			delete root;
			root = nullptr;
		}
	}
	T* BTreeSearch(T k) {
		return root->BTreeSearch(k);
	}
	void BTReeInsert(T k) {
		if (!root)
			root = new BTreeNode<T, P>();
		if (root->n == (2 * P - 1)) {
			BTreeNode<T, P>* s = new BTreeNode<T, P>();
			s->leaf = false;
			s->nodes[0] = root;
			s->BTreeSplitChild(root, 0);
			root = s;
			root->BTreeInsertNonfull(k);
		}
		else {
			root->BTreeInsertNonfull(k);
		}
	}
	void BTreeDeleteNode(T k) {
		if (!root) {
			std::cout << "empty\n";
			return;
		}
		root->BTreeDeleteNode(k);
		if (root->n == 0) {
			BTreeNode<T, P>* tmp = root;
			if (root->leaf) {
				root = nullptr;
			}
			else {
				root = root->nodes[0];
			}
			delete tmp;
		}
	}
	void BTreePrint(std::ostream& out) {
		if (root)
			root->BTreePrint(out, 0);
	}
	void BTreeSave(std::fstream& out) {
		if (root) {
			root->BTreeSave(out);
		}
	}
	void BTreeLoad(std::fstream& in) {
		root->BTreeDestroy();
		delete root;
		root = new BTreeNode<T, P>();
		root->BTreeLoad(in);
	}
};
struct KeyValue {
	char key[257];
	unsigned long long value;
	friend bool operator>(const KeyValue& left, const KeyValue& right);
	friend bool operator<(const KeyValue& left, const KeyValue& right);
	friend bool operator==(const KeyValue& left, const KeyValue& right);
	friend bool operator>=(const KeyValue& left, const KeyValue& right);
	friend bool operator<=(const KeyValue& left, const KeyValue& right);
	void toLower() {
		for (int i = 0; i < 256; ++i) {
			key[i] = (char)tolower(key[i]);
		}
	}
};

bool operator>(const KeyValue& left, const KeyValue& right) {
	return (strcmp(left.key, right.key) > 0 ? true : false);
}
bool operator<(const KeyValue& left, const KeyValue& right) {
	return (strcmp(left.key, right.key) < 0 ? true : false);
}
bool operator==(const KeyValue& left, const KeyValue& right) {
	return (strcmp(left.key, right.key) == 0 ? true : false);
}
bool operator>=(const KeyValue& left, const KeyValue& right) {
	return (strcmp(left.key, right.key) >= 0 ? true : false);
}
bool operator<=(const KeyValue& left, const KeyValue& right) {
	return (strcmp(left.key, right.key) <= 0 ? true : false);
}
int main() {
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	BTree<KeyValue, 50> btree;
	KeyValue buffer;
	while (std::cin >> buffer.key) {
		if (buffer.key[0] == '+') {
			std::cin >> buffer.key >> buffer.value;
			buffer.toLower();
			if (btree.BTreeSearch(buffer)) {
				std::cout << "Exist\n";
				continue;
			}
			btree.BTReeInsert(buffer);
			std::cout << "OK\n";
		}
		else if (buffer.key[0] == '-') {
			std::cin >> buffer.key;
			buffer.toLower();
			if (!btree.BTreeSearch(buffer)) {
				std::cout << "NoSuchWord\n";
				continue;
			}
			btree.BTreeDeleteNode(buffer);
			std::cout << "OK\n";
		}
		else if (buffer.key[0] == '!') {
			std::cin >> buffer.key;
			if (strcmp(buffer.key, "Load") == 0) {
				std::cin >> buffer.key;
				std::fstream file(buffer.key, std::ios::in | std::ios::binary);
				if (!file.is_open())
					std::cout << "File is not opened";
				btree.BTreeLoad(file);
				std::cout << "OK\n";
			}
			else if (strcmp(buffer.key, "Save") == 0) {
				std::cin >> buffer.key;
				std::fstream file(buffer.key, std::ios::binary | std::ios::out);
				file.sync_with_stdio(false);
				btree.BTreeSave(file);
				std::cout << "OK\n";
			}
		}
		else {
			buffer.toLower();
			KeyValue* result = btree.BTreeSearch(buffer);
			if (result) {
				std::cout << "OK: " << result->value << '\n';
			}
			else {
				std::cout << "NoSuchWord\n";
			}
		}
	}
	//*/
	return 0;
}