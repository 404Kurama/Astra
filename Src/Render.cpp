#include "Render.h"

#include "Globals.h"

#include <DirectOverlay/DirectOverlay.h>
#include <iostream>


void Render::DrawLoop(int width, int height) {
	POINT CursorPosition;
	GetCursorPos(&CursorPosition);

	if (Globals::AimbotFovCircle) {
		float FovCircleColor[4] = { 1.f, 0.f , 0.f, 1.f };
		
		// I don't know how to calculate size but nvm it just work
		DrawCircle(CursorPosition.x, CursorPosition.y, Globals::AimbotFovSize + 60, 1, FovCircleColor[0], FovCircleColor[1], FovCircleColor[2], FovCircleColor[3], false);
	}
}

void Render::Setup() {
	HWND CSGOWindow = FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9");

	DirectOverlaySetOption(D2DOV_FONT_COURIER | D2DOV_REQUIRE_FOREGROUND);
	DirectOverlaySetup(DrawLoop, CSGOWindow);
}