#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MusicManager_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_MusicManager.BP_MusicManager_C.OnPlayerNearBaseChanged
struct UBP_MusicManager_C_OnPlayerNearBaseChanged_Params
{
	bool*                                              isNear;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MusicManager.BP_MusicManager_C.OnPlayerEnteredArea
struct UBP_MusicManager_C_OnPlayerEnteredArea_Params
{
	class UClass**                                     mapArea;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MusicManager.BP_MusicManager_C.NotifyPostLoadMap
struct UBP_MusicManager_C_NotifyPostLoadMap_Params
{
	class UWorld**                                     loadedWorld;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AWorldSettings**                             WorldSettings;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MusicManager.BP_MusicManager_C.Play
struct UBP_MusicManager_C_Play_Params
{
};

// Function BP_MusicManager.BP_MusicManager_C.Pause
struct UBP_MusicManager_C_Pause_Params
{
};

// Function BP_MusicManager.BP_MusicManager_C.Stop
struct UBP_MusicManager_C_Stop_Params
{
};

// Function BP_MusicManager.BP_MusicManager_C.ExecuteUbergraph_BP_MusicManager
struct UBP_MusicManager_C_ExecuteUbergraph_BP_MusicManager_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
