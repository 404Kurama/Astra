#include "VisualModules.h"
#include "../Memory.hpp"
#include "../Gui.h"
#include "../Offsets.hpp"

#include <iostream>
#include <thread>

struct Color {
	uint8_t r{ }, g{ }, b{ };
};

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
	uintptr_t GlowObjectManager = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwGlowObjectManager);

	for (int i = 1; i <= 64; i++) {
		uintptr_t Entity = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwEntityList + i * 0x10);

		std::int32_t EntityTeam = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_iTeamNum);
		std::int32_t EntityLifeState = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_lifeState);

		if (EntityLifeState) continue;
		if (EntityTeam == LocalPlayerTeam && !Globals::GlowTeam) continue;

		std::int32_t GlowIndex = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_iGlowIndex);

		float* GlowColor = (EntityTeam == LocalPlayerTeam) ? Globals::GlowTeamColor : Globals::GlowEnemyColor;

		Memory::Write<float>(GlowObjectManager + (GlowIndex * 0x38) + 0x8, GlowColor[0]);  // Red
		Memory::Write<float>(GlowObjectManager + (GlowIndex * 0x38) + 0xC, GlowColor[1]);  // Green
		Memory::Write<float>(GlowObjectManager + (GlowIndex * 0x38) + 0x10, GlowColor[2]); // Blue
		Memory::Write<float>(GlowObjectManager + (GlowIndex * 0x38) + 0x14, GlowColor[3]); // Alpha

		Memory::Write<bool>(GlowObjectManager + (GlowIndex * 0x38) + 0x28, true);
		Memory::Write<bool>(GlowObjectManager + (GlowIndex * 0x38) + 0x29, false);
	}
}

void VisualModules::StartChamsModule() noexcept {

}