#include "MySockets.h"

std::pair <std::string, std::string> SplitOnIpAndPort(const std::string& way) {
	int split_point = -1;
	std::pair <std::string, std::string> res;
	for (int i = 0; i < way.length(); ++i) {
		if (way[i] == ':') {
			split_point = i;
			break;
		}
	}
	if (split_point != -1) {
		res = std::make_pair<std::string, std::string>(way.substr(0, split_point), way.substr(split_point+1));
	}
	else {
		res = std::make_pair<std::string, std::string>("","");
	}
	return res;
}


const std::string& MySocketClass::GetAdr() const {
	return adr;
}
int MySocketClass::GetSocketHandle() const {
	return handle;
}


MySocketClass::MySocketClass() {
	if (!IS_WSA_STARTED) {
		if (WSAStartup(MAKEWORD(2, 2), &W_DATA) == 0) {
			std::cout << "WSA Startup succes\n";
		}
		else {
			"WSA Startup Error!\n";
			exit(1);
		}
		IS_WSA_STARTED = true;
	}
	handle = socket(AF_INET, SOCK_STREAM, NULL);
	if (handle == SOCKET_ERROR) {
		std::cout << "Socket not created!\n";
		exit(1);
	}
	++SOCKET_COUNT;
}

int MySocketClass::Connect(const std::string& way) {
	auto IpAndPort = SplitOnIpAndPort(way);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(IpAndPort.first.c_str());
	addr.sin_port = htons(std::stoi(IpAndPort.second));
	int res = connect(handle, (sockaddr*)&addr, sizeof(addr));
	u_long arg = 1;
	ioctlsocket(handle, FIONBIO, &arg);
	std::cout << "Client connected to server - "
		<< (unsigned char)addr.sin_addr.S_un.S_un_b.s_b1 + '0' - 48 << '.'
		<< (unsigned char)addr.sin_addr.S_un.S_un_b.s_b2 + '0' - 48 << '.'
		<< (unsigned char)addr.sin_addr.S_un.S_un_b.s_b3 + '0' - 48 << '.'
		<< (unsigned char)addr.sin_addr.S_un.S_un_b.s_b4 + '0' - 48 << ':'
		<< ntohs(addr.sin_port) << std::endl;
	if (res != SOCKET_ERROR) {
		adr = way;
	}
	return res;

}
int MySocketClass::Bind(const std::string& way) {
	auto IpAndPort = SplitOnIpAndPort(way);
	SOCKADDR_IN addr;
	int r;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(IpAndPort.first.c_str());
	addr.sin_port = htons(std::stoi(IpAndPort.second));
	if ((r = bind(handle, (SOCKADDR*)&addr, sizeof(addr))) != SOCKET_ERROR) {
		std::cout << "Socket succed binded\n";
		std::cout << "Socket - "
			<< (unsigned char)addr.sin_addr.S_un.S_un_b.s_b1 + '0' - 48 << '.'
			<< (unsigned char)addr.sin_addr.S_un.S_un_b.s_b2 + '0' - 48 << '.'
			<< (unsigned char)addr.sin_addr.S_un.S_un_b.s_b3 + '0' - 48 << '.'
			<< (unsigned char)addr.sin_addr.S_un.S_un_b.s_b4 + '0' - 48 << ':'
			<< ntohs(addr.sin_port) << std::endl;
		state = BINDED;
	}
	else {
		std::cout << "Socket bind error\n";
		return r;
	}
	u_long arg = 1;
	ioctlsocket(handle, FIONBIO, &arg);
	if (listen(handle, SOMAXCONN) != SOCKET_ERROR) {
		std::cout << "Start listening at port : " << ntohs(addr.sin_port) << '\n';
		adr = way;
	}
	else {
		std::cout << "NOT LISTENING"<< '\n';
	}
	return r;
}

int MySocketClass::Close() {
	state = EMPTY;
	adr.clear();
	return closesocket(handle);
}

int MySocketClass::Send(int h, const char* m, int len) {
	char* buf = new char[len + sizeof(int)];
	memcpy(buf, &len, sizeof(int));
	memcpy(buf + sizeof(int), m, len);
	int res = send(h, buf, len + sizeof(int), 0);
	delete[] buf;
	return res;
}
int MySocketClass::Send(const char* m, int len) {
	return Send(handle, m, len);
}
int MySocketClass::Send(const char* m) {
	return Send(m, strlen(m) + 1);
}

int MySocketClass::Send(const std::string& s) {
	return Send(handle, s);
}
int MySocketClass::Send(int h, const std::string& s) {
	return Send(h, s.c_str(), s.length() + 1);
}

int MySocketClass::Recieve(int h, char*& buf) {
	int msg_size;
	int res = recv(h, (char*)&msg_size, sizeof(int), 0);
	if (res < 4) {
		return res;
	}
	buf = new char[msg_size];
	res = recv(h, buf, msg_size, 0);
	return res;
}
int MySocketClass::Recieve(char*& buf) {
	return Recieve(handle, buf);
}
int MySocketClass::Recieve(std::string& m) {
	return Recieve(handle, m);
}
int MySocketClass::Recieve(int h, std::string& m) {
	char* buf = nullptr;
	int res = Recieve(h, buf);
	if (res > 0) {
		m = std::string(buf);
	}
	return res;
}

int MySocketClass::State() const{
	return state;
}


MySocketClass::~MySocketClass() {
	if (SOCKET_COUNT == 1) {
		WSACleanup();
	}
	SOCKET_COUNT = 0;
}
