#pragma once
#include "Globals.h"

#include <TlHelp32.h>

namespace Memory {
	inline DWORD GetProcessId(const wchar_t* ProcessName) noexcept {
		DWORD Pid = 0;
		HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (Snapshot) {
			PROCESSENTRY32W Process;
			Process.dwSize = sizeof(PROCESSENTRY32W);

			while (Process32NextW(Snapshot, &Process)) {
				if (_wcsicmp(Process.szExeFile, ProcessName) == 0) {
					Pid = Process.th32ProcessID;
					break;
				}
			}

			CloseHandle(Snapshot);
		}

		return Pid;
	}

	inline DWORD GetModuleAddress(const DWORD ProcessId, const wchar_t* ModuleName) {
		DWORD Address = 0;
		HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);

		if (Snapshot) {
			MODULEENTRY32W Module;
			Module.dwSize = sizeof(MODULEENTRY32W);

			while (Module32NextW(Snapshot, &Module)) {
				if (_wcsicmp(Module.szModule, ModuleName) == 0) {
					Address = reinterpret_cast<DWORD>(Module.modBaseAddr);
					break;
				}
			}

			CloseHandle(Snapshot);
		}

		return Address;
	}

	template <typename T>
	inline T Read(const DWORD Address) noexcept {
		T Value = {};
		ReadProcessMemory(Globals::ProcessHandle, reinterpret_cast<LPCVOID>(Address), &Value, sizeof(T), nullptr);
		return Value;
	}

	template <typename T>
	inline void Write(const DWORD Address, const T& Value) noexcept {
		WriteProcessMemory(Globals::ProcessHandle, reinterpret_cast<LPVOID>(Address), &Value, sizeof(T), nullptr);
	}
}