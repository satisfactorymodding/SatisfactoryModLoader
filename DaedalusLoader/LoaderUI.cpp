#include "LoaderUI.h"
#include "Utilities/Logger.h"
#include "Memory/mem.h"
#include "Utilities/Dumper.h"
#include "Utilities/Globals.h"
#include "Utilities/MinHook.h"
#include "Utilities/Version.h"

LoaderUI* LoaderUI::UI;

LoaderUI* LoaderUI::GetUI()
{
	if (!UI)
	{
		UI = new LoaderUI();
	}
	return UI;
}

namespace TickVars
{
	bool f1_pressed;
	bool bDumpObjects;
	bool bDumpEngineInfo;
	bool bDumpWorldActors;
	bool bExecuteConsoleCommand;
	std::wstring CurrentCommand;
};

namespace UITools
{
	void ObjectDump()
	{
		TickVars::bDumpObjects = true;
	}

	void EngineDump()
	{
		TickVars::bDumpEngineInfo = true;
	}

	void WorldDump()
	{
		TickVars::bDumpWorldActors = true;
	}

	void ExecuteCommand(std::wstring command)
	{
		TickVars::CurrentCommand = command;
		TickVars::bExecuteConsoleCommand = true;
	}
};

void UILogicTick()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_F1) != 0)
			TickVars::f1_pressed = true;
		else if (TickVars::f1_pressed)
		{
			TickVars::f1_pressed = false;
			if (Global::GetGlobals()->bIsMenuOpen)
			{
				Global::GetGlobals()->bIsMenuOpen = false;
			}
			else
			{
				if (!LoaderUI::GetUI()->IsDXHooked)
				{
					LoaderUI::HookDX();
				}
				Global::GetGlobals()->bIsMenuOpen = true;
			}
		}

		if (TickVars::bDumpObjects)
		{
			TickVars::bDumpObjects = false;
			Dumper::GetDumper()->DumpObjectArray();
		}

		if (TickVars::bDumpEngineInfo)
		{
			TickVars::bDumpEngineInfo = false;
			Dumper::GetDumper()->DumpEngineInfo();
		}

		if (TickVars::bDumpWorldActors)
		{
			TickVars::bDumpWorldActors = false;
			Dumper::GetDumper()->DumpWorldActors();
		}

		if (TickVars::bExecuteConsoleCommand)
		{
			TickVars::bExecuteConsoleCommand = false;
			UE4::UGameplayStatics::ExecuteConsoleCommand(TickVars::CurrentCommand.c_str(), nullptr);
			TickVars::CurrentCommand = L"";
		}
		Sleep(1000 / 60);
	}
}

HRESULT LoaderUI::LoaderResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (!LoaderUI::GetUI()->initRendering)
	{
		if (LoaderUI::GetUI()->pRenderTargetView) {
			LoaderUI::GetUI()->pContext->OMSetRenderTargets(0, 0, 0);
			LoaderUI::GetUI()->pRenderTargetView->Release();
		}

		HRESULT hr = ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

		ID3D11Texture2D* pBuffer;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
		// Perform error handling here!

		LoaderUI::GetUI()->pDevice->CreateRenderTargetView(pBuffer, NULL, &LoaderUI::GetUI()->pRenderTargetView);
		// Perform error handling here!
		pBuffer->Release();

		LoaderUI::GetUI()->pContext->OMSetRenderTargets(1, &LoaderUI::GetUI()->pRenderTargetView, NULL);

		// Set up the viewport.
		D3D11_VIEWPORT vp;
		vp.Width = Width;
		vp.Height = Height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		LoaderUI::GetUI()->pContext->RSSetViewports(1, &vp);
		return hr;
	}
	else
	{
		HRESULT hr = ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
		return hr;
	}
}

