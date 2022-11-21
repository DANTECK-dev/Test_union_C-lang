// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "DllFunc.h"

using namespace std;

MEMORYSTATUSEX statex;
bool firstLog = true;
static string file_name;

/*------------------------------------------------------------------------*/

/*
    1. ���������� ������� - ������ ������� ����������� � ������
    ������������ �������, �� ������������� ����������� ��� ��������� �
    ����������� ������ :
*/

// - 1.1 �������� ������ ����������� ������(� ������);
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

// -1.2 �������� ������ ��������(� ������);
int GetPageSize()
{
    return 1024;
}

// -1.3 �������� ������ �����(� ������);
uint64_t GetDiskSize()
{
    uint64_t lpTotalNumberOfBytes;
    GetDiskFreeSpaceEx(NULL, NULL, (PULARGE_INTEGER)&lpTotalNumberOfBytes, NULL);
    return lpTotalNumberOfBytes;
}

// -1.4 �������� ������ ��������(� ������);
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
// -1.5 �������� ������ � ���(�� ����� 40� �� 500 ��);
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

// -1.6 ������� ���� �� ������ �� ���.������;
BYTE ReadMemoryByte(int &memPhysAdress)
{
    return (BYTE)memPhysAdress;
}

//1.7 - �������� ���� � ������ �� ���.������;
void WriteMemoryByte(int &memPhysAdress, BYTE value)
{
    *&memPhysAdress = (int)*&value;
    return;
}

//1.8 - ������� �� ������ �� ���������� ���.������ ��������� ����
//(memPhysAdress - �����, � �������� ���� ��������� ������, lpBuffer -
//�����, � ������� ���������� ��������� ��������� ������, count -
//���������� ����������� ����);
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

//1.9  - �������� � ������ �� ���������� ������ ��������� ����
//(memPhysAdress - �����, �� �������� ���������� ������, lpBuffer -
//�����, �� �������� ����������� ������, count - ���������� ����);
void WriteMemory(int &memPhysAdress, BYTE * lpBuffer, int count)
{
    for (int i = 0; i < count; i++)
    {
        *&memPhysAdress = (int)*&lpBuffer[i];
        memPhysAdress += sizeof(lpBuffer[i]);
    }
    return;
}

//1.10  - ������� �������
//� �����(��������, ������� �����������), ���������: memAdress -
//����� � ����������� ������, ������� � �������� ����������
//��������� ���������� ��������, nSector - ����� �������� �����, �
//�������� ��������� ������� ������;
void ReadDisk(int memAdress, int nSector)
{
    return;
}

//1.11  - ��������
//������� � �����(��������, ������� �����������), ���������:
//memAdress - ����� � ����������� ������, ������� � �������� ������
//������������ � �������, nSector - ����� �������� �����, � �������
//������������ ������.
void WriteDisk(int memAdress, int nSector)
{
    return;
}

/*
    2. ������� �� - ��������� �������, ������� ���������� �����������
    �������� �������� :
*/

//2.1  - ������ ��������� ����������, ���������
//������������� ���������;
void Start()
{
    return;
}

//2.2 - ��������� ��������� ����������, ���������
//��������� ����������.
void Stop()
{
    return;
}

/*
3. ������� ��, �������������� - ��������� �������, �������
���������� ����������� �������� �������� :
*/

//3.1 - �������� ���������� � ��������� � �������,
//������ ������ = 100, ���������� �������� "�������������"
//���������
void GetProcessStatus(BYTE* lpProcStatusBuffer, double* lpProcData)
{
    return;
}

//3.2  - �������� ���������� ������;
int GetPhysMemoryBlockCount()
{
    return 0;
}

//3.3  - �������� ��������
//������, lpBlockList - ������ �������� ������;
void GetPhysMemoryBlockList(PHYS_MEMORY_BLOCK* lpBlockList)
{
    return;
}

//3.4  - ��������
//���������� � ��������� �����(����������), 0 - ���������
//������, 1 - 100 - ������ ����������� �����(����� ��������� �
//������� � ��������), 255 - ��������������� ��������;
void GetDiskStatus(BYTE* lpStatusBuffer)
{
    return;
}


//3.5  - �������� �������, ������ �� ����� ��
//����� 100 (������� � 1 �� 100 ������������), lpFileNames - �����
//������, lpFirstSectors - ������ ������ ���������, lpSizes - �������
//������;
void GetDiskCatalog(char lpFileNames[][20], int* lpFirstSectors, int* lpSizes)
{
    return;
}

