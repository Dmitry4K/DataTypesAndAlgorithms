#include<iostream>
#include<string>
#include"LongNumber.h"


int main() {
	std::ios::sync_with_stdio(false);
	std::string str;
	LongNumber A, B, C;
	char Operator;
	while (std::getline(std::cin, str)) {
		A = LongNumber(str);
		std::getline(std::cin, str);
		B = LongNumber(str);
		Operator = std::cin.get();
		switch (Operator) {
		case '+' :
			std::cout << Sum(A, B) << std::endl; std::cin.get();
			break;
		case '-' :
			if (A >= B) {
				std::cout << Sub(A, B) << std::endl; std::cin.get();
			}
			else {
				std::cout << "Error\n"; std::cin.get();
			}
			break;
		case '*':
			std::cout << Mult(A, B) << std::endl; std::cin.get();
			break;
		case '^' :
			C = A;
			if (std::stoi(str) == 0) {
				std::cout << 0 << std::endl; std::cin.get();
				break;
			}
			for (int i = 0; i < std::stoi(str)-1; ++i) {
				C = Mult(C, A);
			}
			std::cout << C << std::endl; std::cin.get();
			break;
		case '/':
			std::cout << Div(A, B) << std::endl; std::cin.get();
			break;
		case '>':
			std::cout << (Cmp(A, B) == 1 ? "true\n" : "false\n"); std::cin.get();
			break;
		case '<':
			std::cout << (Cmp(A, B) == -1 ? "true\n" : "false\n"); std::cin.get();
			break;
		case '=':
			std::cout << (Cmp(A, B) == 0 ? "true\n" : "false\n"); std::cin.get();
			break;
		}
	}
	return 0;
}