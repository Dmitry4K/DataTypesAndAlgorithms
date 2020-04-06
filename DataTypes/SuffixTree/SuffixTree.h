#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<set>
#include<limits>
#include<map>
#include<algorithm>

const char TERMINATE_SYMBOL = '$';
																		//узел суффиксного дерева
struct SuffixTreeNode {
	std::pair<std::string::iterator, std::string::iterator> subString;														//пара - итераторы на начало и конец подстроки
	std::map<char, SuffixTreeNode*> nodes;																					//дочерние узлы (map - для быстрого перехода по ним)
	SuffixTreeNode* parent;																									//суффиксная ссылка
	SuffixTreeNode* suffixRef = nullptr;																					//указатель на строку, которую поддерживает узел и дерево
	std::string* str;
	bool isBlank = false;
	bool isRoot = false;
	SuffixTreeNode(std::string* str);																						//конструктор для blank
	SuffixTreeNode(std::string* str, std::string::iterator first, std::string::iterator second, SuffixTreeNode* parent);	//конструктор для обычного узла
	~SuffixTreeNode();
	int length();																											//возвращает длину текущего ребра
	int length(std::string::iterator position);																				//возвращает длину текущего ребра до заданной позиции
	void BuildArrayDFS(std::vector<int>& res, int len);																		//дочерняя функция для потсроения суффиксного массива								
	bool isExist(std::string& str, std::string::iterator cur);
	friend SuffixTree;
};
class SuffixTree {
private:
	SuffixTreeNode* root;
	SuffixTreeNode* blank;
	std::string str;
	std::vector<int> suffixArray;
	std::vector<int> LCP;
public:
	SuffixTree(std::string newStr);
	void BuildTree();
	void BuildArray();
	void BuildLCP();
	std::vector<int> Search(std::string& p);
	bool isExist(std::string& str);
	~SuffixTree();
	friend SuffixTreeNode;
};

struct SuffixTreeActivePoint {
	SuffixTreeNode* activePoint;
	SuffixTreeNode* makeSR;
	SuffixTreeNode* root;
	SuffixTreeNode* blank;
	int len = 0;
	int rem = 0;
	std::string::iterator edge;
	std::string* str;
	SuffixTreeActivePoint(SuffixTreeNode* startPoint, SuffixTreeNode* root, SuffixTreeNode* blank, std::string* s);
	void goTo(SuffixTreeNode* node, std::string::iterator c);
	SuffixTreeNode* getPoint();
	void addSufRef(SuffixTreeNode* node);
};
