#include "Mod.h"
#include "Utilities/MinHook.h"
#include "Utilities/Version.h"

Mod* Mod::ModRef;

namespace CallBackHandler
{
	void CallBackBeginPlay(UE4::AActor* Actor)
	{
		Mod::ModRef->BeginPlay(Actor);
	}

	void CallBackInitGameState()
	{
		Mod::ModRef->InitGameState();
	}

	void CallBackDrawImGui()
	{
		Mod::ModRef->DrawImGui();
	}

	void CallBackPostBeginPlay(std::wstring ModActorName, UE4::AActor* Actor)
	{
		Mod::ModRef->PostBeginPlay(ModActorName, Actor);
	}

	void CallBackDX11Present(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView)
	{
		Mod::ModRef->DX11Present(pDevice, pContext, pRenderTargetView);
	}
}

void Mod::InitGameState()
{
}

void Mod::OnModMenuButtonPressed()
{
}

void Mod::BeginPlay(UE4::AActor* Actor)
{
}

void Mod::PostBeginPlay(std::wstring ModActorName, UE4::AActor* Actor)
{
}

void Mod::DX11Present(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView)
{
}

void Mod::DrawImGui()
{
}

void Mod::SetupHooks()
{
	Global::GetGlobals()->eventSystem.registerEvent(new Event<UE4::AActor*>("BeginPlay", &CallBackHandler::CallBackBeginPlay));
	Global::GetGlobals()->eventSystem.registerEvent(new Event<>("InitGameState", &CallBackHandler::CallBackInitGameState));
	Global::GetGlobals()->eventSystem.registerEvent(new Event<std::wstring, UE4::AActor*>("PostBeginPlay", &CallBackHandler::CallBackPostBeginPlay));
	Global::GetGlobals()->eventSystem.registerEvent(new Event<>("DrawImGui", &CallBackHandler::CallBackDrawImGui));
	Global::GetGlobals()->eventSystem.registerEvent(new Event<ID3D11Device*, ID3D11DeviceContext*, ID3D11RenderTargetView*>("DX11Present", &CallBackHandler::CallBackDX11Present));
}

void Mod::CompleteModCreation()
{
	IsFinishedCreating = true;
	Global::GetGlobals()->AddToCoreMods(ModRef);
	Log::Info("Core Mod Created: %s", ModName.c_str());
	if (ModLoaderVersion != MODLOADER_VERSION)
	{
		Log::Warn("Mod: %s was created with a different version of the Unreal Mod Loader. This mod may be unstable.", ModName.c_str());
	}
}

void Mod::InitializeMod()
{

}