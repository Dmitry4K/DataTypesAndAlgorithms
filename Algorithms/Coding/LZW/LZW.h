#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<functional>
#include<iostream>
#include<unordered_map>

using code_t = unsigned int;

struct CharAndPrefix {
	char Char;
	code_t Prefix;
	bool operator==(const CharAndPrefix & p) const;
};

int mbits(int a);

struct hash_pair {
	size_t operator()(const CharAndPrefix& p) const;
};
std::vector<bool> bits(const int a);
void print_bits(std::vector<bool>&& a);

const std::vector<char> BaseAlphabet = { 'a','b','c','d','e' };
const std::vector<char> EMPTY_ALPHABET = {};

//переменные, которые используются чтобы задать способ вывод/сохранения закодированной/декодированной строки
const int INTO_OBJ = 1;				//сохранить в экземпляр объекта LZW
const int TO_STREAM = 2;			//сразу вывести резултат в поток std::cout


class LZW {
public:
	LZW();
	using code_type = code_t;
	using coding_alphabet_type = std::unordered_map<char, code_type>;
	using decoding_alphabet_type = std::vector<char>;
	using dictionary_type = std::unordered_map<CharAndPrefix, code_type, hash_pair>;
	using decoding_dictionary_type = std::vector<CharAndPrefix>;
	bool compress(const std::string& text, const std::vector<char>& Alphabet = EMPTY_ALPHABET, int print_mode = INTO_OBJ);		//кодирование строки
	//bool decompress(const std::vector<bool>& str, const std::vector<char>& Alphabet);
	bool decompress(const std::vector<LZW::code_type>& str, const std::vector<char>& Alphabet, int print_mode = INTO_OBJ);		//декодирование строки
	bool stream_decompress(std::istream& in, const std::vector<char>& Alphabet, int print_mode = INTO_OBJ);					//декодирование со считыванием из потока
	//void setBitCount(int b);
	const std::vector<LZW::code_type>& getCodedVector() const;													//возвращает вектор кодов в которые был закодирован текст
	const std::string& getUncodedString() const;																	//возвращает ранее раскодированную строку
	std::string getCodedBits();
	std::string getString();																		//возвращает закодированную ранее строку

private:
	inline void compressing_save_to(int mode, const LZW::code_type s);
	inline void decompressing_save_to(int mode, const char s);
	//std::string coded_text = "";						//кодируемый тексты
	std::string decoded_text = "";						//декодированный текст
	bool is_coded = false;								//закодирован ли текст?
	//int count_bit = -1;									//кол-во бит на кодирование
	std::vector<LZW::code_type> CodedMessage;			//вектор закодированного сообщения представленного через набор кодов словаря
	dictionary_type Dictionary;							//словарь - хеш-таблица для кодирования
	decoding_dictionary_type dDictionary;				//словарь - хеш-таблица для декодирования
	coding_alphabet_type cAlphabet;						//алфавит для кодировки - вектор
	decoding_alphabet_type dAlphabet;					//алфавит для декодировки - вектор
};