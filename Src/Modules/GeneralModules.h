#pragma once
#include <iostream>

namespace GeneralModules {
	inline uintptr_t LocalPlayer;
	inline std::int32_t LocalPlayerHealth;
	inline std::int32_t LocalPlayerLifestate;
	inline std::int32_t LocalPlayerTeam;
	inline std::int32_t LocalPlayerFlags;

	void StartGeneralModules() noexcept;

	void StartBhopModule() noexcept;
}