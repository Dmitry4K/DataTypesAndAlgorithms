#include<iostream>
#include<fstream>
#include<string>
#include"LZW.h"
#include"SimpleTimer.h"

std::vector<char> EngAlp() {
	std::vector<char> Alp;
	for (char i = 'a'; i <= 'z'; ++i) {
		Alp.push_back(i);
	}
	return Alp;
}

int main(int argc, char* argv[]) {
	std::ios::sync_with_stdio(false);

	std::istream& in = std::cin;
	std::ostream& out = std::cout;
	std::string action, line;
	std::vector<LZW::code_type> codes;
	
	Timer t;
	LZW obj = LZW();

	in >> action;

	while(in.get() != '\n'){}
	
	if (action == "compress") {
		std::getline(in, line);
		t.Start();
		obj.compress(line, EngAlp(), TO_STREAM);
		t.Stop();
		std::cout<<std::endl<<"Time: "<<t.Time();
	}
	else if (action == "decompress") {
		obj.stream_decompress(in, EngAlp(), INTO_OBJ);
		out << obj.getUncodedString();
	}
	std::cout << std::endl;
	return 0;
}