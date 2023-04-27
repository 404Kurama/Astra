#pragma once
#include <Windows.h>
#include <iostream>

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

	inline bool ESPEnabled = false;
	inline bool ESPTeam = false;
	inline bool ESPShowHealth = false;
	inline float ESPTeamColor[] = { 0.f, 1.f, 0.f };
	inline float ESPEnemyColor[] = { 1.f, 0.f, 0.f };

	inline bool GlowEnabled = false;
	inline bool GlowTeam = true;
	inline float GlowTeamColor[] = { 0.f, 1.f, 0.f, 1.f };
	inline float GlowEnemyColor[] = { 1.f, 0.f, 0.f, 1.f };

	inline bool ChamsEnabled = false;
	inline bool ChamsTeam = true;
	inline float ChamsTeamColor[] = { 0.f, 1.f, 0.f };
	inline float ChamsEnemyColor[] = { 1.f, 0.f, 0.f };

	inline bool AutoLoadConfig = true;
	inline bool AutoSaveConfig = false;
	inline std::string AutoLoadConfigFileName = "default.json";
}