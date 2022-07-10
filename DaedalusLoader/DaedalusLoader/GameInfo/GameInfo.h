#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "Memory/mem.h"

#define GAME_EXECUTABLE_NAME "Icarus-Win64-Shipping.exe"

struct Offsets {
	struct {
		uint16_t Index = 0x0;
		uint16_t Class = 0x0;
		uint16_t Name = 0x0;
		uint16_t Outer = 0x0;
	} UObject;
	struct {
		uint16_t Next = 0x0;
	} UField;
	struct {
		uint16_t SuperStruct = 0x0;
		uint16_t Children = 0x0;
		uint16_t PropertiesSize = 0x0;
		uint16_t OverallUStructSize = 0x0;
	} UStruct;
	struct {
		uint16_t FunctionFlags = 0x0;
		uint16_t Func = 0x0;
	} UFunction;
	struct {
		uint16_t Next = 0x0;
		uint16_t Name = 0x0;
	} FField;
	struct {
		uint16_t ArrayDim = 0x0;
		uint16_t Offset = 0x0;
	} Property;
};

class LOADER_API GameProfile
{
public:
	std::string ProfileName;
	std::string LoaderPath;
	int UsesFNamePool = 0;
	std::string BeginPlayOverwrite = "Class Engine.PlayerController";

	bool IsGInfoPatterns = false;
	DWORD64 GName = 0x0;
	DWORD64 GObject = 0x0;
	DWORD64 GWorld = 0x0;
	bool IsUsingDeferedSpawn = false;
	bool IsUsingFChunkedFixedUObjectArray = false;
	bool IsUsing4_22 = false;

	bool IsFunctionPatterns = false;
	DWORD64 ProcessEvent = 0x0;
	DWORD64 CreateDefaultObject = 0x0;
	DWORD64 GameStateInit = 0x0;
	DWORD64 BeginPlay = 0x0;
	DWORD64 StaticLoadObject = 0x0;
	DWORD64 SpawnActorFTrans = 0x0;

	DWORD64 ProcessInternals = 0x0;
	DWORD64 StaticConstructObject_Internal = 0x0;
	bool IsUsingUpdatedStaticConstruct = false;

	DWORD64 CallFunctionByNameWithArguments = 0x0;

	bool IsUObjectMissing = true;
	bool IsUFieldMissing = true;
	bool IsUStructMissing = true;
	bool IsUFunctionMissing = true;

	bool IsPropertyMissing = false;

	bool bIsFProperty = false;

	bool bIsDefaultObjectArrayed = false;

	bool bDelayGUISpawn = false;

	Offsets defs;

	static GameProfile SelectedGameProfile;
	static void CreateGameProfile();
};