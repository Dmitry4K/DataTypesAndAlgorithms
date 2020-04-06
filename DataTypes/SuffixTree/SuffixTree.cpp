#include"SuffixTree.h"

template<class T>
void countingSort(std::vector<T>& a) {
	T maxEl = a[0];
	for (int i = 1; i < a.size(); ++i) {
		if (maxEl < a[i]) {
			maxEl = a[i];
		}
	}
	std::vector<T> c(maxEl + 1);
	for (int i = 0; i <= maxEl; ++i)
		c[i] = 0;
	for (int i = 0; i < a.size(); ++i)
		c[a[i]]++;
	for (int i = 1; i <= maxEl; ++i)
		c[i] += c[i - 1];
	std::vector<T> b(a.size());
	for (int i = a.size() - 1; i >= 0; i--) {
		c[a[i]]--;
		b[c[a[i]]] = a[i];
	}
	for (int i = 0; i < a.size(); i++)
		a[i] = b[i];
}

SuffixTree::SuffixTree(std::string newStr) {
	str = newStr + TERMINATE_SYMBOL;
	blank = new SuffixTreeNode(&str);
	blank->isBlank = true;
	root = new SuffixTreeNode(&str);
	for (char i = 'a'; i <= 'z'; ++i) {
		blank->nodes[i] = root;
	}
	blank->nodes[TERMINATE_SYMBOL] = root;
	root->suffixRef = blank;
	BuildTree();
}

void SuffixTree::BuildTree() {
	SuffixTreeActivePoint activePoint(root, root, blank, &str);
	std::string::iterator it = str.begin();
	while (it != str.end()) {
		activePoint.makeSR = root;
		++activePoint.rem;
		while (activePoint.rem > 0) {
			if (activePoint.len == 0) {
				activePoint.edge = it;
			}
			std::map<char, SuffixTreeNode*>::iterator next = activePoint.getPoint()->nodes.find(*activePoint.edge);
			if (next == activePoint.getPoint()->nodes.end()) {
				activePoint.getPoint()->nodes[*activePoint.edge] = new SuffixTreeNode(&str, it, str.end(), activePoint.getPoint());
				activePoint.addSufRef(activePoint.getPoint());
			}
			else {

				if (activePoint.len >= next->second->length(it)) {
					activePoint.goTo(next->second, it);
					continue;
				}

				if (*(next->second->subString.first + activePoint.len) == *it) {
					++activePoint.len;
					activePoint.addSufRef(activePoint.getPoint());
					break;
				}
				SuffixTreeNode* split = new SuffixTreeNode(&str, next->second->subString.first, next->second->subString.first + activePoint.len, activePoint.getPoint());
				SuffixTreeNode* newNode = new SuffixTreeNode(&str, it, str.end(), split);
				SuffixTreeNode* nextPtr = next->second;
				activePoint.getPoint()->nodes[*activePoint.edge] = split;
				split->nodes[*it] = newNode;
				nextPtr->subString.first += activePoint.len;
				split->nodes[*nextPtr->subString.first] = nextPtr;
				activePoint.addSufRef(split);
			}
			--activePoint.rem;
			if (activePoint.getPoint() == root && activePoint.len > 0) {//если AP - root или len > 0
				--activePoint.len;//уменьшаем активную длину
				activePoint.edge = it - activePoint.rem + 1; //переходим ?
			}
			else {
				activePoint.activePoint = (activePoint.getPoint()->suffixRef) ? activePoint.getPoint()->suffixRef : root; //если не в root или len = 0, то переходим по суф. ссылку, или в корень
			}
		}
		it++;
	}
}
SuffixTreeNode* SuffixTreeActivePoint::getPoint() {
	return activePoint;
}
SuffixTreeActivePoint::SuffixTreeActivePoint(SuffixTreeNode* startPoint, SuffixTreeNode* r, SuffixTreeNode* b, std::string* s) : activePoint(startPoint), root(r), blank(b), str(s) {}

void SuffixTreeActivePoint::goTo(SuffixTreeNode* node, std::string::iterator c) {
	edge += node->length(c);
	len -= node->length(c);
	activePoint = node;
}

int SuffixTreeNode::length() {
	if (isRoot) {
		return 0;
	}
	return subString.second - subString.first + 1;
}
int SuffixTreeNode::length(std::string::iterator position) {
	if (isRoot) {
		return 0;
	}
	return min(subString.second, position + 1) - subString.first;
}
void SuffixTreeActivePoint::addSufRef(SuffixTreeNode* node) {
	if (makeSR != root) {
		makeSR->suffixRef = node;
	}
	makeSR = node;
}
SuffixTreeNode::SuffixTreeNode(std::string* s) {
	str = s;
	parent = nullptr;
	isRoot = true;
}
SuffixTreeNode::SuffixTreeNode(std::string* s, std::string::iterator first, std::string::iterator second, SuffixTreeNode* par) {
	str = s;
	subString = { first, second };
	parent = par;
}

