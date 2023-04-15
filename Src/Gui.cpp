#include "Gui.h"

#include <Windows.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>

LRESULT WINAPI WndProc(HWND window, UINT message, WPARAM wideParameter, LPARAM longParameter);

// Gui
void Gui::RenderGui() noexcept {
	WindowClass.hInstance = GetModuleHandle(0);
	WindowClass.lpfnWndProc = WndProc;
	WindowClass.lpszClassName = "Astra";

	RegisterClass(&WindowClass);

	Window = CreateWindowEx(
		WS_EX_TOPMOST,
		WindowClass.lpszClassName,
		WindowClass.lpszClassName,
		WS_POPUP,
		XPOS,
		YPOS,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		WindowClass.hInstance,
		NULL
	);

	if (!CreateDevice()) {
		DestroyDevice();
		UnregisterClass(WindowClass.lpszClassName, WindowClass.hInstance);
		return;
	}

	ShowWindow(Window, SW_SHOWDEFAULT);
	UpdateWindow(Window);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ::ImGui::GetIO();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX9_Init(Device);

	while (IsRunning) {
		MSG Message;

		while (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);

			if (Message.message == WM_QUIT) {
				IsRunning = false;
				return;
			}
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Resize
		ImGui::SetNextWindowPos({ 0, 0 });
		ImGui::SetNextWindowSize({ WIDTH, HEIGHT });

		//------------------//
		// --Start Render-- //
		ImGui::Begin("Astra", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
		ImGui::End();

		// --End Render-- //
		//----------------//

		ImGui::EndFrame();

		Device->SetRenderState(D3DRS_ZENABLE, FALSE);
		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		Device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

		if (Device->BeginScene() >= 0) {
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			Device->EndScene();
		}

		HRESULT result = Device->Present(NULL, NULL, NULL, NULL);

		if (result == D3DERR_DEVICELOST && Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ResetDevice();
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyDevice();
	DestroyWindow(Window);
	UnregisterClass(WindowClass.lpszClassName, WindowClass.hInstance);
}

// Device
bool Gui::CreateDevice() noexcept {
	D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!D3D)
		return false;

	ZeroMemory(&PresentParameters, sizeof(PresentParameters));

	PresentParameters.Windowed = TRUE;
	PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PresentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	PresentParameters.EnableAutoDepthStencil = TRUE;
	PresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	PresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &PresentParameters, &Device) < 0)
		return false;

	return true;
}

void Gui::DestroyDevice() noexcept {
	if (Device) {
		Device->Release();
		Device = NULL;
	}

	if (D3D) {
		D3D->Release();
		D3D = NULL;
	}
}

void Gui::ResetDevice() noexcept {
	ImGui_ImplDX9_InvalidateDeviceObjects();
	
	HRESULT result = Device->Reset(&PresentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

// Window Process
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM wideParameter, LPARAM longParameter);

LRESULT WINAPI WndProc(HWND window, UINT message, WPARAM wideParameter, LPARAM longParameter) {
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter)) {
		return true;
	}

	switch (message) {
		case WM_SIZE:
			if (Gui::Device != NULL && wideParameter != SIZE_MINIMIZED) {
				Gui::PresentParameters.BackBufferWidth = LOWORD(longParameter);
				Gui::PresentParameters.BackBufferHeight = HIWORD(longParameter);
				Gui::ResetDevice();
			}
			return 0;

		case WM_SYSCOMMAND:
			if ((wideParameter & 0xFFF0) == SC_KEYMENU)
				return 0;
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			exit(0);
			return 0;
	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}