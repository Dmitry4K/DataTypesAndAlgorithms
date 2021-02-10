#include"LZW.h"

size_t hash_pair::operator()(const CharAndPrefix& p) const {
	if (sizeof(size_t) == sizeof(code_t)) {
		auto hash1 = std::hash<char>{}(p.Char);
		auto hash2 = std::hash<code_t>{}(p.Prefix);
		return hash1 ^ hash2;
	}
	size_t res = p.Char;
	res = res << (sizeof(code_t) * 8);
	res += p.Prefix;
	return res;
}

bool CharAndPrefix::operator==(const CharAndPrefix& p) const {
	return Char == p.Char && Prefix == p.Prefix;
}

LZW::LZW() {}

inline void LZW::compressing_save_to(int mode,const LZW::code_type s){
	if (mode & TO_STREAM) {
		std::cout << s << ' ';
	}
	if (mode & INTO_OBJ){
		CodedMessage.push_back(s);
	}
}


inline void LZW::decompressing_save_to(int mode, const char s) {
	if (mode & TO_STREAM) {
		std::cout << s;
	}
	if (mode & INTO_OBJ) {
		decoded_text += s;
	}
}

bool LZW::compress(const std::string& text, const std::vector<char>& Alp, int print_mode) {
	
	coded_text = text;
	char current_symbol;
	code_type last_index = 0;
	code_type current_code = -1;
//-----Создаем изначальный алфавит--------------
	cAlphabet.clear();
	if (Alp == EMPTY_ALPHABET) {
		for (auto iter : text) {
			cAlphabet[iter] = last_index;
			++last_index;
		}
		cAlphabet['\0'] = last_index;
		++last_index;
	}
	else {
		for (auto iter : Alp) {
			cAlphabet[iter] = last_index;
			++last_index;
		}
		cAlphabet['\0'] = last_index;
		++last_index;
		
	}
//-----------------------------------------------

	if (text.size()) {
		std::string::const_iterator iter = text.begin();
		current_symbol = *text.begin();
		current_code = cAlphabet[current_symbol];
		++iter;
		
		for (; iter != text.end(); ++iter) {//всего N итераций
			dictionary_type::iterator dict_iter = Dictionary.find({*iter, current_code}); //поиск в хеш-таблице за константу
			if (dict_iter != Dictionary.end()) {
				current_symbol = *iter;
				current_code = (*dict_iter).second;
			}
			else {
				Dictionary[{*iter, current_code}] = last_index;
				compressing_save_to(print_mode, current_code);
				++last_index;
				current_code = cAlphabet[*iter];
				current_symbol = *iter;
			}
		}
		compressing_save_to(print_mode, current_code);
		compressing_save_to(print_mode, cAlphabet['\0']);
		is_coded = true;
		return true;
	}
	compressing_save_to(print_mode, cAlphabet['\0']);
	is_coded = true;
	return true;
}

/*void LZW::setBitCount(int b) {
	count_bit = b;
}*/

const std::vector<LZW::code_type>& LZW::getCodedVector() const{
	return CodedMessage;
}
std::string LZW::getCodedBits() {
	std::string str = "";
	for (int i = 0; i < (int)CodedMessage.size(); ++i) {
		int bits = mbits(CodedMessage[i]);
		for (int j = 0; j < bits ; ++j) {
			str += (((CodedMessage[i] & (1 << (bits - j - 1)))>>(bits - j - 1)) + '0');
		}
	}
	return str;
}

std::string LZW::getString() {
	return coded_text;
}

int mbits(int a) {
	return (a== 0) ? 1 : (int)log2(a) + 1;
}
std::vector<bool> bits(const int a) {
	std::vector<bool> res;
	int bitc = mbits(a);
	for (int i = 0; i < bitc; ++i) {
		res.push_back(((a & (1 << (bitc - i - 1))) >> (bitc - i - 1)));
	}
	return res;
}

void print_bits(std::vector<bool>&& a){
	for (int i = 0; i < (int)a.size(); ++i) {
		std::cout << a[i];
	}
}

