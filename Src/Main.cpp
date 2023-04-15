#include "Gui.h"
#include "Memory.hpp"

#include "Modules/GeneralModules.h"

#include <iostream>
#include <thread>

int main() {
	std::cout << "[X] -->> Welcome to Astra <<-- [X]" << std::endl;
	//std::cout << "I don't know why i can't make this console hide with c++, I think you need to do it yourself!\n" << std::endl; // I don't know why but it work now!

	// Getting Game Process
	DWORD ProcessId = Memory::GetProcessId(L"csgo.exe");

	if (!ProcessId) {
		std::cout << "Waiting for CS:GO..." << std::endl;

		while (!ProcessId) {
			ProcessId = Memory::GetProcessId(L"csgo.exe");
			Sleep(200UL);
		}
	}

	DWORD BaseAddress = Memory::GetModuleAddress(ProcessId, L"csgo.exe");
	DWORD ClientAddress = Memory::GetModuleAddress(ProcessId, L"client.dll");
	DWORD EngineAddress = Memory::GetModuleAddress(ProcessId, L"engine.dll");

	if (EngineAddress == 0 || BaseAddress == 0 || EngineAddress == 0) {
		std::cout << "Waiting for CS:GO to load..." << std::endl;

		while (ClientAddress == 0 || BaseAddress == 0 || EngineAddress == 0) {
			BaseAddress = Memory::GetModuleAddress(ProcessId, L"csgo.exe");
			ClientAddress = Memory::GetModuleAddress(ProcessId, L"client.dll");
			EngineAddress = Memory::GetModuleAddress(ProcessId, L"engine.dll");
			Sleep(200UL);
		}
	}

	HANDLE Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);

	if (!Handle) {
		std::cout << "Couldn't get CS:GO handle." << std::endl;
		system("pause");
		return 0;
	}

	Globals::ProcessHandle = Handle;
	Globals::ClientAddress = ClientAddress;
	Globals::EngineAddress = EngineAddress;

	// Start
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Base Process Id: " << ProcessId << std::endl;
	std::cout << "Base Address: " << BaseAddress << std::endl;
	std::cout << "Client Address: " << ClientAddress << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	std::cout << "\nFound game process starting astra in 3s" << std::endl;
	//Sleep(3000UL);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// Modules
	std::thread(GeneralModules::StartGeneralModules).detach();

	// Render Gui
	Gui::RenderGui();

	return 0;
}