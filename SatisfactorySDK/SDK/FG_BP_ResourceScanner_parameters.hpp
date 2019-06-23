#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceScanner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_ResourceScanner.BP_ResourceScanner_C.IsScannerWheelVisible
struct ABP_ResourceScanner_C_IsScannerWheelVisible_Params
{
	bool                                               IsVisible;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.UserConstructionScript
struct ABP_ResourceScanner_C_UserConstructionScript_Params
{
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.Timeline_0__FinishedFunc
struct ABP_ResourceScanner_C_Timeline_0__FinishedFunc_Params
{
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.Timeline_0__UpdateFunc
struct ABP_ResourceScanner_C_Timeline_0__UpdateFunc_Params
{
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.ShowResourceDescriptorSelectUI
struct ABP_ResourceScanner_C_ShowResourceDescriptorSelectUI_Params
{
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.CloseResourceDescriptorSelectUI
struct ABP_ResourceScanner_C_CloseResourceDescriptorSelectUI_Params
{
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.PlayClusterEffects
struct ABP_ResourceScanner_C_PlayClusterEffects_Params
{
	TArray<struct FNodeClusterData>*                   clusters;                                                 // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.Event Play Pulse Effect
struct ABP_ResourceScanner_C_Event_Play_Pulse_Effect_Params
{
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.CustomEvent_1
struct ABP_ResourceScanner_C_CustomEvent_1_Params
{
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.ExecuteUbergraph_BP_ResourceScanner
struct ABP_ResourceScanner_C_ExecuteUbergraph_BP_ResourceScanner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_ResourceScanner.BP_ResourceScanner_C.OnClustersFound__DelegateSignature
struct ABP_ResourceScanner_C_OnClustersFound__DelegateSignature_Params
{
	TArray<struct FNodeClusterData>                    ClustersFound;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
