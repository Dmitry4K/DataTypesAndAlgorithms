#include<iostream>
#include<sstream>
#include<Windows.h>
#include<vector>
#include<thread>
#include<mutex>
#include<list>
#include"SimpeTimer.hpp"

//количество читателей
#define totalReadersCount 5
//количество писателей
#define totalWritersCount 3
//задрежка работы читателей в мс
#define readDelay 1000
//задержка работы писателей в мс
#define writeDelay 5000
//количество повторений, которое нужно сделать писателям и читателям
#define repeatCount 2


//общее хранилище данных, которое доступно всем потокам
std::string generalString;

//мьютекс, который предоставляет права на запись в хранилище данных
std::mutex writeMutex;

//поток писателей, который пытается поймать writeMutex и дать доступ читателям прочитать сообщения
std::thread ReaderWathcer;

//семафор по которому будем определять, когда все читатели закончили чтении их хранилища
HANDLE readSemaphore;

//семафор по которому будем определять, когда все читатели выполнили свои инструкции
HANDLE readerSemaphoreExit;
//аналогично для писателей
HANDLE writerSemaphoreExit;

//таймер, чтобы отслеживать запись работу всех потоков
Timer myTime;


//описание класса писателя
class Writer {
public:
	void write(std::string string) {
		writeMutex.lock();			//ловим мьютекс
		generalString += string;	//записываем новые данные в строку
		writeMutex.unlock();		//отпускаем мьютекс
		Sleep(writeDelay);			//спим
	}
	std::thread writerThread;		//поток в котором исполняется функиция писателя
};

std::vector<Writer> writersVector;	//вектор со всеми писателями

void writerFunction(int numberOfWriter) { //то, что делает писатель в ходе работы всей программы
	//получаем ссылку на текущего писателя, который работает с данным потоком
	Writer& currentWriter = writersVector[numberOfWriter - 1];
	for (int i = 0; i < repeatCount; ++i) {

		//выполняем запись в хранилище
		currentWriter.write("writer [" + std::to_string(numberOfWriter) + "] write the string at time : " + std::to_string(myTime.Time()) + "\n");
	}
	//увеличиваем счетчик семафора для того, чтобы понять, когда завершить программу
	ReleaseSemaphore(writerSemaphoreExit, 1, NULL);
}


//описание писателя
class Reader {
public: 
	std::list<std::string> Logs;	//записываем логи, чтобы в конце проверить работу программы
	void read(int num) {
		//писатель считывает все хранилище, добавляя мета-информацию о том какой писатель обратился к хранилищу
		//и время посещения хранилища
		Logs.push_back("Reader ["+ std::to_string(num) + "] read the string at time : " 
			+ std::to_string(myTime.Time()) 
			+ "\n------------------------------------------" + 
			+ "\n" +  generalString 
			+ "------------------------------------------\n");
	}
	std::thread readThread;
	//Выводит все логи в стандартный поток вывода
	void logs() {
		for (auto iter = Logs.begin(); iter != Logs.end(); ++iter) {
			std::cout << *iter << "\n";
		}
		std::cout << "\n";
	}
};
std::vector<Reader> readersVector; //вектор с читателями

//функция, которая выполняется у каждого читателя
void readerFunction(int num) {
	Reader& currentReader = readersVector[num - 1];
	currentReader.read(num);

	//увеличиваем счетчик семафора для того, чтобы понять, когда завершить процесс чтения писателей
	ReleaseSemaphore(readSemaphore, 1, NULL);
}


//функция запуска всех читателей
void readersFunction() {
	for (int i = 0; i < repeatCount; ++i) {
		//пытается поймать мьютекс, чтобы остановить писателей
		writeMutex.lock();
		//поднимаем потоки с писателями
		for (int i = 0; i < totalReadersCount; ++i) {
			readersVector[i].readThread = std::thread(readerFunction, i + 1);
		}
		//ждем когда все писатели считают хранилище
		for (int i = 0; i < totalReadersCount; ++i) {
			WaitForSingleObject(readSemaphore, INFINITE);
		}
		//присоединяем и завершаем потоки читателей
		for (int i = 0; i < totalReadersCount; ++i) {
			readersVector[i].readThread.join();
		}
		//отпускаем мьютекс
		writeMutex.unlock();
		//увеличиваем счетчик семафора для того, чтобы понять, когда завершить программу
		ReleaseSemaphore(readerSemaphoreExit, 1, NULL);
		Sleep(readDelay);
	}
}


//функция запуска и настройки программы
void start() {
	//задаем размеры векторов
	//создаем семафоры
	//поднимаем потоки писателей
	//поднимаем поток слушателя читателей
	//запускаем таймер
	writersVector.resize(totalWritersCount);
	readerSemaphoreExit = CreateSemaphore(NULL, 0, repeatCount, NULL);
	writerSemaphoreExit = CreateSemaphore(NULL, 0, totalWritersCount, NULL);
	readSemaphore = CreateSemaphore(NULL, 0, totalReadersCount, NULL);
	ReaderWathcer = std::thread(readersFunction);
	readersVector.resize(totalReadersCount);
	for (int i = 0; i < totalWritersCount; ++i) {
		writersVector[i].writerThread = std::thread(writerFunction, i+1);
	}
	myTime.Start();
}

//функция закрытия всех потоков и всех семафоров
void close() {
	CloseHandle(readSemaphore);
	CloseHandle(readerSemaphoreExit);
	CloseHandle(writerSemaphoreExit);
	for (int i = 0; i < totalWritersCount; ++i) {
		writersVector[i].writerThread.join();
	}
	ReaderWathcer.join();
}

//функция, которая держит программу в рабочем состоянии, пока не будут выполнены все функции.
void loop(){
	for (int i = 0; i < repeatCount; ++i) {
		WaitForSingleObject(readerSemaphoreExit, INFINITE);
	}
	for (int i = 0; i < totalWritersCount; ++i) {
		WaitForSingleObject(writerSemaphoreExit, INFINITE);
	}
}

//выводит логи работы читателей и писателей
void logs() {
	std::cout << "WORK OF WRITERS:\n\n";
	std::cout << generalString;
	std::cout << "\nWORK OF READERS:\n\n";
	for (int i = 0; i < totalReadersCount; ++i) {
		readersVector[i].logs();
	}
}

int main() {
	start();
	loop();
	close();
	logs();
	return 0;
}
