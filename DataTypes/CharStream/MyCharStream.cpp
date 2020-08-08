#include"MyCharStream.h"
#include<string>

inline bool space(char c) {
	return std::isspace(c);
}

inline bool notspace(char c) {
	return !std::isspace(c);
}

MyCharStreamClass::MyCharStreamClass(const char* ptr, size_t l) :
	src(ptr),
	len(l)
{

}
void MyCharStreamClass::GetWord(char*& dest) {
	SkipSpaces();
	size_t start = pos;
	while (pos < len) {
		if (space(src[pos])) {
			break;
		}
		else {
			++pos;
		}
	}
	size_t w_len = pos - start;
	if (w_len > 0) {
		if (src[w_len - 1] != '\0') {
			dest = new char[w_len + 1];
			dest[w_len] = '\0';
		}
		else {
			dest = new char[w_len];
		}
	}
	else {
		dest = new char('\0');
		return;
	}
	memcpy(dest, src + start, w_len);
}

void MyCharStreamClass::Get(char*& dest, size_t s) {
	if (s > len - pos) {
		s = len - pos;
	}
	if (src[s - 1] != '\0') {
		dest = new char[s+1];
		dest[s] = '\0';
	}
	else {
		dest = new char[s];
	}
	memcpy(dest, src + pos, s);
	pos += s;
}
char MyCharStreamClass::Get() {
	char res = '\0';
	if (pos < len){
		res = src[pos];
		++pos;
	}
	return res;
}
void MyCharStreamClass::SkipSpaces() {
	while (pos < len) {
		if (space(src[pos])) {
			++pos;
		}
		else {
			break;
		}
	}
}
bool MyCharStreamClass::EOS() {
	return pos == len ? true : false;
}
