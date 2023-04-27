#pragma once
#include <iostream>

namespace VisualModules {
	inline uintptr_t LocalPlayer;
	inline std::int32_t LocalPlayerHealth;
	inline std::int32_t LocalPlayerLifestate;
	inline std::int32_t LocalPlayerTeam;
	inline std::int32_t LocalPlayerFlags;

	void StartVisualModules() noexcept;

	void StartGlowModule() noexcept;
	void StartChamsModule() noexcept;
	void ResetChamsModule() noexcept;
}