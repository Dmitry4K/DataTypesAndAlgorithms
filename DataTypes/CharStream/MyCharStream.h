#pragma once

class MyCharStreamClass {
private:
	const char* src = nullptr;
	size_t len = 0;
	size_t pos = 0;
public:
	MyCharStreamClass(const char* ptr, size_t len);
	void GetWord(char*& dest);
	void Get(char*& dest, size_t s);
	char Get();
	void SkipSpaces();
	bool EOS();
};
