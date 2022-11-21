// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "DllFunc.h"

using namespace std;

MEMORYSTATUSEX statex;
bool firstLog = true;
static string file_name;

/*------------------------------------------------------------------------*/

/*
    1. Аппаратные функции - данные функции реализованы с модели
    операционной системы, их использование обязательно при обращении к
    виртуальной машине :
*/

// - 1.1 получить размер оперативной памяти(в байтах);
uint64_t GetMemorySize()
{
    statex.dwLength = sizeof(statex); // I misunderstand that

    GlobalMemoryStatusEx(&statex);
    //cout << "Physical RAM => " << (float)statex.ullTotalPhys / (1024 * 1024 * 1024) << endl;
    return statex.ullTotalPhys;
    //return EXIT_SUCCESS;
    //PULONGLONG TotalMemoryInKilobytes;
    //GetPhysicallyInstalledSystemMemory(TotalMemoryInKilobytes);
    //return (int) TotalMemoryInKilobytes;
}

// -1.2 получить размер страницы(в байтах);
int GetPageSize()
{
    return 1024;
}

// -1.3 получить размер диска(в байтах);
uint64_t GetDiskSize()
{
    uint64_t lpTotalNumberOfBytes;
    GetDiskFreeSpaceEx(NULL, NULL, (PULARGE_INTEGER)&lpTotalNumberOfBytes, NULL);
    return lpTotalNumberOfBytes;
}

// -1.4 получить размер кластера(в байтах);
uint64_t GetSectorSize()
{
    uint64_t lpSectorsPerCluster;
    uint64_t lpBytesPerSector;
    GetDiskFreeSpaceA(NULL, (LPDWORD)&lpSectorsPerCluster, (LPDWORD)&lpBytesPerSector, NULL, NULL);
    //return ((uint64_t)lpSectorsPerCluster * (uint64_t)lpBytesPerSector);
    return 512;
}

string currentDateTime() {
    time_t t = time(nullptr);
#pragma warning(disable : 4996)
    tm* now = localtime(&t);
#pragma warning(suppress : 4996)

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
    for (int i = 0; i < sizeof(buffer); i++)
        if (buffer[i] == ':') buffer[i] = ';';
    return buffer;
}
// -1.5 записать строку в лог(не более 40К за 500 мс);
void AddLog(char* s, int size)
{
    ofstream out;

    if (firstLog) 
    {
        srand(time(NULL));

        file_name = "log_";
        file_name += currentDateTime() + "_" + to_string(rand());
        file_name += ".txt";

        out.open(file_name, std::ios_base::app);

        firstLog = false;
    }
    else if(!firstLog)
    {
        out.open(file_name, std::ios_base::app);
    }

    for (int i = 0; i < size; i++)
        out << s[i];
    out << "\n";

    out.close();
    
    return;
}

// -1.6 считать байт из памяти по физ.адресу;
BYTE ReadMemoryByte(int &memPhysAdress)
{
    return (BYTE)memPhysAdress;
}

//1.7 - записать байт в память по физ.адресу;
void WriteMemoryByte(int &memPhysAdress, BYTE value)
{
    *&memPhysAdress = (int)*&value;
    return;
}

//1.8 - считать из памяти по указанному физ.адресу несколько байт
//(memPhysAdress - адрес, с которого надо считывать данные, lpBuffer -
//буфер, в который необходимо перенести указанные данные, count -
//количество считываемых байт);
BYTE* ReadMemory(int &memPhysAdress, int count)
{
    ReadProcessMemory()
    BYTE* lpBuffer = new BYTE[count];

    for (int i = 0; i < count; i++)
    {
        lpBuffer[i] = (BYTE)memPhysAdress;
        memPhysAdress += sizeof(lpBuffer[i]);
    }

    return lpBuffer;
}

//1.9  - записать в памяти из указанного буфера несколько байт
//(memPhysAdress - адрес, по которому происходит запись, lpBuffer -
//буфер, из которого переносятся данные, count - количество байт);
void WriteMemory(int &memPhysAdress, BYTE * lpBuffer, int count)
{
    for (int i = 0; i < count; i++)
    {
        *&memPhysAdress = (int)*&lpBuffer[i];
        memPhysAdress += sizeof(lpBuffer[i]);
    }
    return;
}

//1.10  - считать кластер
//с диска(внимание, функция блокирующая), параметры: memAdress -
//адрес в оперативной памяти, начиная с которого необходимо
//поместить содержимое кластера, nSector - номер кластера диска, с
//которого небходимо считать данные;
void ReadDisk(int memAdress, int nSector)
{
    return;
}

//1.11  - записать
//кластер с диска(внимание, функция блокирующая), параметры:
//memAdress - адрес в оперативной памяти, начиная с которого данные
//записываются в кластер, nSector - номер кластера диска, в который
//записываются данные.
void WriteDisk(int memAdress, int nSector)
{
    return;
}

/*
    2. Функции ОС - прототипы функций, которые необходимо реализовать
    согласно варианту :
*/

//2.1  - запуск подсистем управления, начальная
//инициализация подсистем;
void Start()
{
    return;
}