void ShowLogicMods()
{
	if (!ImGui::CollapsingHeader("Logic Mods"))
		return;

	for (size_t i = 0; i < Global::GetGlobals()->ModInfoList.size(); i++)
	{
		std::string str(Global::GetGlobals()->ModInfoList[i].ModName.begin(), Global::GetGlobals()->ModInfoList[i].ModName.end());
		std::string ModLabel = str + "##" + std::to_string(i);
		if (ImGui::TreeNode(ModLabel.c_str()))
		{
			std::string Author = "Created By: " + Global::GetGlobals()->ModInfoList[i].ModAuthor;
			ImGui::Text(Author.c_str());
			ImGui::Separator();
			std::string Description = "Description: " + Global::GetGlobals()->ModInfoList[i].ModDescription;
			ImGui::Text(Description.c_str());
			ImGui::Separator();
			std::string Version = "Version: " + Global::GetGlobals()->ModInfoList[i].ModVersion;
			ImGui::Text(Version.c_str());
			ImGui::Separator();
			if (ImGui::TreeNode("Mod Buttons"))
			{
				if (Global::GetGlobals()->ModInfoList[i].IsEnabled && Global::GetGlobals()->ModInfoList[i].CurrentModActor && Global::GetGlobals()->ModInfoList[i].ContainsButton)
				{
					for (size_t bi = 0; bi < Global::GetGlobals()->ModInfoList[i].ModButtons.size(); bi++)
					{
						auto currentmodbutton = Global::GetGlobals()->ModInfoList[i].ModButtons[bi];
						std::string ButtonLabel = currentmodbutton + "##" + std::to_string(i + bi);
						if (ImGui::Button(ButtonLabel.c_str()))
						{
							std::wstring FuncNameAndArgs = L"ModMenuButtonPressed " + std::to_wstring(bi);
							Global::GetGlobals()->ModInfoList[i].CurrentModActor->CallFunctionByNameWithArguments(FuncNameAndArgs.c_str(), nullptr, NULL, true);
						}
					}
					ImGui::Separator();
				}
				ImGui::TreePop();
			}
			std::string ActiveLabel = "Enable##" + std::to_string(i);
			ImGui::Checkbox(ActiveLabel.c_str(), &Global::GetGlobals()->ModInfoList[i].IsEnabled);
			ImGui::TreePop();
		}
	}
}

void ShowCoreMods()
{
	if (!ImGui::CollapsingHeader("Core Mods"))
		return;

	for (size_t i = 0; i < Global::GetGlobals()->CoreMods.size(); i++)
	{
		std::string str(Global::GetGlobals()->CoreMods[i]->ModName.begin(), Global::GetGlobals()->CoreMods[i]->ModName.end());
		std::string ModLabel = str + "##cm" + std::to_string(i);
		if (ImGui::TreeNode(ModLabel.c_str()))
		{

			std::string Author = "Created By: " + Global::GetGlobals()->CoreMods[i]->ModAuthors;
			ImGui::Text(Author.c_str());
			ImGui::Separator();
			std::string Description = "Description: " + Global::GetGlobals()->CoreMods[i]->ModDescription;
			ImGui::Text(Description.c_str());
			ImGui::Separator();
			std::string Version = "Version: " + Global::GetGlobals()->CoreMods[i]->ModVersion;
			ImGui::Text(Version.c_str());
			ImGui::Separator();

			if (Global::GetGlobals()->CoreMods[i]->UseMenuButton && Global::GetGlobals()->CoreMods[i]->IsFinishedCreating)
			{
				std::string ButtonLabel = str + " Button" + "##cm" + std::to_string(i);
				if (ImGui::Button(ButtonLabel.c_str()))
				{
					Global::GetGlobals()->CoreMods[i]->OnModMenuButtonPressed();
				}
			}

			ImGui::TreePop();
		}
	}
}

void ShowTools()
{
	if (!ImGui::CollapsingHeader("Tools"))
		return;

	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Spacing();
	if (ImGui::Button("Dump Objects"))
	{
		UITools::ObjectDump();
	}
	if (ImGui::Button("Dump Engine Info"))
	{
		UITools::EngineDump();
	}
	if (ImGui::Button("Dump World Actors"))
	{
		UITools::WorldDump();
	}

	static char Command[128];
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Text("Execute Console Command");
	ImGui::InputText("", Command, IM_ARRAYSIZE(Command));
	if (ImGui::Button("Execute"))
	{
		std::string strCommand(Command);
		std::wstring wstrCommand = std::wstring(strCommand.begin(), strCommand.end());
		UITools::ExecuteCommand(wstrCommand);
	}
}

void DrawImGui()
{
	ImGui::Begin("Unreal Mod Loader", NULL, NULL);
	ImGui::Spacing();
	ImGui::Text("Unreal Mod Loader V: %s", MODLOADER_VERSION);
	ShowLogicMods();
	ShowCoreMods();
	ShowTools();

	ImGui::End();
}

LRESULT CALLBACK LoaderUI::hookWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CallWindowProc(ImGui_ImplWin32_WndProcHandler, hWnd, uMsg, wParam, lParam);

	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
		return true;
	}
	return CallWindowProc(LoaderUI::GetUI()->hGameWindowProc, hWnd, uMsg, wParam, lParam);
}


HRESULT hookResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	return LoaderUI::GetUI()->LoaderResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

