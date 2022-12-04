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
    1. ���������� ������� - ������ ������� ����������� � ������
    ������������ �������, �� ������������� ����������� ��� ��������� �
    ����������� ������ :
*/

//1.1 - �������� ������ ����������� ������(� ������);
extern "C" DLLFUNC_API uint64_t GetMemorySize();

//1.2 - �������� ������ ��������(� ������);
extern "C" DLLFUNC_API int GetPageSize();

//1.3 - �������� ������ �����(� ������);
extern "C" DLLFUNC_API uint64_t GetDiskSize();

//1.4 - �������� ������ ��������(� ������);
extern "C" DLLFUNC_API uint64_t GetSectorSize();

//1.5  -�������� ������ � ���(�� ����� 40� �� 500 ��);
extern "C" DLLFUNC_API void AddLog(char* s, int size);

//1.6  -������� ���� �� ������ �� ���.������;
extern "C" DLLFUNC_API BYTE ReadMemoryByte(int &memPhysAdress);

//1.7 - �������� ���� � ������ �� ���.������;
extern "C" DLLFUNC_API void WriteMemoryByte(int &memPhysAdress, BYTE value);

//1.8 - ������� �� ������ �� ���������� ���.������ ��������� ����
//(memPhysAdress - �����, � �������� ���� ��������� ������, lpBuffer -
//�����, � ������� ���������� ��������� ��������� ������, count -
//���������� ����������� ����);
extern "C" DLLFUNC_API BYTE* ReadMemory(int &memPhysAdress, int count);

//1.9  - �������� � ������ �� ���������� ������ ��������� ����
//(memPhysAdress - �����, �� �������� ���������� ������, lpBuffer -
//�����, �� �������� ����������� ������, count - ���������� ����);
extern "C" DLLFUNC_API void WriteMemory(int &memPhysAdress, BYTE* lpBuffer, int count);

//1.10  - ������� �������
//� �����(��������, ������� �����������), ���������: memAdress -
//����� � ����������� ������, ������� � �������� ����������
//��������� ���������� ��������, nSector - ����� �������� �����, �
//�������� ��������� ������� ������;
extern "C" DLLFUNC_API void ReadDisk(int memAdress, int nSector);

//1.11  - ��������
//������� � �����(��������, ������� �����������), ���������:
//memAdress - ����� � ����������� ������, ������� � �������� ������
//������������ � �������, nSector - ����� �������� �����, � �������
//������������ ������.
extern "C" DLLFUNC_API void WriteDisk(int memAdress, int nSector);

/*
    2. ������� �� - ��������� �������, ������� ���������� �����������
    �������� �������� :
*/

//2.1  - ������ ��������� ����������, ���������
//������������� ���������;
extern "C" DLLFUNC_API void Start();

//2.2 - ��������� ��������� ����������, ���������
//��������� ����������.
extern "C" DLLFUNC_API void Stop();

/*
    3. ������� ��, �������������� - ��������� �������, �������
    ���������� ����������� �������� �������� :
*/

extern enum PROCESS_STATUS {
    NotExist = 0, 
    Execute = 1, 
    Ready = 2, 
    Wait = 3
};

//3.1 - �������� ���������� � ��������� � �������,
//������ ������ = 100, ���������� �������� "�������������"
//���������
extern "C" DLLFUNC_API void GetProcessStatus(BYTE* lpProcStatusBuffer, double* lpProcData); 

// ��������� ��� �������� ��������� ���. ������
extern "C" struct PHYS_MEMORY_BLOCK {
    int nStart; // ������ ����� � ����������� ������
    int nLength; // ����� �����
    int nProcess; // ����� �������� (0-99), �������� ������� ���� (255 - �������)
};

//3.2  - �������� ���������� ������;
extern "C" DLLFUNC_API int GetPhysMemoryBlockCount();

//3.3  - �������� ��������
//������, lpBlockList - ������ �������� ������;
extern "C" DLLFUNC_API void GetPhysMemoryBlockList(PHYS_MEMORY_BLOCK* lpBlockList);

//3.4  - ��������
//���������� � ��������� �����(����������), 0 - ���������
//������, 1 - 100 - ������ ����������� �����(����� ��������� �
//������� � ��������), 255 - ��������������� ��������;
extern "C" DLLFUNC_API void GetDiskStatus(BYTE* lpStatusBuffer);


