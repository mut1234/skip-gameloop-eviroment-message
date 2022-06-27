// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Memx.h"


#include <iostream>


#include <filesystem>

#include <fstream>
#include <Windows.h>
#include <tlhelp32.h>
#include <thread>
#include <filesystem> 

#include <urlmon.h>
#include"Memx.h"


#include <thread>

#include <Windows.h>



#include <Windows.h>
#include <string>

DWORD MyGetProcessId(LPCTSTR ProcessName) // non-conflicting function name
{
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hsnap, &pt)) { // must call this first
		do {
			if (!lstrcmpi(pt.szExeFile, ProcessName)) {
				CloseHandle(hsnap);
				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}
	CloseHandle(hsnap); // close handle on failure
	return 0;
}

void PatchGameloopAntiCheat2()
{

	//Sleep(8000);
	Memory memory;
	DWORD pid = MyGetProcessId("AndroidEmulatorEx.exe");

	if (!memory.AttachProcess(pid))
	{
		MessageBoxA(0, "error attache proccess.", "Error", MB_ICONERROR);
		return;
	}

	memory.ReplacePattern(0x00000000, 0x7fffffff, new BYTE[]{ 0xE9,0xE7,0x2D,0x2B,0x00,0x8D,0x64 }, new BYTE[]{ 0xC2,0x08,0x00,0x2B,0x00,0x8D,0x64 }, true);


}
int main()
{
	PatchGameloopAntiCheat2();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