/*
bool LZW::decompress(const std::vector<bool>& str, const std::vector<char>& Alphabet) {
	//Создать словарь
	//В фазу добавить первый символ сообщения
	//Cчитать символ Y <----------------------------|
	//Если Y - символ конца сообщения				|
		//выдать символ для кода X					|
	//иначе											|
		//Если фразы под кодом XY нет в словаре		|
			//Вывести фразу соот. коду X			|
			//фразу с кодом XY занести в словарь	|
		//иначе										|
			//присвоить входной фразе код XY		|
			//перейти к ----------------------------|

	int last_index = 0;
	std::vector<bool> Phase;
	for (size_t i = 0; i < Alphabet.size(); ++i) {
		Dictionary.insert(std::make_pair(std::string() + (Alphabet[i]), IndexAndCode(last_index, last_index)));
		++last_index;
	}
	Phase.push_back(str[0]);
	int i = 1;
	for (i; i < (int)str.size(); ++i) {
		Phase.push_back(str[i]);

	}
	return true;
}*/
///*
bool LZW::decompress(const std::vector<LZW::code_type>& str, const std::vector<char>& Alp, int print_mode) {
	size_t last_index = 0;
	//-----Создаем изначальный алфавит--------------
	dAlphabet.clear();
	dAlphabet.resize(Alp.size() + 1);
	for (auto iter : Alp) {
		dAlphabet[last_index] = iter;
		++last_index;
	}
	dAlphabet[last_index] = '\0';
	++last_index;
	//-----------------------------------------------
	dDictionary.clear();
	if (str.size()) {
		auto it = str.begin();
		code_type old_code = *it;
		code_type new_code;
		char old_symbol = dAlphabet[old_code];
		++it;
		decompressing_save_to(print_mode, old_symbol);
		for (; it != str.end(); ++it) {
			new_code = (*it);
			if (new_code < dAlphabet.size()) {
				dDictionary.push_back({dAlphabet[new_code], old_code});
				decompressing_save_to(print_mode, dAlphabet[new_code]);
				old_symbol = dAlphabet[new_code];
			}
			else {
				int code;
				std::vector<char> s;
				if (new_code - dAlphabet.size() >= dDictionary.size()) {
																				//случай, когда еще нет строки в словаре
					code = old_code;											//<-------
					while ((size_t)code >= dAlphabet.size()) {
						s.push_back(dDictionary[code - dAlphabet.size()].Char);
						code = dDictionary[code - dAlphabet.size()].Prefix;
					}
					decompressing_save_to(print_mode, dAlphabet[code]);
					if (!s.empty()) {
						for (size_t i = s.size(); i > 0; --i) {
							decompressing_save_to(print_mode, s[i-1]);
						}
					}
					decompressing_save_to(print_mode, dAlphabet[code]); 	//<-------
				}
				else {
																				//случай, когда строка есть в словаре
					code = new_code;
					while ((size_t)code >= dAlphabet.size()) {
						s.push_back(dDictionary[code - dAlphabet.size()].Char);
						code = dDictionary[code - dAlphabet.size()].Prefix;
					}
					decompressing_save_to(print_mode, dAlphabet[code]);
					if (!s.empty()) {
						for (size_t i = s.size(); i > 0; --i) {
							decompressing_save_to(print_mode, s[i-1]);
						}
					}
				}
				old_symbol = dAlphabet[code];
				dDictionary.push_back({ old_symbol, old_code });
			}
			old_code = new_code;
		}

		return true;
	}
	return false;
}
//*/
const std::string& LZW::getUncodedString() const{
	return decoded_text;
}

bool LZW::stream_decompress(std::istream & in, const std::vector<char>& Alp, int print_mode) {
	size_t last_index = 0;
	//-----Создаем изначальный алфавит--------------
	dAlphabet.clear();
	dAlphabet.resize(Alp.size() + 1);
	for (auto iter : Alp) {
		dAlphabet[last_index] = iter;
		++last_index;
	}
	dAlphabet[last_index] = '\0';
	++last_index;
	//-----------------------------------------------
	dDictionary.clear();
	LZW::code_type it;
	in >> it;
	//auto it = str.begin();
	code_type old_code = it;
	code_type new_code;
	char old_symbol = dAlphabet[old_code];
	decompressing_save_to(print_mode, old_symbol);

	while(in.get() != '\n'){ // <
		in >> new_code;
		if (new_code < dAlphabet.size()) {
			dDictionary.push_back({ dAlphabet[new_code], old_code });
			decompressing_save_to(print_mode, dAlphabet[new_code]);
			old_symbol = dAlphabet[new_code];
		}
		else {
			int code;
			std::vector<char> s;
			if (new_code - dAlphabet.size() >= dDictionary.size()) {
				//случай, когда еще нет строки в словаре
				code = old_code;											//<-------
				while ((size_t)code >= dAlphabet.size()) {
					s.push_back(dDictionary[code - dAlphabet.size()].Char);
					code = dDictionary[code - dAlphabet.size()].Prefix;
				}
				decompressing_save_to(print_mode, dAlphabet[code]);
				if (!s.empty()) {
					for (size_t i = s.size(); i > 0; --i) {
						decompressing_save_to(print_mode, s[i - 1]);
					}
				}
				decompressing_save_to(print_mode, dAlphabet[code]); //<-------
			}
			else {
				//случай, когда строка есть в словаре
				code = new_code;
				while ((size_t)code >= dAlphabet.size()) {
					s.push_back(dDictionary[code - dAlphabet.size()].Char);
					code = dDictionary[code - dAlphabet.size()].Prefix;
				}
				decompressing_save_to(print_mode, dAlphabet[code]);
				if (!s.empty()) {
					for (size_t i = s.size(); i > 0; --i) {
						decompressing_save_to(print_mode, s[i - 1]);
					}
				}
			}
			old_symbol = dAlphabet[code];
			dDictionary.push_back({ old_symbol, old_code });
		}
		old_code = new_code;
	} // <
	return true;
}