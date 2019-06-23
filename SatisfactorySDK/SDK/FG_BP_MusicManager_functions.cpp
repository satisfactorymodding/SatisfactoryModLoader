// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MusicManager_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MusicManager.BP_MusicManager_C.OnPlayerNearBaseChanged
// ()
// Parameters:
// bool*                          isNear                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MusicManager_C::OnPlayerNearBaseChanged(bool* isNear)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MusicManager.BP_MusicManager_C.OnPlayerNearBaseChanged");

	UBP_MusicManager_C_OnPlayerNearBaseChanged_Params params;
	params.isNear = isNear;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MusicManager.BP_MusicManager_C.OnPlayerEnteredArea
// ()
// Parameters:
// class UClass**                 mapArea                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MusicManager_C::OnPlayerEnteredArea(class UClass** mapArea)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MusicManager.BP_MusicManager_C.OnPlayerEnteredArea");

	UBP_MusicManager_C_OnPlayerEnteredArea_Params params;
	params.mapArea = mapArea;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MusicManager.BP_MusicManager_C.NotifyPostLoadMap
// ()
// Parameters:
// class UWorld**                 loadedWorld                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AWorldSettings**         WorldSettings                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MusicManager_C::NotifyPostLoadMap(class UWorld** loadedWorld, class AWorldSettings** WorldSettings)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MusicManager.BP_MusicManager_C.NotifyPostLoadMap");

	UBP_MusicManager_C_NotifyPostLoadMap_Params params;
	params.loadedWorld = loadedWorld;
	params.WorldSettings = WorldSettings;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MusicManager.BP_MusicManager_C.Play
// ()

void UBP_MusicManager_C::Play()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MusicManager.BP_MusicManager_C.Play");

	UBP_MusicManager_C_Play_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MusicManager.BP_MusicManager_C.Pause
// ()

void UBP_MusicManager_C::Pause()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MusicManager.BP_MusicManager_C.Pause");

	UBP_MusicManager_C_Pause_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MusicManager.BP_MusicManager_C.Stop
// ()

void UBP_MusicManager_C::Stop()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MusicManager.BP_MusicManager_C.Stop");

	UBP_MusicManager_C_Stop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MusicManager.BP_MusicManager_C.ExecuteUbergraph_BP_MusicManager
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MusicManager_C::ExecuteUbergraph_BP_MusicManager(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MusicManager.BP_MusicManager_C.ExecuteUbergraph_BP_MusicManager");

	UBP_MusicManager_C_ExecuteUbergraph_BP_MusicManager_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
