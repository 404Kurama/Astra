#include "GeneralModules.h"
#include "../Memory.hpp"
#include "../Gui.h"
#include "../Offsets.hpp"

#include <iostream>
#include <thread>

void GeneralModules::StartGeneralModules() noexcept {
	while (Gui::IsRunning) {
		LocalPlayer = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwLocalPlayer);

		if (LocalPlayer) {
			LocalPlayerHealth = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_iHealth);
			LocalPlayerLifestate = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_lifeState);
			LocalPlayerTeam = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_iTeamNum);
			LocalPlayerFlags = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_fFlags);

			if (Globals::BHOPEnabled) StartBhopModule();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void GeneralModules::StartBhopModule() noexcept {
	if (LocalPlayerHealth < 0 || LocalPlayerLifestate != 0) return;

	if (GetAsyncKeyState(VK_SPACE)) {
		if (LocalPlayerFlags & (1 << 0)) { // On Ground
			Memory::Write(Globals::ClientAddress + Offsets::signatures::dwForceJump, 6);
		}
		else {
			Memory::Write(Globals::ClientAddress + Offsets::signatures::dwForceJump, 4);
		}
	}
}