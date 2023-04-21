#pragma once
#pragma once
#include <iostream>

namespace CombatModules {
	inline uintptr_t LocalPlayer;
	inline std::int32_t LocalPlayerHealth;
	inline std::int32_t LocalPlayerLifestate;
	inline std::int32_t LocalPlayerTeam;
	inline std::int32_t LocalPlayerFlags;

	void StartCombatModules() noexcept;
	void StartSecondLoop() noexcept;
	
	void StartAimbotModule() noexcept;
	void StartTriggerbotModule() noexcept;
}