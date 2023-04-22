#pragma once
#include <Windows.h>

namespace Globals {
	// Address
	inline HANDLE ProcessHandle;
	inline uintptr_t ClientAddress = 0;
	inline uintptr_t EngineAddress = 0;

	// Modules
	inline bool BHOPEnabled = false;
	inline bool TriggerBotEnabled = false;
	inline bool NorecoilEnabled = false;

	inline bool AimbotEnabled = false;
	inline bool AimbotFovCircle = false;
	inline int AimbotTarget = 2;
	inline int AimbotKey = 2;
	inline float AimbotSmoothness = 5.f;
	inline float AimbotFovSize = 8.f;
}