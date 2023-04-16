#include "CombatModules.h"
#include "../Memory.hpp"
#include "../Gui.h"
#include "../Offsets.hpp"
#include "../Vector.h"

#include <iostream>
#include <thread>

constexpr Vector3 CalculateAngle(const Vector3& localPosition, const Vector3& enemyPosition, const Vector3& viewAngles) noexcept {
	return ((enemyPosition - localPosition).ToAngle() - viewAngles);
}

void CombatModules::StartCombatModules() noexcept {
	while (Gui::IsRunning) {
		LocalPlayer = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwLocalPlayer);

		if (LocalPlayer) {
			LocalPlayerHealth = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_iHealth);
			LocalPlayerLifestate = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_lifeState);
			LocalPlayerTeam = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_iTeamNum);
			LocalPlayerFlags = Memory::Read<std::int32_t>(LocalPlayer + Offsets::netvars::m_fFlags);

			if (Globals::AimbotEnabled) StartAimbotModule();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void CombatModules::StartAimbotModule() noexcept {
	int AimbotKey = Globals::AimbotKey;

	if (AimbotKey == 0) {
		AimbotKey = VK_RBUTTON;
	}
	else if (AimbotKey == 1) {
		AimbotKey = VK_LBUTTON;
	}
	else if (AimbotKey == 2) {
		AimbotKey = VK_XBUTTON1;
	}
	else if (AimbotKey == 3) {
		AimbotKey = VK_XBUTTON2;
	}

	if (!GetAsyncKeyState(AimbotKey))
		return;

	uintptr_t ClientState = Memory::Read<uintptr_t>(Globals::EngineAddress + Offsets::signatures::dwClientState);

	std::int32_t LocalPlayerId = Memory::Read<std::int32_t>(ClientState + Offsets::signatures::dwClientState_GetLocalPlayer);
	Vector3 LocalPlayerPosition = Memory::Read<Vector3>(LocalPlayer + Offsets::netvars::m_vecOrigin) + Memory::Read<Vector3>(LocalPlayer + Offsets::netvars::m_vecViewOffset);

	Vector3 ViewAngles = Memory::Read<Vector3>(ClientState + Offsets::signatures::dwClientState_ViewAngles);
	Vector3 AimPunch = Memory::Read<Vector3>(LocalPlayer + Offsets::netvars::m_aimPunchAngle) * 2;

	float BestFov = Globals::AimbotFovSize;
	Vector3 BestAngle = Vector3{ };

	for (int i = 1; i <= 64; i++) {
		uintptr_t Entity = Memory::Read<uintptr_t>(Globals::ClientAddress + Offsets::signatures::dwEntityList + i * 0x10);

		std::int32_t EntityTeam = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_iTeamNum);
		std::int32_t EntityLifeState = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_lifeState);
		std::int32_t EntitySpottedByMask = Memory::Read<std::int32_t>(Entity + Offsets::netvars::m_bSpottedByMask);
		bool EntityDormant = Memory::Read<bool>(Entity + Offsets::signatures::m_bDormant);

		if (EntityTeam == LocalPlayerTeam) continue;
		if (EntityDormant) continue;
		if (EntityLifeState) continue;

		if (EntitySpottedByMask & (1 << LocalPlayerId)) {
			int AimbotPart = Globals::AimbotTarget;

			if (AimbotPart == 0) {
				AimbotPart = 8;
			}
			else if (AimbotPart == 1) {
				AimbotPart = 5;
			}
			else if (AimbotPart == 2) {
				// Todo Random Part
				AimbotPart = 5;
			}

			uintptr_t BoneMatrix = Memory::Read<uintptr_t>(Entity + Offsets::netvars::m_dwBoneMatrix);

			Vector3 EntityPosition = Vector3{
				Memory::Read<float>(BoneMatrix + 0x30 * AimbotPart + 0x0C),
				Memory::Read<float>(BoneMatrix + 0x30 * AimbotPart + 0x1C),
				Memory::Read<float>(BoneMatrix + 0x30 * AimbotPart + 0x2C)
			};

			Vector3 Angle = CalculateAngle(LocalPlayerPosition, EntityPosition, ViewAngles + AimPunch);
			float Fov = std::hypot(Angle.x, Angle.y);

			if (Fov < BestFov) {
				BestFov = Fov;
				BestAngle = Angle;
			}
		}
	}

	if (!BestAngle.IsZero())
		Memory::Write<Vector3>(ClientState + Offsets::signatures::dwClientState_ViewAngles, ViewAngles + BestAngle / Globals::AimbotSmoothness);
}