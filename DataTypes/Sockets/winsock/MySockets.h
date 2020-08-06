#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<string>
#include<utility>

#pragma comment (lib,"Ws2_32.lib")
#include <winsock2.h>
#include<Windows.h>
#include<mutex>
													//Состояния сокетов
const int EMPTY = 0;
const int CONNECTED = 1;
const int BINDED = 2;
													//Переменный для хранения информации библиотеки winsock
static bool IS_WSA_STARTED = false;
static WSADATA W_DATA;

static int SOCKET_COUNT = 0;						//Кол-во созданных в процессе экземпляров MySocketClass
class MySocketClass {		
private:
	std::string adr;								//подключенный адресс
	int handle = 0;									//handle, который получаем при вызове socket()
	int state = EMPTY;								//Состояние сокета
	//std::mutex door;								//Можно добавить мьютекс, чтобы сделать сокет потоко-безопасным
public:
	MySocketClass();
	~MySocketClass();
	const std::string& GetAdr() const;
	int GetSocketHandle() const;
	int Connect(const std::string& way);
	int Bind(const std::string& way);
	int Close();
													//методы отправки сообщений
	int Send(int h, const char*, int len);
	int Send(const char*, int len);
	int Send(const char*);							//только для классических си строк !
	int Send(const std::string& m);
	int Send(int h, const std::string& m);
													//методы приема сообщений
	int Recieve(int h, char*&);
	int Recieve(char*&);
	int Recieve(std::string& m);					//только для классических строк
	int Recieve(int h, std::string& m);				//только для классических строк

	int State() const ;
};
