#include<iostream>
#include<string>
#include"LongNumber.h"



int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::string str1;
	std::string str2;
	char Operator;
	while (std::cin>>str1>>str2>>Operator) {
		LongNumber A(str1);
		LongNumber B(str2);
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
			if (A == 0 && B == 0) {
				std::cout << "Error\n"; std::cin.get();
			}
			else {
				 std::cout << SmallExp(A, B) << std::endl; std::cin.get();
			}
			break;
		case '/':
			if (B != 0) {
				std::cout << Div(A, B) << std::endl; std::cin.get();
			}
			else {
				std::cout << "Error\n"; std::cin.get();
			}
			break;
		case '>':
			std::cout << (A > B ? "true\n" : "false\n"); std::cin.get();
			break;
		case '<':
			std::cout << (A < B ? "true\n" : "false\n"); std::cin.get();
			break;
		case '=':
			std::cout << (A == B ? "true\n" : "false\n"); std::cin.get();
			break;
		}
	}
	return 0;
}
