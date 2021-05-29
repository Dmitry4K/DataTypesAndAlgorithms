## Задание

Необходимо реализовать схему взаимодействия процессов «читатели-писатели» под ОС Windows с использованием соответствующих системных вызовов WinAPI и многопоточности,
используя thread, event, и mutex. Приоритет может быть любым. Потоки должны разделять общее адресное пространство. Количество читателей, писателей,
повторов программы, а также директивами препроцессора. Обеспечить вывод на экран результат работы читателей и писателей.

### Алгоритм программы

Выделим основные объекты в данном задании, а также характер их работы. 

Писатель – поток, который имеет доступ к общему хранилищу данных, и может осуществлять запись в него. Писателей может быть достаточно много, поэтому их нужно синхронизировать. Так как только один писатель может иметь доступ к хранилищу, создадим мьютекс, по которому будет предоставляться доступ к данному хранилищу и уже по нему давать доступ как на запись данных так и на чтение.

Читатель может в независимости от других читателей производить чтение и из хранилища. Так как доступ к хранилищу ограничен мьютексом, создадим отдельный поток, который наравне с писателями будет стараться получить доступ к хранилищу и уже потом запускать потоки читателей, которые параллельно в разных потоках считают данные, дождутся друг друга и завершат работу. Синхронизацию читателей будем осуществлять при помощи семафоров.

### Код задания

```c++
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
		currentWriter.write("writer [" + std::to_string(numberOfWriter) 
		+ "] write the string at time : " + std::to_string(myTime.Time()) + "\n");
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
```

### Результат работы

#### Тест 1
_Заданные параметры:_
```
#define totalReadersCount 1
#define totalWritersCount 5
#define readDelay 10
#define writeDelay 40
#define repeatCount 2
```
```
WORK OF WRITERS:

writer [1] write the string at time : 11865300
writer [2] write the string at time : 12867900
writer [3] write the string at time : 12952100
writer [4] write the string at time : 13081500
writer [5] write the string at time : 13146700
writer [3] write the string at time : 54165000
writer [2] write the string at time : 54162700
writer [5] write the string at time : 54161200
writer [4] write the string at time : 54162700
writer [1] write the string at time : 54161200 <-- писатели записывают по одной строке

WORK OF READERS:

Reader [1] read the string at time : 13247900
------------------------------------------
------------------------------------------

Reader [1] read the string at time : 25200500
------------------------------------------
writer [1] write the string at time : 11865300 <-
writer [2] write the string at time : 12867900  |
writer [3] write the string at time : 12952100  |- читатель считывает все хранилище данных
writer [4] write the string at time : 13081500  |
writer [5] write the string at time : 13146700 <-
------------------------------------------
```
#### Тест 2
_Заданные параметры:_ 
```c++
#define totalReadersCount 6
#define totalWritersCount 30
#define readDelay 10
#define writeDelay 50
#define repeatCount 2
```
```
WORK OF WRITERS:

writer [1] write the string at time : 16640400
writer [2] write the string at time : 16668100
writer [1] write the string at time : 74003500
writer [2] write the string at time : 74001900
writer [2] write the string at time : 124426300
writer [1] write the string at time : 124431700

WORK OF READERS:

Reader [1] read the string at time : 17234900
------------------------------------------
------------------------------------------

Reader [1] read the string at time : 30869100
------------------------------------------
writer [1] write the string at time : 16640400
writer [2] write the string at time : 16668100
------------------------------------------

Reader [1] read the string at time : 44410200
------------------------------------------
writer [1] write the string at time : 16640400
writer [2] write the string at time : 16668100
------------------------------------------


Reader [2] read the string at time : 17264800
------------------------------------------
------------------------------------------

Reader [2] read the string at time : 31419500
------------------------------------------
writer [1] write the string at time : 16640400
writer [2] write the string at time : 16668100
------------------------------------------

Reader [2] read the string at time : 44355000
------------------------------------------
writer [1] write the string at time : 16640400
writer [2] write the string at time : 16668100
------------------------------------------


Reader [3] read the string at time : 17967400
------------------------------------------
------------------------------------------

Reader [3] read the string at time : 31466900
------------------------------------------
writer [1] write the string at time : 16640400
writer [2] write the string at time : 16668100
------------------------------------------

Reader [3] read the string at time : 44472100
------------------------------------------
writer [1] write the string at time : 16640400
writer [2] write the string at time : 16668100
------------------------------------------
```

