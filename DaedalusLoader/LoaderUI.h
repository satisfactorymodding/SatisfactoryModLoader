#pragma once
#include <Windows.h>
#include <inttypes.h>
#include <string>
#include <d3d11.h>
#include <D3D11Shader.h>
#include <D3Dcompiler.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3dcompiler.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
class LOADER_API LoaderUI
{
public:
	typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	D3D11PresentHook phookD3D11Present = NULL;

	DWORD_PTR* pSwapChainVtable = NULL;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* pRenderTargetView = NULL;

	WNDPROC hGameWindowProc = NULL;

	D3D11_VIEWPORT viewport;
	float screenCenterX = 0;
	float screenCenterY = 0;

	HRESULT(*ResizeBuffers)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT) = NULL;

	HRESULT LoaderResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

	void LoaderD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	static LRESULT CALLBACK hookWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void CreateUILogicThread();

	static LoaderUI* GetUI();

	bool initRendering = true;

	static void HookDX();

	bool IsDXHooked = 0;
	
private:
	static LoaderUI* UI;
};