//2.2 - остановка подсистем управления, остановка
//подсистем управления.
void Stop()
{
    return;
}

/*
3. Функции ОС, информационные - прототипы функций, которые
необходимо реализовать согласно варианту :
*/

//3.1 - получить информацию о процессах в системе,
//размер буфера = 100, фактически является "планировщиком"
//процессов
void GetProcessStatus(BYTE* lpProcStatusBuffer, double* lpProcData)
{
    return;
}

//3.2  - получить количество блоков;
int GetPhysMemoryBlockCount()
{
    return 0;
}

//3.3  - получить описание
//блоков, lpBlockList - список описания блоков;
void GetPhysMemoryBlockList(PHYS_MEMORY_BLOCK* lpBlockList)
{
    return;
}

//3.4  - получить
//информацию о состоянии диска(посекторно), 0 - свободный
//сектор, 1 - 100 - сектор принадлежит файлу(номер совпадает с
//номером в каталоге), 255 - зарезервировано системой;
void GetDiskStatus(BYTE* lpStatusBuffer)
{
    return;
}


//3.5  - получить каталог, файлов на диске не
//более 100 (индексы с 1 по 100 включительно), lpFileNames - имена
//файлов, lpFirstSectors - номера первых кластеров, lpSizes - размеры
//файлов;
void GetDiskCatalog(char lpFileNames[][20], int* lpFirstSectors, int* lpSizes)
{
    return;
}

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
int osCreateProcess(int nData)
{
    return 0;
}

//3.7  - удалить процесс с указанным номером
void osDeleteProcess(int nProcess)
{
    return;
}

/*
4. Функции ОС, управление памятью - прототипы функций, которые
необходимо реализовать согласно варианту :
*/

//4.1  - создать адресное пространство для
//указанного процесса, nProcess - номер процесса для которого
//создается адресное пространство, bBlockCount - количество блоков
//адресного пространства, для страничного распределения
//bBlockCount всегда равен 1, для сегментного и сегментностраничного распределения - количество сегментов,
//lpBlockLength - длины блоков аресного пространства;
void osMakeAddressSpace(int nProcess, int bBlockCount, int* lpBlockLength)
{
    return;
}

//4.2  - выполнить трансляцию адреса, nProcess - номер
//процесса, в адресном пространстве которого выполняется
//преобразование, nVirtualAdress - виртуальный адрес, по которому
//пытаемся произвести обращение, nOperationType - выполняемая
//операция при доступе к ячейке памяти(MemoryRead или
//MemoryWrite), функция должна вернуть номер физ.ячейки или - 1
//если необходимая часть адресного пространства отсутствует в
//оперативной памяти;
int osTranslateAddress(int nProcess, int nVirtualAdress, int nOperationType)
{
    return 0;
}

//4.3  - выполнить трансляцию адреса,
//nProcess - номер процесса, в адресном пространстве которого
//выполняется преобразование, nSegment - номер сегмента, к
//которому пытаемся произвести обращение, nOffset - смещение в
//сегменте, nOperationType - выполняемая операция при доступе к
//ячейке памяти(MemoryRead или MemoryWrite), функция должна
//вернуть номер физ.ячейки или - 1 если необходимая часть
//адресного пространства отсутствует в оперативной памяти;

int osTranslateAddress2(int nProcess, int nSegment, int nOffset, int nOperationType)
{
    return 0;
}

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
int osWriteFile(int nProcess, char* fileName, int virtMemBuffer, int count, int offset)
{
    return 0;
}

//5.2  - запись данных в файл из указанного внешнего буфера,
//fileName - имя файла(не более 20 символов), lpBuffer - адрес
//буфера с данными, count - длина буфера на запись, возвращает 1 -
//если успех - 1 - если ошибка;
int osWriteExternFile(char* fileName, BYTE * lpBuffer, int count)
{
    return 0;
}

//5.3  - чтение из файла данных в
//оперативную память, nProcess - номер процесса(0 - 99), вызвавший
//метод(255 - система), fileName - имя файла(не более 20 символов),
//virtMemBuffer - адрес буфера в адресном пространстве процесса,
//если вызывается от имени системы - virtMemBuffer указывает на
//физ.память, count - длина буфера на чтение, offset - позиция в
//файле, с которой необходимо осуществлять чтение, возвращает
//количество прочитанных символов - 1 - если ошибка
int osReadFile(int nProcess, char* fileName, int virtMemBuffer, int count, int offset)
{
    return 0;
}

//5.4  - чтение из файла данных в указанный внешний буфер,
//fileName - имя файла(не более 20 символов), lpBuffer - адрес
//буфера с данными, count - длина буфера на для данных, возвращает
//количество прочитанных символов - 1 - если ошибка;
int osReadExternFile(char* fileName, BYTE * lpBuffer, int count)
{
    return 0;
}

//5.5  - удаление
//файла, nProcess - номер процесса(0 - 99), вызвавший метод(255 -
//система), fileName - имя файла(не более 20 символов), возвращает
//1 - если успешно - 1 - если ошибка.
int osDeleteFile(int nProcess, char* fileName)
{
    return 0;
}
