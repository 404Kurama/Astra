#include "Render.h"

#include <DirectOverlay/DirectOverlay.h>
#include <iostream>


void Render::DrawLoop(int width, int height) {
	//DrawString("Test", 26.f, 50.f, 50.f, 255.f, 255.f, 255.f, 1.0f);
}

void Render::Setup() {
	HWND CSGOWindow = FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9");

	DirectOverlaySetOption(D2DOV_FONT_COURIER | D2DOV_REQUIRE_FOREGROUND);
	DirectOverlaySetup(DrawLoop, CSGOWindow);
}