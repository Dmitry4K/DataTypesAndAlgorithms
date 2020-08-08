Простая реализация потокого ввода из строки, которая игнорирурует знак '\0', что позволяет работать с источниками в которых содержится сжатая информация и символ '\0' может находится в любом месте текста

***Пример*** 
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

```Output
123 1
```
