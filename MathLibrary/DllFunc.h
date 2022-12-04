// MathLibrary.h - Contains declarations of math functions
#pragma once
#include <ctime>
#include <string>
#include <random>
#include <time.h>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <stdio.h>
#include <tchar.h>
//#include <stdafx.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <shlobj.h>
#include <windows.h>
//#include <sys/ipc.h>
//#include <sys/sem.h> 

#pragma comment(lib, "shell32.lib")

#define _WIN32_WINNT  0x0501 // I misunderstand that

#ifdef DLLFUNC_EXPORTS
#define DLLFUNC_API __declspec(dllexport)
#else
#define DLLFUNC_API __declspec(dllimport)
#endif

/*
// The Fibonacci recurrence relation describes a sequence F
// where F(n) is { n = 0, a
//               { n = 1, b
//               { n > 1, F(n-2) + F(n-1)
// for some initial integral values a and b.
// If the sequence is initialized F(0) = 1, F(1) = 1,
// then this relation produces the well-known Fibonacci
// sequence: 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

// Initialize a Fibonacci relation sequence
// such that F(0) = a, F(1) = b.
// This function must be called before any other function.
extern "C" DLLFUNC_API void fibonacci_init(
    int a, int b);

// Produce the next value in the sequence.
// Returns true on success and updates current value and index;
// false on overflow, leaves current value and index unchanged.
extern "C" DLLFUNC_API bool fibonacci_next();

// Get the current value in the sequence.
extern "C" DLLFUNC_API int fibonacci_current();

// Get the position of the current value in the sequence.
extern "C" DLLFUNC_API int fibonacci_index();

extern "C" DLLFUNC_API void return_string(char* ref);
*/

/*
    1. Аппаратные функции - данные функции реализованы с модели
    операционной системы, их использование обязательно при обращении к
    виртуальной машине :
*/

//1.1 - получить размер оперативной памяти(в байтах);
extern "C" DLLFUNC_API uint64_t GetMemorySize();

//1.2 - получить размер страницы(в байтах);
extern "C" DLLFUNC_API int GetPageSize();

//1.3 - получить размер диска(в байтах);
extern "C" DLLFUNC_API uint64_t GetDiskSize();

//1.4 - получить размер кластера(в байтах);
extern "C" DLLFUNC_API uint64_t GetSectorSize();

//1.5  -записать строку в лог(не более 40К за 500 мс);
extern "C" DLLFUNC_API void AddLog(char* s, int size);

//1.6  -считать байт из памяти по физ.адресу;
extern "C" DLLFUNC_API BYTE ReadMemoryByte(int &memPhysAdress);

//1.7 - записать байт в память по физ.адресу;
extern "C" DLLFUNC_API void WriteMemoryByte(int &memPhysAdress, BYTE value);

//1.8 - считать из памяти по указанному физ.адресу несколько байт
//(memPhysAdress - адрес, с которого надо считывать данные, lpBuffer -
//буфер, в который необходимо перенести указанные данные, count -
//количество считываемых байт);
extern "C" DLLFUNC_API BYTE* ReadMemory(int &memPhysAdress, int count);

//1.9  - записать в памяти из указанного буфера несколько байт
//(memPhysAdress - адрес, по которому происходит запись, lpBuffer -
//буфер, из которого переносятся данные, count - количество байт);
extern "C" DLLFUNC_API void WriteMemory(int &memPhysAdress, BYTE* lpBuffer, int count);

//1.10  - считать кластер
//с диска(внимание, функция блокирующая), параметры: memAdress -
//адрес в оперативной памяти, начиная с которого необходимо
//поместить содержимое кластера, nSector - номер кластера диска, с
//которого небходимо считать данные;
extern "C" DLLFUNC_API void ReadDisk(int memAdress, int nSector);

//1.11  - записать
//кластер с диска(внимание, функция блокирующая), параметры:
//memAdress - адрес в оперативной памяти, начиная с которого данные
//записываются в кластер, nSector - номер кластера диска, в который
//записываются данные.
extern "C" DLLFUNC_API void WriteDisk(int memAdress, int nSector);

/*
    2. Функции ОС - прототипы функций, которые необходимо реализовать
    согласно варианту :
*/

//2.1  - запуск подсистем управления, начальная
//инициализация подсистем;
extern "C" DLLFUNC_API void Start();

//2.2 - остановка подсистем управления, остановка
//подсистем управления.
extern "C" DLLFUNC_API void Stop();

/*
    3. Функции ОС, информационные - прототипы функций, которые
    необходимо реализовать согласно варианту :
*/

extern enum PROCESS_STATUS {
    NotExist = 0, 
    Execute = 1, 
    Ready = 2, 
    Wait = 3
};

//3.1 - получить информацию о процессах в системе,
//размер буфера = 100, фактически является "планировщиком"
//процессов
extern "C" DLLFUNC_API void GetProcessStatus(BYTE* lpProcStatusBuffer, double* lpProcData); 

// структура для описания состояния физ. памяти
extern "C" struct PHYS_MEMORY_BLOCK {
    int nStart; // начало блока в оперативной памяти
    int nLength; // длина блока
    int nProcess; // номер процесса (0-99), которому выделен блок (255 - система)
};

//3.2  - получить количество блоков;
extern "C" DLLFUNC_API int GetPhysMemoryBlockCount();

//3.3  - получить описание
//блоков, lpBlockList - список описания блоков;
extern "C" DLLFUNC_API void GetPhysMemoryBlockList(PHYS_MEMORY_BLOCK* lpBlockList);