//3.5  - �������� �������, ������ �� ����� ��
//����� 100 (������� � 1 �� 100 ������������), lpFileNames - �����
//������, lpFirstSectors - ������ ������ ���������, lpSizes - �������
//������;
extern "C" DLLFUNC_API void GetDiskCatalog(char lpFileNames[][20], int* lpFirstSectors, int* lpSizes);

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
extern "C" DLLFUNC_API int osCreateProcess(int nData);

//3.7  - ������� ������� � ��������� �������
extern "C" DLLFUNC_API void osDeleteProcess(int nProcess);

/*
    4. ������� ��, ���������� ������� - ��������� �������, �������
    ���������� ����������� �������� �������� :
*/

//4.1  - ������� �������� ������������ ���
//���������� ��������, nProcess - ����� �������� ��� ��������
//��������� �������� ������������, bBlockCount - ���������� ������
//��������� ������������, ��� ����������� �������������
//bBlockCount ������ ����� 1, ��� ����������� � �������������������� ������������� - ���������� ���������, lpBlockLength
//- ����� ������ �������� ������������;
extern "C" DLLFUNC_API void osMakeAddressSpace(int nProcess, int bBlockCount, int* lpBlockLength);

extern enum MEMORY_OPERATION {
    MemoryRead = 0, 
    MemoryWrite = 1
};

//4.2  - ��������� ���������� ������, nProcess - �����
//��������, � �������� ������������ �������� �����������
//��������������, nVirtualAdress - ����������� �����, �� ��������
//�������� ���������� ���������, nOperationType - �����������
//�������� ��� ������� � ������ ������(MemoryRead ���
//MemoryWrite), ������� ������ ������� ����� ���.������ ��� - 1
//���� ����������� ����� ��������� ������������ ����������� �
//����������� ������;
extern "C" DLLFUNC_API int osTranslateAddress(int nProcess, int nVirtualAdress, int nOperationType);

//4.3  - ��������� ���������� ������,
//nProcess - ����� ��������, � �������� ������������ ��������
//����������� ��������������, nSegment - ����� ��������, �
//�������� �������� ���������� ���������, nOffset - �������� �
//��������, nOperationType - ����������� �������� ��� ������� �
//������ ������(MemoryRead ��� MemoryWrite), ������� ������
//������� ����� ���.������ ��� - 1 ���� ����������� �����
//��������� ������������ ����������� � ����������� ������;
extern "C" DLLFUNC_API int osTranslateAddress2(int nProcess, int nSegment, int nOffset, int nOperationType);

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
extern "C" DLLFUNC_API int osWriteFile(int nProcess, char* fileName, int virtMemBuffer, int count, int offset);

//5.2  - ������ ������ � ���� �� ���������� �������� ������,
//fileName - ��� �����(�� ����� 20 ��������), lpBuffer - �����
//������ � �������, count - ����� ������ �� ������, ���������� 1 -
//���� ����� - 1 - ���� ������;
extern "C" DLLFUNC_API int osWriteExternFile(char* fileName, BYTE* lpBuffer, int count);

//5.3  - ������ �� ����� ������ �
//����������� ������, nProcess - ����� ��������(0 - 99), ���������
//�����(255 - �������), fileName - ��� �����(�� ����� 20 ��������),
//virtMemBuffer - ����� ������ � �������� ������������ ��������,
//���� ���������� �� ����� ������� - virtMemBuffer ��������� ��
//���.������, count - ����� ������ �� ������, offset - ������� �
//�����, � ������� ���������� ������������ ������, ����������
//���������� ����������� �������� - 1 - ���� ������
extern "C" DLLFUNC_API int osReadFile(int nProcess, char* fileName, int virtMemBuffer, int count, int offset);

//5.4  - ������ �� ����� ������ � ��������� ������� �����,
//fileName - ��� �����(�� ����� 20 ��������), lpBuffer - �����
//������ � �������, count - ����� ������ �� ��� ������, ����������
//���������� ����������� �������� - 1 - ���� ������;
extern "C" DLLFUNC_API int osReadExternFile(char* fileName, BYTE* lpBuffer, int count);

//5.5  - ��������
//�����, nProcess - ����� ��������(0 - 99), ��������� �����(255 -
//�������), fileName - ��� �����(�� ����� 20 ��������), ����������
//1 - ���� ������� - 1 - ���� ������.
extern "C" DLLFUNC_API int osDeleteFile(int nProcess, char* fileName);