void LoaderUI::LoaderD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (LoaderUI::GetUI()->initRendering)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&LoaderUI::GetUI()->pDevice)) &&
			SUCCEEDED(pSwapChain->GetDevice(__uuidof(LoaderUI::GetUI()->pDevice), (void**)&LoaderUI::GetUI()->pDevice)))
		{
			LoaderUI::GetUI()->pDevice->GetImmediateContext(&LoaderUI::GetUI()->pContext);
			Log::Info("D3D11Device Initialized");
		}
		else
		{
			Log::Error("Failed to initialize D3D11Device");
		}

		ID3D11Texture2D* pRenderTargetTexture = NULL;
		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)) &&
			SUCCEEDED(LoaderUI::GetUI()->pDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &LoaderUI::GetUI()->pRenderTargetView)))
		{
			pRenderTargetTexture->Release();
			Log::Info("D3D11RenderTargetView Initialized");
		}
		else
		{
			Log::Error("Failed to initialize D3D11RenderTargetView");
		}

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

		HWND hGameWindow = MEM::FindWindow(GetCurrentProcessId(), L"UnrealWindow");
		LoaderUI::GetUI()->hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)LoaderUI::hookWndProc);
		ImGui_ImplWin32_Init(hGameWindow);

		//ImGui_ImplDX11_CreateDeviceObjects();
		ImGui_ImplDX11_Init(LoaderUI::GetUI()->pDevice, LoaderUI::GetUI()->pContext);

		LoaderUI::GetUI()->initRendering = false;
	}

	// must call before drawing
	LoaderUI::GetUI()->pContext->OMSetRenderTargets(1, &LoaderUI::GetUI()->pRenderTargetView, NULL);

	// ImGui Rendering ---------------------------------------------

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = Global::GetGlobals()->bIsMenuOpen;
	if (Global::GetGlobals()->bIsMenuOpen)
	{
		/*
		* STYLE
		* https://github.com/ocornut/imgui/issues/707#issuecomment-463758243
		*/
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;
		colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
		colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
		colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->TabBorderSize = 1.0f;
		style->TabRounding = 0.0f;
		style->WindowRounding = 4.0f;
		DrawImGui();
		Global::GetGlobals()->eventSystem.dispatchEvent("DrawImGui");
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

HRESULT(*D3D11Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	// LoaderUI initializes D3D objects, mods can then use those objects for drawing, hardware access, etc.
	LoaderUI* UI = LoaderUI::GetUI();
	UI->LoaderD3D11Present(pSwapChain, SyncInterval, Flags);
	Global::GetGlobals()->eventSystem.dispatchEvent("DX11Present", UI->pDevice, UI->pContext, UI->pRenderTargetView);
	return D3D11Present(pSwapChain, SyncInterval, Flags);
}

DWORD __stdcall InitDX11Hook(LPVOID)
{
	Log::Info("Setting up D3D11Present hook");

	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle(L"dxgi.dll");
		Sleep(100);
	} while (!hDXGIDLL);
	Sleep(100);

	IDXGISwapChain* pSwapChain;

	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);

	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	UINT createFlags = 0;
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	IDXGISwapChain* d3dSwapChain = 0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&LoaderUI::GetUI()->pDevice,
		&obtainedLevel,
		&LoaderUI::GetUI()->pContext)))
	{
		Log::Error("Failed to create D3D device and swapchain");
		return NULL;
	}

	LoaderUI::GetUI()->pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	LoaderUI::GetUI()->pSwapChainVtable = (DWORD_PTR*)LoaderUI::GetUI()->pSwapChainVtable[0];
	LoaderUI::GetUI()->phookD3D11Present = (LoaderUI::D3D11PresentHook)LoaderUI::GetUI()->pSwapChainVtable[8];
	MinHook::Add((DWORD64)LoaderUI::GetUI()->pSwapChainVtable[13], &hookResizeBuffers, &LoaderUI::GetUI()->ResizeBuffers, "DX11-ResizeBuffers");
	MinHook::Add((DWORD64)LoaderUI::GetUI()->phookD3D11Present, &hookD3D11Present, &D3D11Present, "DX11-Present");

	DWORD dPresentwOld;
	DWORD dResizeOld;
	VirtualProtect(LoaderUI::GetUI()->phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dPresentwOld);
	VirtualProtect((LPVOID)LoaderUI::GetUI()->pSwapChainVtable[13], 2, PAGE_EXECUTE_READWRITE, &dResizeOld);

	while (true)
	{
		Sleep(10);
	}

	LoaderUI::GetUI()->pDevice->Release();
	LoaderUI::GetUI()->pContext->Release();
	pSwapChain->Release();
	return NULL;
}

void LoaderUI::HookDX()
{
	if (!LoaderUI::GetUI()->IsDXHooked)
	{
		CreateThread(NULL, 0, InitDX11Hook, NULL, 0, NULL);
		LoaderUI::GetUI()->IsDXHooked = true;
	}
}

DWORD __stdcall LogicThread(LPVOID)
{
	UILogicTick();
	return NULL;
}


void LoaderUI::CreateUILogicThread()
{
	Log::Info("CreateUILogicThread Called");
	CreateThread(0, 0, LogicThread, 0, 0, 0);
}