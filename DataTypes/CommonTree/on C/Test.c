#include<stdio.h>

#include"common_tree.h"

int main() {
	cTree* ctree = nullptr;
	ctree = cTreeCreate(0);
	cTreeAddNode(ctree, 0, 1);
	cTreeAddNode(ctree, 0, 2);
	cTreeAddNode(ctree, 1, 3);
	cTreeAddNode(ctree, 1, 4);
	cTreeAddNode(ctree, 2, 5);
	cTreePrint(ctree);
	//cNode* res = cTreeFindNodeByKey(ctree->root, 2);
	//std::cout << res->key;
	cTreeDeleteNode(ctree, 2);
	printf("_---------------_\n");
	cTreePrint(ctree);
	cTreeDestroy(ctree);
	cTreePrint(ctree);
	system("pause");
	return 0;
}
