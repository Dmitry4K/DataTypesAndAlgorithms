
//#include<vld.h>
#include<iostream>
#include<fstream>
#include<cctype>
#include<string.h>
#include"BTree.h"

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
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
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
				if (!file.is_open()) {
					std::cout << "ERROR: File is not opened\n";
					continue;
				}
				btree.BTreeLoad(file);
				file.close();
				std::cout << "OK\n";
			}
			else if (strcmp(buffer.key, "Save") == 0) {
				std::cin >> buffer.key;
				std::fstream file(buffer.key, std::ios::binary | std::ios::out);
				file.sync_with_stdio(false);
				btree.BTreeSave(file);
				file.close();
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
	return 0;
}