//3.4  - получить
//информацию о состоянии диска(посекторно), 0 - свободный
//сектор, 1 - 100 - сектор принадлежит файлу(номер совпадает с
//номером в каталоге), 255 - зарезервировано системой;
extern "C" DLLFUNC_API void GetDiskStatus(BYTE* lpStatusBuffer);


//3.5  - получить каталог, файлов на диске не
//более 100 (индексы с 1 по 100 включительно), lpFileNames - имена
//файлов, lpFirstSectors - номера первых кластеров, lpSizes - размеры
//файлов;
extern "C" DLLFUNC_API void GetDiskCatalog(char lpFileNames[][20], int* lpFirstSectors, int* lpSizes);

//3.6 - создать процесс, nData -
//дополнительные параметры для процесса(зависит от алгоритма
//планирования), 1. Гарантированное планирование - номер
//пользователя от имени которого запущен процесс, 2. SJF с
//предсказанием - не используется, 3. Вытесняющий SJF - полное
//время выполнения процесса, 4. Приоритетное планирование с
//абсолютным приоритетом - номер приоритета, 5. Многоуровневая
//очередь(2 уровня: высокий приоритет – Round robin, низкий
//приоритет – FCFS) - номер приоритета, функция должна вернуть
//номер для созданного процесса;
extern "C" DLLFUNC_API int osCreateProcess(int nData);

//3.7  - удалить процесс с указанным номером
extern "C" DLLFUNC_API void osDeleteProcess(int nProcess);

/*
    4. Функции ОС, управление памятью - прототипы функций, которые
    необходимо реализовать согласно варианту :
*/

//4.1  - создать адресное пространство для
//указанного процесса, nProcess - номер процесса для которого
//создается адресное пространство, bBlockCount - количество блоков
//адресного пространства, для страничного распределения
//bBlockCount всегда равен 1, для сегментного и сегментностраничного распределения - количество сегментов, lpBlockLength
//- длины блоков аресного пространства;
extern "C" DLLFUNC_API void osMakeAddressSpace(int nProcess, int bBlockCount, int* lpBlockLength);

extern enum MEMORY_OPERATION {
    MemoryRead = 0, 
    MemoryWrite = 1
};

//4.2  - выполнить трансляцию адреса, nProcess - номер
//процесса, в адресном пространстве которого выполняется
//преобразование, nVirtualAdress - виртуальный адрес, по которому
//пытаемся произвести обращение, nOperationType - выполняемая
//операция при доступе к ячейке памяти(MemoryRead или
//MemoryWrite), функция должна вернуть номер физ.ячейки или - 1
//если необходимая часть адресного пространства отсутствует в
//оперативной памяти;
extern "C" DLLFUNC_API int osTranslateAddress(int nProcess, int nVirtualAdress, int nOperationType);

//4.3  - выполнить трансляцию адреса,
//nProcess - номер процесса, в адресном пространстве которого
//выполняется преобразование, nSegment - номер сегмента, к
//которому пытаемся произвести обращение, nOffset - смещение в
//сегменте, nOperationType - выполняемая операция при доступе к
//ячейке памяти(MemoryRead или MemoryWrite), функция должна
//вернуть номер физ.ячейки или - 1 если необходимая часть
//адресного пространства отсутствует в оперативной памяти;
extern "C" DLLFUNC_API int osTranslateAddress2(int nProcess, int nSegment, int nOffset, int nOperationType);

/*
    5. Функции ОС, управление вводом / выводом - прототипы функций, которые
    необходимо реализовать согласно варианту :
*/

//5.1  - запись данных из оперативной
//памяти в указанный файл, nProcess - номер процесса(0 - 99),
//вызвавший метод(255 - система), fileName - имя файла(не более
//20 символов), virtMemBuffer - адрес буфера в адресном
//пространстве процесса, если вызывается от имени системы -
//virtMemBuffer указывает на физ.память, count - длина буфера на
//запись, offset - позиция в файле, с которой необходимо
//осуществлять запись, возвращает 1 - если успех - 1 - если ошибка;
extern "C" DLLFUNC_API int osWriteFile(int nProcess, char* fileName, int virtMemBuffer, int count, int offset);

//5.2  - запись данных в файл из указанного внешнего буфера,
//fileName - имя файла(не более 20 символов), lpBuffer - адрес
//буфера с данными, count - длина буфера на запись, возвращает 1 -
//если успех - 1 - если ошибка;
extern "C" DLLFUNC_API int osWriteExternFile(char* fileName, BYTE* lpBuffer, int count);

//5.3  - чтение из файла данных в
//оперативную память, nProcess - номер процесса(0 - 99), вызвавший
//метод(255 - система), fileName - имя файла(не более 20 символов),
//virtMemBuffer - адрес буфера в адресном пространстве процесса,
//если вызывается от имени системы - virtMemBuffer указывает на
//физ.память, count - длина буфера на чтение, offset - позиция в
//файле, с которой необходимо осуществлять чтение, возвращает
//количество прочитанных символов - 1 - если ошибка
extern "C" DLLFUNC_API int osReadFile(int nProcess, char* fileName, int virtMemBuffer, int count, int offset);

//5.4  - чтение из файла данных в указанный внешний буфер,
//fileName - имя файла(не более 20 символов), lpBuffer - адрес
//буфера с данными, count - длина буфера на для данных, возвращает
//количество прочитанных символов - 1 - если ошибка;
extern "C" DLLFUNC_API int osReadExternFile(char* fileName, BYTE* lpBuffer, int count);

//5.5  - удаление
//файла, nProcess - номер процесса(0 - 99), вызвавший метод(255 -
//система), fileName - имя файла(не более 20 символов), возвращает
//1 - если успешно - 1 - если ошибка.
extern "C" DLLFUNC_API int osDeleteFile(int nProcess, char* fileName);