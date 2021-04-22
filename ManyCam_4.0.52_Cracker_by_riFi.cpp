#include <iostream>
#include <vector>
#include <Windows.h>
#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <winuser.h>
#include <io.h>
#include <tlhelp32.h>
#include <tchar.h>


DWORD GetModuleBase(const wchar_t* ModuleName, DWORD ProcessId) {	//Fonction pour trouver la base adresse  
	// This structure contains lots of goodies about a module
	MODULEENTRY32 ModuleEntry = { 0 };

	// Grab a snapshot of all the modules in the specified process
	HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);

	if (!SnapShot)
		return NULL;

	// You have to initialize the size, otherwise it will not work
	ModuleEntry.dwSize = sizeof(ModuleEntry);

	// Get the first module in the process
	if (!Module32First(SnapShot, &ModuleEntry))
		return NULL;

	do {
		// Check if the module name matches the one we're looking for
		if (!wcscmp(ModuleEntry.szModule, ModuleName)) {
			// If it does, close the snapshot handle and return the base address
			CloseHandle(SnapShot);
			return (DWORD)ModuleEntry.modBaseAddr;
		}
		// Grab the next module in the snapshot
	} while (Module32Next(SnapShot, &ModuleEntry));

	// We couldn't find the specified module, so return NULL
	CloseHandle(SnapShot);
	return NULL;
}



DWORD baseAddressAdded(DWORD BaseAddress, DWORD address) {

	DWORD bAdd = BaseAddress + address ;
	return bAdd;
}




void memWrite() {

	int totalPatch = 0;

	HWND hWnd = FindWindow(0, L"ManyCam 4.0");
	DWORD proccess_ID;
	GetWindowThreadProcessId(hWnd, &proccess_ID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proccess_ID);

	DWORD baseAddress = GetModuleBase(L"ManyCam.exe", proccess_ID);
	DWORD Crack = baseAddress + 0xe51b6; 
	int crackOffset = 0xEB;
	//std::cout << baseAddress+ 0xe51b6;

	int zero = 0x00;
	char newdata[19] = { 0x64,0x20,0x77,0x69,0x74,0x68,0x20,0x6c,0x6f,0x76,0x65,0x20,0x62,0x79,0x20,0x72,0x69,0x46,0x69 };


	if (WriteProcessMemory(hProcess, (LPVOID)Crack, &crackOffset, 1, NULL)) { totalPatch = totalPatch + 1; } // OPTIONS VIDEO

	//*******************************************************************************************************
	//CRACK BANNIERE
	int bann = 0xEB;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0x105F07), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }
	bann = 0x32;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0x105F6B), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }
	bann = 0xC0;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0x105F6C), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }
	bann = 0xEB;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0x135506), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }

	//*******************************************************************************************************

	bann = 0x43;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1180), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }
	bann = 0x72;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1181), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }
	bann = 0x61;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1181), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }
	bann = 0x63;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1181), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }
	bann = 0x6B;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1181), (LPCVOID)&bann, 1, NULL)) { totalPatch = totalPatch + 1; }

	//*******************************************************************************************************
	// PARTIE TEXTE
	int value = 0x43;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1180), (LPCVOID)&value, 1, NULL)) { totalPatch = totalPatch + 1; }
	value = 0x72;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1181), (LPCVOID)&value, 1, NULL)) { totalPatch = totalPatch + 1; }
	value = 0x61;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1182), (LPCVOID)&value, 1, NULL)) { totalPatch = totalPatch + 1; }
	value = 0x63;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1183), (LPCVOID)&value, 1, NULL)) { totalPatch = totalPatch + 1; }
	value = 0x6b;
	if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, 0xBA1184), (LPCVOID)&value, 1, NULL)) { totalPatch = totalPatch + 1; }
	
	//*******************************************************************************************************

	int waterMark = 12194182;
	for (int i = 0; i < 19; i++) {
		if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, waterMark), &newdata[i], 1, NULL)) { totalPatch = totalPatch + 1; }
		//std::cout << std::endl << baseAddress << " " << waterMark << " " << i ;
		waterMark =  waterMark+1;
	}
	//*******************************************************************************************************


	int eraseChar = 0xBA1199; // Caractères vides

	for (int j = 0; j < 27; j++) {

		if (WriteProcessMemory(hProcess, (LPVOID)baseAddressAdded(baseAddress, eraseChar), &zero, 1, NULL)) { totalPatch = totalPatch + 1; }
		eraseChar = eraseChar + 1;
	}


	std::string ttltmp = std::to_string(totalPatch);
	std::string ttl = "Injection réussie ! \n(" + ttltmp + "/61)";
	MessageBoxA(NULL, &ttl[0], "Succès", MB_OK + MB_ICONINFORMATION);
	exit(0);


}


void findWindow(){


	std::cout << "ManyCam 4.0.52 Cracker Injector" << std::endl ;
	std::cout << "-------------------------------" << std::endl ;
	std::cout << " _                    _  ___ _ " << std::endl ;
	std::cout << "| |                  (_)/ __|_)"<< std::endl ;
	std::cout << "| | _  _   _     ____ _| |__ _ "<< std::endl ;
	std::cout << "| || \\| | | |   / ___) |  __) |" << std::endl ;
	std::cout << "| |_) ) |_| |  | |   | | |  | |"<< std::endl ;
	std::cout << "|____/ \\__  |  |_|   |_|_|  |_|"<< std::endl ;
	std::cout << "      (____/                   "<< std::endl ;
	std::cout << "-------------------------------" << std::endl ;
	std::cout << "Gr33tz : ZolaBeille & Mohatours" << std::endl;
	std::cout << "-------------------------------" << std::endl;

	HWND hWnd = FindWindow(0, L"ManyCam 4.0");

	std::string state ;

	if (hWnd==0) {
		std::cout << "-> Statut : Non detecte (Veuillez lancer ManyCam)" ;
		Sleep(500);
		system("cls") ;
		findWindow() ;
	} else {
		std::cout << "-> Statut : Non detecte (Veuillez lancer ManyCam)" ;
		std::cout << std::endl ;
		std::cout << "-> Statut : Injection effectuee !" ;
		memWrite();
		

	}

}


int main() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);

	findWindow();	
	//rien();

}