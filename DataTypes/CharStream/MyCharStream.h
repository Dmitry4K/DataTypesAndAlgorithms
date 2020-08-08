#pragma once

class MyCharStreamClass {
private:
	const char* src = nullptr;	//строка
	size_t len = 0;			//длина строки
	size_t pos = 0;			//текущая позиция
public:
	MyCharStreamClass(const char* ptr, size_t len);
	void GetWord(char*& dest);
	void Get(char*& dest, size_t s);
	char Get();
	void SkipSpaces();
	bool EOS();
};
