#pragma once
#include <d3d9.h>

namespace Gui {
	// Window Position
	constexpr int XPOS = 0;
	constexpr int YPOS = 0;

	// Window Size
	constexpr int WIDTH = 500;
	constexpr int HEIGHT = 528;

	// Is running
	inline bool IsRunning = true;

	// Win Api
	inline HWND Window = nullptr;
	inline WNDCLASS WindowClass = {};

	// Direct X
	inline LPDIRECT3D9 D3D = nullptr;
	inline LPDIRECT3DDEVICE9 Device = nullptr;
	inline D3DPRESENT_PARAMETERS PresentParameters = {};

	// Gui
	void RenderGui() noexcept;

	// Device
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;
}