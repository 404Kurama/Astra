#include "VisualModules.h"
#include "../Memory.hpp"
#include "../Gui.h"
#include "../Offsets.hpp"

#include <iostream>
#include <thread>

struct Color {
	uint8_t r{ }, g{ }, b{ };
};

float Brightness = 0.f;
void VisualModules::StartVisualModules() noexcept {
	while (Gui::IsRunning) {
		LocalPlayer = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwLocalPlayer);

		if (LocalPlayer) {
			LocalPlayerHealth = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_iHealth);
			LocalPlayerLifestate = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_lifeState);
			LocalPlayerTeam = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_iTeamNum);
			LocalPlayerFlags = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_fFlags);

			if (Globals::GlowEnabled) StartGlowModule();
			if (Globals::ChamsEnabled) StartChamsModule(); else ResetChamsModule();
			
			uintptr_t a = static_cast<uintptr_t>(Globals::EngineAddress + Offsets::signatures::model_ambient_min - 0x2C);
			Memory::Write<int32_t>(Globals::EngineAddress + Offsets::signatures::model_ambient_min, *reinterpret_cast<uintptr_t*>(&Brightness) ^ a);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void VisualModules::ResetChamsModule() noexcept {
	// Omg reset chams module that doesn't exist in Meloternal OMGG!!!!!
	// https://github.com/404Kurama/Meloternal/blob/main/src/Modules.cpp#L106

	Brightness = 0.f;

	for (int i = 1; i <= 64; i++) {
		uintptr_t Entity = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwEntityList + i * 0x10);

		std::int32_t EntityTeam = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_iTeamNum);
		std::int32_t EntityLifeState = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_lifeState);

		if (EntityLifeState) continue;
		if (EntityTeam == LocalPlayerTeam && !Globals::GlowTeam) continue;

		Color color = Color{ uint8_t(255), uint8_t(255), uint8_t(255) };
		Memory::Write<Color>(Entity + Offsets::netvars::m_clrRender, color);
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
	Brightness = 10.f;

	for (int i = 1; i <= 64; i++) {
		uintptr_t Entity = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwEntityList + i * 0x10);

		std::int32_t EntityTeam = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_iTeamNum);
		std::int32_t EntityLifeState = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_lifeState);

		if (EntityLifeState) continue;
		if (EntityTeam == LocalPlayerTeam && !Globals::GlowTeam) continue;

		float* ChamsColor = (EntityTeam == LocalPlayerTeam) ? Globals::ChamsTeamColor : Globals::ChamsEnemyColor;
		int r, g, b;

		r = int(ChamsColor[0] * 255.0f + 0.5f);
		g = int(ChamsColor[1] * 255.0f + 0.5f);
		b = int(ChamsColor[2] * 255.0f + 0.5f);

		Color color = Color{ uint8_t(r), uint8_t(g), uint8_t(b) };

		Memory::Write<Color>(Entity + Offsets::netvars::m_clrRender, color);
	}
}