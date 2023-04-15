#include "Gui.h"
#include "Spectrum.h"

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
		25,
		25,
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

	// Style
	ImGuiStyle* Style = &ImGui::GetStyle();
	ImVec4* Colors = Style->Colors;

	Style->WindowRounding = 6.0f;
	Style->ChildRounding = 4.0f;
	Style->FrameRounding = 4.0f;
	Style->GrabRounding = 4.0f;
	Style->PopupRounding = 4.0f;
	Style->ScrollbarRounding = 4.0f;
	Style->GrabRounding = 4.0f;

	Colors[ImGuiCol_Text] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY800); // text on hovered controls is gray900
	Colors[ImGuiCol_TextDisabled] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY500);
	Colors[ImGuiCol_WindowBg] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY100);
	Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	Colors[ImGuiCol_PopupBg] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY50); // not sure about this. Note: applies to tooltips too.
	Colors[ImGuiCol_Border] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY300);
	Colors[ImGuiCol_BorderShadow] = ImGui::ColorConvertU32ToFloat4(Spectrum::Static::NONE); // We don't want shadows. Ever.
	Colors[ImGuiCol_FrameBg] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY75); // this isnt right, spectrum does not do this, but it's a good fallback
	Colors[ImGuiCol_FrameBgHovered] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY50);
	Colors[ImGuiCol_FrameBgActive] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY200);
	Colors[ImGuiCol_TitleBg] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY300); // those titlebar values are totally made up, spectrum does not have this.
	Colors[ImGuiCol_TitleBgActive] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY200);
	Colors[ImGuiCol_TitleBgCollapsed] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY400);
	Colors[ImGuiCol_MenuBarBg] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY100);
	Colors[ImGuiCol_ScrollbarBg] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY100); // same as regular background
	Colors[ImGuiCol_ScrollbarGrab] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY400);
	Colors[ImGuiCol_ScrollbarGrabHovered] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY600);
	Colors[ImGuiCol_ScrollbarGrabActive] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY700);
	Colors[ImGuiCol_CheckMark] = ImGui::ColorConvertU32ToFloat4(Spectrum::BLUE500);
	Colors[ImGuiCol_SliderGrab] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY700);
	Colors[ImGuiCol_SliderGrabActive] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY800);
	Colors[ImGuiCol_Button] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY75); // match default button to Spectrum's 'Action Button'.
	Colors[ImGuiCol_ButtonHovered] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY50);
	Colors[ImGuiCol_ButtonActive] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY200);
	Colors[ImGuiCol_Header] = ImGui::ColorConvertU32ToFloat4(Spectrum::BLUE400);
	Colors[ImGuiCol_HeaderHovered] = ImGui::ColorConvertU32ToFloat4(Spectrum::BLUE500);
	Colors[ImGuiCol_HeaderActive] = ImGui::ColorConvertU32ToFloat4(Spectrum::BLUE600);
	Colors[ImGuiCol_Separator] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY400);
	Colors[ImGuiCol_SeparatorHovered] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY600);
	Colors[ImGuiCol_SeparatorActive] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY700);
	Colors[ImGuiCol_ResizeGrip] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY400);
	Colors[ImGuiCol_ResizeGripHovered] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY600);
	Colors[ImGuiCol_ResizeGripActive] = ImGui::ColorConvertU32ToFloat4(Spectrum::GRAY700);
	Colors[ImGuiCol_PlotLines] = ImGui::ColorConvertU32ToFloat4(Spectrum::BLUE400);
	Colors[ImGuiCol_PlotLinesHovered] = ImGui::ColorConvertU32ToFloat4(Spectrum::BLUE600);
	Colors[ImGuiCol_PlotHistogram] = ImGui::ColorConvertU32ToFloat4(Spectrum::BLUE400);
	Colors[ImGuiCol_PlotHistogramHovered] = ImGui::ColorConvertU32ToFloat4(Spectrum::BLUE600);
	Colors[ImGuiCol_TextSelectedBg] = ImGui::ColorConvertU32ToFloat4((Spectrum::BLUE400 & 0x00FFFFFF) | 0x33000000);
	Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	Colors[ImGuiCol_NavHighlight] = ImGui::ColorConvertU32ToFloat4((Spectrum::GRAY900 & 0x00FFFFFF) | 0x0A000000);
	Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);


	// Main Loop
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
		ImGui::Begin("Astra", &IsRunning, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
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

		case WM_LBUTTONDOWN:
			Gui::Position = MAKEPOINTS(longParameter);
			return 0;

		case WM_MOUSEMOVE:
			if (wideParameter) {
				POINTS Points = MAKEPOINTS(longParameter);
				RECT Rect = ::RECT{};

				GetWindowRect(Gui::Window, &Rect);

				Rect.left += Points.x - Gui::Position.x;
				Rect.top += Points.y - Gui::Position.y;

				if (Gui::Position.x >= 0 && Gui::Position.x <= Gui::WIDTH && Gui::Position.y >= 0 && Gui::Position.y <= 19)
					SetWindowPos(Gui::Window, HWND_TOPMOST, Rect.left, Rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
			}
			return 0;
	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}