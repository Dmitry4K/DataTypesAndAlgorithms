int main() {
	AVLtree<int> tree;
	tree.Insert(0);
	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);
	tree.Insert(6);
	tree.Insert(7);
	tree.Print(std::cout);
	tree.Delete(3);
	tree.Print(std::cout);
	return 0;
}

/* Console view
----------------------------
                        7
                6
        5
                4
3
                2
        1
                0
                7
        6
                5
4
                2
        1
                0
----------------------------
*/
