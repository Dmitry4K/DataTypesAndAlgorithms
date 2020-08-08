***CharStream***

Простая реализация потокого ввода из строки, которая игнорирурует знак '\0', что позволяет работать с источниками в которых содержится сжатая информация и символ '\0' может находится в любом месте текста

***Пример*** 

_Code_

```c++
#include<iostream>
#include"MyCharStream.h"


int main(int argc, char* argv[]) {
	MyCharStreamClass CharStream("123\0 123", 9);
	char* word1;
	CharStream.Get(word1,6);
	std::cout << word1 << ' ' << word1[5];
	return 0;
}
```
_Output_

```Output
123 1
```

***Использование***

```c++
MyCharStreamClass::MyCharStreamClass(const char* ptr, size_t len); 	//конструктор класса, принимает указатель на строку и активную длину
void MyCharStreamClass::GetWord(char*& dest);				//получить слово из потока игнорируя пробелы
void MyCharStreamClass::Get(char*& dest, size_t s);			//получить определённое кол-во символов
char MyCharStreamClass::Get();						//получить символ
void MyCharStreamClass::SkipSpaces();					//пропустить пробелы
bool MyCharStreamClass::EOS();						//проверка на конец строки
```
