//The most code getted from habr.com
#include<iostream>
#include<fstream>

const int VALID = 101;
const int TRASH = 0;

template<class T>
class AVLtree {
public:
	class AVLnode {
		friend class AVLtree<T>;
		T key;
		int height = 0;
		AVLnode* left = nullptr;
		AVLnode* right = nullptr;
	public:
		T GetKey() const { return key; };
	private:
		static int Height(AVLnode* p) { return (p ? p->height : 0); }
		static void  FixHeight(AVLnode* p) {
			int lh = Height(p->left);
			int rh = Height(p->right);
			p->height = (lh > rh ? lh : rh) + 1;
		}
		static AVLnode* RotateRight(AVLnode* p) {
			AVLnode* q = p->left;
			p->left = q->right;
			q->right = p;
			FixHeight(p);
			FixHeight(q);
			return q;
		}
		static AVLnode* RotateLeft(AVLnode* q) {
			AVLnode* p = q->right;
			q->right = p->left;
			p->left = q;
			FixHeight(q);
			FixHeight(p);
			return p;
		}
		static AVLnode* Balance(AVLnode* p) {
			FixHeight(p);
			if (BalanceFactor(p) == 2) {
				if (BalanceFactor(p->right) < 0) {
					p->right = RotateRight(p->right);
				}
				return RotateLeft(p);
			}
			if (BalanceFactor(p) == -2)
			{
				if (BalanceFactor(p->left) > 0)
					p->left = RotateLeft(p->left);
				return RotateRight(p);
			}
			return p;
		}
		static int BalanceFactor(AVLnode* p) {
			return Height(p->right) - Height(p->left);
		}
		static AVLnode* Insert(AVLnode* p, T k) {
			if (!p) return new AVLnode(k);
			if (k < p->key)
				p->left = Insert(p->left, k);
			else
				p->right = Insert(p->right, k);
			return Balance(p);
		}
		static AVLnode* FindMin(AVLnode* p) {return (p->left ? FindMin(p->left) : p);}
		static AVLnode* RemoveMin(AVLnode* p) { 
			if (p->left == nullptr) {
				return p->right;
			}
			p->left = RemoveMin(p->left);
			return Balance(p);
		}
		static AVLnode* Remove(AVLnode* p, T k) {
			if (!p) return nullptr;
			if (k < p->key) {
				p->left = Remove(p->left, k);
			}
			else if (k > p->key) {
				p->right = Remove(p->right, k);
			}
			else { //found key
				AVLnode* q = p->left;
				AVLnode* r = p->right;
				delete p;
				if (!r) return q;
				AVLnode* min = FindMin(r);
				min->right = RemoveMin(r);
				min->left = q;
				return Balance(min);
			}
			return Balance(p);
		}
		static AVLnode* Find(AVLnode* p, T k) {
			if (!p) return nullptr;
			if (k < p->key) return Find(p->left, k);
			else if (k > p->key) return Find(p->right, k);
			else return p;
		}
		static void Save(AVLnode* p, std::fstream& out) {
			if (p) {
				out.write((char*)&VALID, sizeof(int));
				out.write((char*)&(p->height), sizeof(int));
				out.write((char*)&(p->key), sizeof(T));
				Save(p->left, out);
				Save(p->right, out);
			}
			else {
				out.write((char*)&TRASH, sizeof(int));
			}
		}
		static AVLnode*  Load(AVLnode* p, std::fstream& in) {
			int check;
			in.read((char*)&check, sizeof(int));
			if (check == VALID) {
				p = new AVLnode();
				in.read((char*)&(p->height), sizeof(int));
				in.read((char*)&(p->key), sizeof(T));
				p->left = Load(p->left, in);
				p->right = Load(p->right, in);
			}
			else {
				p = nullptr;
			}
			return p;
		}
		static void Destroy(AVLnode* p) {
			if (p) {
				Destroy(p->left);
				Destroy(p->right);
				delete p->left;
				delete p->right;
				p->left = nullptr;
				p->right = nullptr;
			}
		}
		static int Size(AVLnode* p) {
			if (p) {
				int ls = Size(p->left);
				int rs = Size(p->right);
				return ls + rs + 1;
			}
			else {
				return 0;
			}
		}
		static void Print(AVLnode* p, std::ostream& out, int l) {
			if (p) {
				if (p->right)
					Print(p->right, out, l + 1);
				for (int i = 0; i < l; ++i) {
					out << '\t';
				}
				out << p->key << std::endl;
				if (p->left)
					Print(p->left, out, l + 1);
			}
		}
	private :
		AVLnode(T k) { key = k; left = right = nullptr; height = 1; }
		AVLnode() {}
	public:
		AVLnode* GetRight() { return right; }
		AVLnode* GetLeft() { return left; }
	};


	AVLnode* root = nullptr;

public:
	bool Insert(T k) {return (Find(k) == nullptr ? (root = AVLnode::Insert(root, k), true) : false);}
	bool Delete(T k) {return (Find(k) == nullptr ? false : (root = AVLnode::Remove(root, k), true));}
	AVLnode* Find(T k) { return (root ? AVLnode::Find(root, k) : nullptr); }
	void Save(std::fstream& out) {
		AVLnode::Save(root, out);
	}
	void Load(std::fstream& in) {
		if (in.peek() == EOF)
			return;
		Destroy();
		root = AVLnode::Load(root, in);
	}
	void Destroy() {
		if (root) {
			AVLnode::Destroy(root);
			delete root;
			root = nullptr;
		}
	}
	int Size() {
		return AVLnode::Size(root);
	}
	void Print(std::ostream& out) {
		AVLnode::Print(root, out, 0);
	}
	~AVLtree() {
		Destroy();
		delete root;
	}
};
