#pragma once
#include <Windows.h>

namespace Globals {
	// Address
	inline HANDLE ProcessHandle;
	inline uintptr_t ClientAddress = 0;
	inline uintptr_t EngineAddress = 0;

	// Modules
	inline bool BHOPEnabled = false;
}