//3.6 - ������� �������, nData -
//�������������� ��������� ��� ��������(������� �� ���������
//������������), 1. ��������������� ������������ - �����
//������������ �� ����� �������� ������� �������, 2. SJF �
//������������� - �� ������������, 3. ����������� SJF - ������
//����� ���������� ��������, 4. ������������ ������������ �
//���������� ����������� - ����� ����������, 5. ��������������
//�������(2 ������: ������� ��������� � Round robin, ������
//��������� � FCFS) - ����� ����������, ������� ������ �������
//����� ��� ���������� ��������;
int osCreateProcess(int nData)
{
    return 0;
}

//3.7  - ������� ������� � ��������� �������
void osDeleteProcess(int nProcess)
{
    return;
}

/*
4. ������� ��, ���������� ������� - ��������� �������, �������
���������� ����������� �������� �������� :
*/

//4.1  - ������� �������� ������������ ���
//���������� ��������, nProcess - ����� �������� ��� ��������
//��������� �������� ������������, bBlockCount - ���������� ������
//��������� ������������, ��� ����������� �������������
//bBlockCount ������ ����� 1, ��� ����������� � �������������������� ������������� - ���������� ���������,
//lpBlockLength - ����� ������ �������� ������������;
void osMakeAddressSpace(int nProcess, int bBlockCount, int* lpBlockLength)
{
    return;
}

//4.2  - ��������� ���������� ������, nProcess - �����
//��������, � �������� ������������ �������� �����������
//��������������, nVirtualAdress - ����������� �����, �� ��������
//�������� ���������� ���������, nOperationType - �����������
//�������� ��� ������� � ������ ������(MemoryRead ���
//MemoryWrite), ������� ������ ������� ����� ���.������ ��� - 1
//���� ����������� ����� ��������� ������������ ����������� �
//����������� ������;
int osTranslateAddress(int nProcess, int nVirtualAdress, int nOperationType)
{
    return 0;
}

//4.3  - ��������� ���������� ������,
//nProcess - ����� ��������, � �������� ������������ ��������
//����������� ��������������, nSegment - ����� ��������, �
//�������� �������� ���������� ���������, nOffset - �������� �
//��������, nOperationType - ����������� �������� ��� ������� �
//������ ������(MemoryRead ��� MemoryWrite), ������� ������
//������� ����� ���.������ ��� - 1 ���� ����������� �����
//��������� ������������ ����������� � ����������� ������;

int osTranslateAddress2(int nProcess, int nSegment, int nOffset, int nOperationType)
{
    return 0;
}

/*
5. ������� ��, ���������� ������ / ������� - ��������� �������, �������
���������� ����������� �������� �������� :
*/

//5.1  - ������ ������ �� �����������
//������ � ��������� ����, nProcess - ����� ��������(0 - 99),
//��������� �����(255 - �������), fileName - ��� �����(�� �����
//20 ��������), virtMemBuffer - ����� ������ � ��������
//������������ ��������, ���� ���������� �� ����� ������� -
//virtMemBuffer ��������� �� ���.������, count - ����� ������ ��
//������, offset - ������� � �����, � ������� ����������
//������������ ������, ���������� 1 - ���� ����� - 1 - ���� ������;
int osWriteFile(int nProcess, char* fileName, int virtMemBuffer, int count, int offset)
{
    return 0;
}

//5.2  - ������ ������ � ���� �� ���������� �������� ������,
//fileName - ��� �����(�� ����� 20 ��������), lpBuffer - �����
//������ � �������, count - ����� ������ �� ������, ���������� 1 -
//���� ����� - 1 - ���� ������;
int osWriteExternFile(char* fileName, BYTE * lpBuffer, int count)
{
    return 0;
}

//5.3  - ������ �� ����� ������ �
//����������� ������, nProcess - ����� ��������(0 - 99), ���������
//�����(255 - �������), fileName - ��� �����(�� ����� 20 ��������),
//virtMemBuffer - ����� ������ � �������� ������������ ��������,
//���� ���������� �� ����� ������� - virtMemBuffer ��������� ��
//���.������, count - ����� ������ �� ������, offset - ������� �
//�����, � ������� ���������� ������������ ������, ����������
//���������� ����������� �������� - 1 - ���� ������
int osReadFile(int nProcess, char* fileName, int virtMemBuffer, int count, int offset)
{
    return 0;
}

//5.4  - ������ �� ����� ������ � ��������� ������� �����,
//fileName - ��� �����(�� ����� 20 ��������), lpBuffer - �����
//������ � �������, count - ����� ������ �� ��� ������, ����������
//���������� ����������� �������� - 1 - ���� ������;
int osReadExternFile(char* fileName, BYTE * lpBuffer, int count)
{
    return 0;
}

//5.5  - ��������
//�����, nProcess - ����� ��������(0 - 99), ��������� �����(255 -
//�������), fileName - ��� �����(�� ����� 20 ��������), ����������
//1 - ���� ������� - 1 - ���� ������.
int osDeleteFile(int nProcess, char* fileName)
{
    return 0;
}
