#include"list.hpp"
#include<iostream>

int main() {
	MyListClass<int> list;
	list.insert(1);
	list.insert(1);
	list.insert_back(1);
	list.insert(1, 1);
	auto* ptr = list.begin();
	while (ptr->has_next()) {
		std::cout << ptr->get() << ' ';
		ptr = ptr->next();
	}
	std::cout << ptr->get() << ' ';
}