#### Тест 3
_Заданные параметры:_ 
```c++
#define totalReadersCount 6
#define totalWritersCount 30
#define readDelay 10
#define writeDelay 50
#define repeatCount 2
```
```
WORK OF WRITERS:

writer [1] write the string at time : 1476200
writer [2] write the string at time : 1547100
writer [3] write the string at time : 2012300
writer [4] write the string at time : 2662000
writer [5] write the string at time : 3049200
writer [6] write the string at time : 3083600
writer [8] write the string at time : 4029400
writer [9] write the string at time : 4578700
writer [7] write the string at time : 4706800
writer [10] write the string at time : 4765900
writer [11] write the string at time : 4879800
writer [12] write the string at time : 4924100
writer [13] write the string at time : 5030400
writer [14] write the string at time : 5103500
writer [15] write the string at time : 5192700
writer [16] write the string at time : 5227100
writer [17] write the string at time : 5367600
writer [18] write the string at time : 5487000
writer [19] write the string at time : 5662500
writer [20] write the string at time : 5754300
writer [21] write the string at time : 5803700
writer [22] write the string at time : 5901500
writer [23] write the string at time : 6044600
writer [24] write the string at time : 6101600
writer [25] write the string at time : 6133600
writer [26] write the string at time : 6252000
writer [27] write the string at time : 6312100
writer [28] write the string at time : 6456700
writer [29] write the string at time : 6487100
writer [30] write the string at time : 6564700
writer [12] write the string at time : 60888600
writer [16] write the string at time : 60889700
writer [7] write the string at time : 60887200
writer [11] write the string at time : 60882800
writer [15] write the string at time : 60882800
writer [13] write the string at time : 60902400
writer [10] write the string at time : 60904000
writer [14] write the string at time : 60905700
writer [8] write the string at time : 60949000
writer [4] write the string at time : 60960000
writer [3] write the string at time : 60951500
writer [9] write the string at time : 60952800
writer [6] write the string at time : 60975900
writer [2] write the string at time : 60972800
writer [5] write the string at time : 60970700
writer [1] write the string at time : 60978200
writer [28] write the string at time : 62202600
writer [30] write the string at time : 62178400
writer [23] write the string at time : 62178400
writer [27] write the string at time : 62211800
writer [29] write the string at time : 62211300
writer [21] write the string at time : 62244900
writer [24] write the string at time : 62202600
writer [26] write the string at time : 62213800
writer [20] write the string at time : 62252600
writer [22] write the string at time : 62330200
writer [18] write the string at time : 62254300
writer [25] write the string at time : 62212100
writer [19] write the string at time : 62261600
writer [17] write the string at time : 62289900

WORK OF READERS:

Reader [1] read the string at time : 6698600
------------------------------------------
------------------------------------------

Reader [1] read the string at time : 19894300
------------------------------------------
writer [1] write the string at time : 1476200
writer [2] write the string at time : 1547100
writer [3] write the string at time : 2012300
writer [4] write the string at time : 2662000
writer [5] write the string at time : 3049200
writer [6] write the string at time : 3083600
writer [8] write the string at time : 4029400
writer [9] write the string at time : 4578700
writer [7] write the string at time : 4706800
writer [10] write the string at time : 4765900
writer [11] write the string at time : 4879800
writer [12] write the string at time : 4924100
writer [13] write the string at time : 5030400
writer [14] write the string at time : 5103500
writer [15] write the string at time : 5192700
writer [16] write the string at time : 5227100
writer [17] write the string at time : 5367600
writer [18] write the string at time : 5487000
writer [19] write the string at time : 5662500
writer [20] write the string at time : 5754300
writer [21] write the string at time : 5803700
writer [22] write the string at time : 5901500
writer [23] write the string at time : 6044600
writer [24] write the string at time : 6101600
writer [25] write the string at time : 6133600
writer [26] write the string at time : 6252000
writer [27] write the string at time : 6312100
writer [28] write the string at time : 6456700
writer [29] write the string at time : 6487100
writer [30] write the string at time : 6564700
------------------------------------------


Reader [2] read the string at time : 6731800
------------------------------------------
------------------------------------------

Reader [2] read the string at time : 20489700
------------------------------------------
writer [1] write the string at time : 1476200
writer [2] write the string at time : 1547100
writer [3] write the string at time : 2012300
writer [4] write the string at time : 2662000
writer [5] write the string at time : 3049200
writer [6] write the string at time : 3083600
writer [8] write the string at time : 4029400
writer [9] write the string at time : 4578700
writer [7] write the string at time : 4706800
writer [10] write the string at time : 4765900
writer [11] write the string at time : 4879800
writer [12] write the string at time : 4924100
writer [13] write the string at time : 5030400
writer [14] write the string at time : 5103500
writer [15] write the string at time : 5192700
writer [16] write the string at time : 5227100
writer [17] write the string at time : 5367600
writer [18] write the string at time : 5487000
writer [19] write the string at time : 5662500
writer [20] write the string at time : 5754300
writer [21] write the string at time : 5803700
writer [22] write the string at time : 5901500
writer [23] write the string at time : 6044600
writer [24] write the string at time : 6101600
writer [25] write the string at time : 6133600
writer [26] write the string at time : 6252000
writer [27] write the string at time : 6312100
writer [28] write the string at time : 6456700
writer [29] write the string at time : 6487100
writer [30] write the string at time : 6564700
------------------------------------------


Reader [3] read the string at time : 3557000
------------------------------------------
------------------------------------------

Reader [3] read the string at time : 21595300
------------------------------------------
writer [1] write the string at time : 1476200
writer [2] write the string at time : 1547100
writer [3] write the string at time : 2012300
writer [4] write the string at time : 2662000
writer [5] write the string at time : 3049200
writer [6] write the string at time : 3083600
writer [8] write the string at time : 4029400
writer [9] write the string at time : 4578700
writer [7] write the string at time : 4706800
writer [10] write the string at time : 4765900
writer [11] write the string at time : 4879800
writer [12] write the string at time : 4924100
writer [13] write the string at time : 5030400
writer [14] write the string at time : 5103500
writer [15] write the string at time : 5192700
writer [16] write the string at time : 5227100
writer [17] write the string at time : 5367600
writer [18] write the string at time : 5487000
writer [19] write the string at time : 5662500
writer [20] write the string at time : 5754300
writer [21] write the string at time : 5803700
writer [22] write the string at time : 5901500
writer [23] write the string at time : 6044600
writer [24] write the string at time : 6101600
writer [25] write the string at time : 6133600
writer [26] write the string at time : 6252000
writer [27] write the string at time : 6312100
writer [28] write the string at time : 6456700
writer [29] write the string at time : 6487100
writer [30] write the string at time : 6564700
------------------------------------------


Reader [4] read the string at time : 3606500
------------------------------------------
------------------------------------------

Reader [4] read the string at time : 21838700
------------------------------------------
writer [1] write the string at time : 1476200
writer [2] write the string at time : 1547100
writer [3] write the string at time : 2012300
writer [4] write the string at time : 2662000
writer [5] write the string at time : 3049200
writer [6] write the string at time : 3083600
writer [8] write the string at time : 4029400
writer [9] write the string at time : 4578700
writer [7] write the string at time : 4706800
writer [10] write the string at time : 4765900
writer [11] write the string at time : 4879800
writer [12] write the string at time : 4924100
writer [13] write the string at time : 5030400
writer [14] write the string at time : 5103500
writer [15] write the string at time : 5192700
writer [16] write the string at time : 5227100
writer [17] write the string at time : 5367600
writer [18] write the string at time : 5487000
writer [19] write the string at time : 5662500
writer [20] write the string at time : 5754300
writer [21] write the string at time : 5803700
writer [22] write the string at time : 5901500
writer [23] write the string at time : 6044600
writer [24] write the string at time : 6101600
writer [25] write the string at time : 6133600
writer [26] write the string at time : 6252000
writer [27] write the string at time : 6312100
writer [28] write the string at time : 6456700
writer [29] write the string at time : 6487100
writer [30] write the string at time : 6564700
------------------------------------------


Reader [5] read the string at time : 4470400
------------------------------------------
------------------------------------------

Reader [5] read the string at time : 22254900
------------------------------------------
writer [1] write the string at time : 1476200
writer [2] write the string at time : 1547100
writer [3] write the string at time : 2012300
writer [4] write the string at time : 2662000
writer [5] write the string at time : 3049200
writer [6] write the string at time : 3083600
writer [8] write the string at time : 4029400
writer [9] write the string at time : 4578700
writer [7] write the string at time : 4706800
writer [10] write the string at time : 4765900
writer [11] write the string at time : 4879800
writer [12] write the string at time : 4924100
writer [13] write the string at time : 5030400
writer [14] write the string at time : 5103500
writer [15] write the string at time : 5192700
writer [16] write the string at time : 5227100
writer [17] write the string at time : 5367600
writer [18] write the string at time : 5487000
writer [19] write the string at time : 5662500
writer [20] write the string at time : 5754300
writer [21] write the string at time : 5803700
writer [22] write the string at time : 5901500
writer [23] write the string at time : 6044600
writer [24] write the string at time : 6101600
writer [25] write the string at time : 6133600
writer [26] write the string at time : 6252000
writer [27] write the string at time : 6312100
writer [28] write the string at time : 6456700
writer [29] write the string at time : 6487100
writer [30] write the string at time : 6564700
------------------------------------------


Reader [6] read the string at time : 7027400
------------------------------------------
------------------------------------------

Reader [6] read the string at time : 22576200
------------------------------------------
writer [1] write the string at time : 1476200
writer [2] write the string at time : 1547100
writer [3] write the string at time : 2012300
writer [4] write the string at time : 2662000
writer [5] write the string at time : 3049200
writer [6] write the string at time : 3083600
writer [8] write the string at time : 4029400
writer [9] write the string at time : 4578700
writer [7] write the string at time : 4706800
writer [10] write the string at time : 4765900
writer [11] write the string at time : 4879800
writer [12] write the string at time : 4924100
writer [13] write the string at time : 5030400
writer [14] write the string at time : 5103500
writer [15] write the string at time : 5192700
writer [16] write the string at time : 5227100
writer [17] write the string at time : 5367600
writer [18] write the string at time : 5487000
writer [19] write the string at time : 5662500
writer [20] write the string at time : 5754300
writer [21] write the string at time : 5803700
writer [22] write the string at time : 5901500
writer [23] write the string at time : 6044600
writer [24] write the string at time : 6101600
writer [25] write the string at time : 6133600
writer [26] write the string at time : 6252000
writer [27] write the string at time : 6312100
writer [28] write the string at time : 6456700
writer [29] write the string at time : 6487100
writer [30] write the string at time : 6564700
------------------------------------------
```
