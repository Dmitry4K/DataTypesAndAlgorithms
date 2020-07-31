#pragma once
#include <string>
#include <mutex>
#include <zmq.h>
//адреса на которых будут распологаться все сокеты
const std::string PREFIX_ADRESS_LOCALHOST = "tcp://localhost:";		//используется в методах connect
const std::string PREFIX_ADRESS = "tcp://*:";						//используется в методах bind

const int UNKNOWN = -1;			//с сокетом ничего не делали
const int BINDED = 0;			//сокет был привзян
const int CONNECTED = 1;		//сокет был подключен
const int RECONNECTED = 2;		//сокет был преподключен

struct Socket {			//структура zmq сокета подстроенная под текущую задачу, работаем внутри машины
	void* context;				//контекст сокета
	void* socket;				//сам zmq сокет
	int port = -1;				//порт по которому подкюлчен сокет или не подключен 
	int config = UNKNOWN;		//что происходило с сокетом
	bool Bind(int port);		//привязать узел по порту 
	bool Connect(int port);		//присоединить узел по порту
	bool Disconnect();			//отосоединиться от узла
	bool Reconnect(int port);
};
const int NOT_BLOCKING = ZMQ_DONTWAIT;
const int BLOCKING = 0;
struct PushPullSocket {			//структура которая объединяет push и pull сокет в один, благодаря чему может как отправлять сообщения, так и считывать
private:
	Socket push;
	Socket pull;
	std::mutex door;
	int flags = BLOCKING;
public:
	PushPullSocket();
	int SendMsg(const std::string& msg);				//отправить сообщение в сокет
	int GetMsg(std::string& msg);						//получить сообщение с сокета
	int SendInt(int);
	int GetInt(int&);
	void SetBlock(int flags);
	Socket& GetPushSocket();
	Socket& GetPullSocket();
};
