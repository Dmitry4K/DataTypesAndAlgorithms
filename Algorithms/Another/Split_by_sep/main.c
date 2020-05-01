#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"split.h"
const int STR_LENGTH = 1000;


int main() {
	char* str;
	str = (char*)malloc(STR_LENGTH * sizeof(char));
	char buffer[10000] = "";
	str = gets_s(buffer);
	char** res = split(str, ' ');
	int t_size = 0;

	if(res != nullptr)
		while (res[t_size][0] != '\0') {
			printf("%s ", res[t_size]);
			t_size++;
		}
	str = nullptr;
	for (int i = 0; i < t_size; i++)
		free(res[i]);
	free(res);
	//system("pause");
	return 0;
}
