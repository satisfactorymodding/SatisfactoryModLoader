#pragma once
#include "UE4.hpp"
#include <map>
#include <iostream>
#include <string>
#include "../UMLDefs.h"
#include "../Mod/Mod.h"
#include "../EventSystem.h"
struct ModInfo
{
	std::wstring ModName;
	std::string ModAuthor = "Unknown Author";
	std::string ModDescription = "No Description";
	std::string ModVersion = "Unknown Version";
	UE4::AActor* CurrentModActor = nullptr;
	UE4::UObject* PersistentObject = nullptr;
	bool IsEnabled = 0;
	bool ContainsButton = 0;
	bool WasInitialized = 0;
	std::vector<std::string> ModButtons;
};

class LOADER_API Global {
public:
	struct BPFunctionWrapper
	{
		std::string FunctionName;
		void* FuncPtr;
	};
	std::vector<ModInfo> ModInfoList;
	std::string GameName;
	bool bIsMenuOpen;
	std::vector<class Mod*> CoreMods;
	std::vector<BPFunctionWrapper> BPFunctionWrappers;
	EventDispatcher eventSystem;

	static Global* GetGlobals();

	void AddBPFunctionWrapper(std::string FunctionName, void* FuncPtr)
	{
		BPFunctionWrapper FunctionWrap;
		FunctionWrap.FunctionName = FunctionName;
		FunctionWrap.FuncPtr = FuncPtr;
		BPFunctionWrappers.push_back(FunctionWrap);
	}

	void AddToCoreMods(Mod* mod)
	{
		CoreMods.push_back(mod);
	}

	std::vector<BPFunctionWrapper> GetBPFunctionWrappers()
	{
		return BPFunctionWrappers;
	}

private:
	static Global* glb;
};
