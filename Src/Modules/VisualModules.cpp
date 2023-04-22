#include "VisualModules.h"
#include "../Memory.hpp"
#include "../Gui.h"
#include "../Offsets.hpp"

#include <iostream>
#include <thread>

void VisualModules::StartVisualModules() noexcept {
	while (Gui::IsRunning) {
		LocalPlayer = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwLocalPlayer);

		if (LocalPlayer) {
			LocalPlayerHealth = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_iHealth);
			LocalPlayerLifestate = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_lifeState);
			LocalPlayerTeam = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_iTeamNum);
			LocalPlayerFlags = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_fFlags);

			if (Globals::GlowEnabled) StartGlowModule();
			if (Globals::ChamsEnabled) StartChamsModule();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void VisualModules::StartGlowModule() noexcept {

}

void VisualModules::StartChamsModule() noexcept {

}