#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Planet_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Planet.BP_Planet_C.ShouldSave
struct ABP_Planet_C_ShouldSave_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Planet.BP_Planet_C.GatherDependencies
struct ABP_Planet_C_GatherDependencies_Params
{
	TArray<class UObject*>                             out_dependentObjects;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function BP_Planet.BP_Planet_C.NeedTransform
struct ABP_Planet_C_NeedTransform_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Planet.BP_Planet_C.UpdateMaterialParameters
struct ABP_Planet_C_UpdateMaterialParameters_Params
{
};

// Function BP_Planet.BP_Planet_C.UserConstructionScript
struct ABP_Planet_C_UserConstructionScript_Params
{
};

// Function BP_Planet.BP_Planet_C.PostSaveGame
struct ABP_Planet_C_PostSaveGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Planet.BP_Planet_C.PreLoadGame
struct ABP_Planet_C_PreLoadGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Planet.BP_Planet_C.ReceiveBeginPlay
struct ABP_Planet_C_ReceiveBeginPlay_Params
{
};

// Function BP_Planet.BP_Planet_C.ReceiveTick
struct ABP_Planet_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Planet.BP_Planet_C.UpdatePreview
struct ABP_Planet_C_UpdatePreview_Params
{
};

// Function BP_Planet.BP_Planet_C.PreSaveGame
struct ABP_Planet_C_PreSaveGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Planet.BP_Planet_C.PostLoadGame
struct ABP_Planet_C_PostLoadGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Planet.BP_Planet_C.ExecuteUbergraph_BP_Planet
struct ABP_Planet_C_ExecuteUbergraph_BP_Planet_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