void SuffixTree::BuildArray() {
	root->BuildArrayDFS(suffixArray, 0);
	BuildLCP();
}
void SuffixTreeNode::BuildArrayDFS(std::vector<int>& res, int len) {
	if (nodes.empty()) {
		res.push_back(str->length() - len);
		return;
	}
	for (std::map<char, SuffixTreeNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		it->second->BuildArrayDFS(res, len + it->second->length() - 1);
	}
}
SuffixTreeNode::~SuffixTreeNode() {
	if (isBlank) {
		nodes.clear();
	}
	else {
		for (std::map<char, SuffixTreeNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			delete it->second;
			//it->second = nullptr;
		}
		parent = nullptr;
		suffixRef = nullptr;
		str = nullptr;
	}
}
SuffixTree::~SuffixTree() {

	if (root) {
		delete root;
	}
	if (blank) {
		delete blank;
		blank = nullptr;
	}
}

bool SuffixTree::isExist(std::string& str) {
	return root->isExist(str, str.begin());
}

bool SuffixTreeNode::isExist(std::string& str, std::string::iterator cur) {
	std::map<char, SuffixTreeNode*>::iterator it = nodes.find(*cur);
	if (it == nodes.end()) {
		return false;
	}
	else {
		std::string::iterator f = it->second->subString.first;
		for (; f < it->second->subString.second && cur != str.end(); ++f) {
			if (*f != *cur) {
				return false;
			}
			++cur;
		}
		if (cur == str.end()) {
			return true;
		}
		else {
			++cur;
			return it->second->isExist(str, cur);
		}
	}
}


void SuffixTree::BuildLCP() {
	int n = str.length();
	LCP = std::vector<int>(suffixArray.size());
	std::vector<int> revLCP(LCP.size());
	for (int i = 0; i < n; ++i) {
		revLCP[suffixArray[i]] = i;
	}
	int k = 0;
	for (int i = 0; i < n; ++i) {
		if (k > 0) {
			--k;
		}
		if (revLCP[i] == n - 1) {
			LCP[n - 1] = -1;
			k = 0;
			continue;
		}
		else {
			int j = suffixArray[revLCP[i] + 1];
			while (std::max(i + k, j + k) < n && str[i + k] == str[j + k]) {
				k++;
				LCP[revLCP[i]] = k;
			}
		}
	}
}
int LowerBound(int left, int right, int i, std::string& text, std::string& p, std::vector<int> suffixArray) {
	bool found = false;
	int middle;
	while ((left <= right) && (found != true)) {
		middle = (left + right) / 2;//находим средний индекс в отрезке
		if (text[suffixArray[middle] + i] == p[i]) {
			if (middle > left) {
				if (text[suffixArray[middle] + i] == (suffixArray[middle - 1] + i < text.size() ? text[suffixArray[middle - 1] + i] : '$')) {
					right = middle - 1;
				}
				else {
					found = true;
				}
			}
			else {
				found = true;//?
			}
		}
		else if (text[suffixArray[middle] + i] > p[i]) {
			right = middle - 1;
		}
		else {
			left = middle + 1;
		}
	}

	if (found) return middle;
	else return -1;
}
int UpperBound(int left, int right, int i, std::string& text, std::string& p, std::vector<int> suffixArray) {
	bool found = false;
	int middle;
	while ((left <= right) && (found != true)) {
		middle = (left + right) / 2;//находим средний индекс в отрезке
		if (text[suffixArray[middle] + i] == p[i]) {
			if (middle < /*suffixArray.size() - 1*/ right) {
				if (text[suffixArray[middle] + i] == (suffixArray[middle + 1] + i < text.size() ? text[suffixArray[middle + 1] + i] : '$')) {
					left = middle + 1;
				}
				else {
					found = true;
				}
			}
			else {
				found = true;//?
			}
		}
		else if (text[suffixArray[middle] + i] > p[i]) {
			right = middle - 1;
		}
		else {
			left = middle + 1;
		}
	}

	if (found) return middle;
	else return -1;
}

std::vector<int> SuffixTree::Search(std::string& p) {
	std::vector<int> res;
	if (p.length() >= str.length()) {
		return res;
	}
	int left = 1;
	int	right = suffixArray.size() - 1;
	for (int i = 0; i < p.length(); ++i) {
		left = LowerBound(left, right, i, str, p, suffixArray);
		if (left == -1) {
			return res;
		}
		right = UpperBound(left, right, i, str, p, suffixArray);
		if (right == -1) {
			return res;
		}
	}
	if (right - left < 0) {
		return res;
	}
	res = std::vector<int>(right - left + 1);
	for (int i = 0; left <= right; ++left, ++i) {
		res[i] = suffixArray[left] + 1;
	}
	countingSort<int>(res);
	return res;
}
