// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceScanner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_ResourceScanner.BP_ResourceScanner_C.IsScannerWheelVisible
// ()
// Parameters:
// bool                           IsVisible                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_ResourceScanner_C::IsScannerWheelVisible(bool* IsVisible)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.IsScannerWheelVisible");

	ABP_ResourceScanner_C_IsScannerWheelVisible_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsVisible != nullptr)
		*IsVisible = params.IsVisible;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.UserConstructionScript
// ()

void ABP_ResourceScanner_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.UserConstructionScript");

	ABP_ResourceScanner_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.Timeline_0__FinishedFunc
// ()

void ABP_ResourceScanner_C::Timeline_0__FinishedFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.Timeline_0__FinishedFunc");

	ABP_ResourceScanner_C_Timeline_0__FinishedFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.Timeline_0__UpdateFunc
// ()

void ABP_ResourceScanner_C::Timeline_0__UpdateFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.Timeline_0__UpdateFunc");

	ABP_ResourceScanner_C_Timeline_0__UpdateFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.ShowResourceDescriptorSelectUI
// ()

void ABP_ResourceScanner_C::ShowResourceDescriptorSelectUI()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.ShowResourceDescriptorSelectUI");

	ABP_ResourceScanner_C_ShowResourceDescriptorSelectUI_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.CloseResourceDescriptorSelectUI
// ()

void ABP_ResourceScanner_C::CloseResourceDescriptorSelectUI()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.CloseResourceDescriptorSelectUI");

	ABP_ResourceScanner_C_CloseResourceDescriptorSelectUI_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.PlayClusterEffects
// ()
// Parameters:
// TArray<struct FNodeClusterData>* clusters                       (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)

void ABP_ResourceScanner_C::PlayClusterEffects(TArray<struct FNodeClusterData>* clusters)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.PlayClusterEffects");

	ABP_ResourceScanner_C_PlayClusterEffects_Params params;
	params.clusters = clusters;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.Event Play Pulse Effect
// ()

void ABP_ResourceScanner_C::Event_Play_Pulse_Effect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.Event Play Pulse Effect");

	ABP_ResourceScanner_C_Event_Play_Pulse_Effect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.CustomEvent_1
// ()

void ABP_ResourceScanner_C::CustomEvent_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.CustomEvent_1");

	ABP_ResourceScanner_C_CustomEvent_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.ExecuteUbergraph_BP_ResourceScanner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ResourceScanner_C::ExecuteUbergraph_BP_ResourceScanner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.ExecuteUbergraph_BP_ResourceScanner");

	ABP_ResourceScanner_C_ExecuteUbergraph_BP_ResourceScanner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceScanner.BP_ResourceScanner_C.OnClustersFound__DelegateSignature
// ()
// Parameters:
// TArray<struct FNodeClusterData> ClustersFound                  (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)

void ABP_ResourceScanner_C::OnClustersFound__DelegateSignature(TArray<struct FNodeClusterData>* ClustersFound)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceScanner.BP_ResourceScanner_C.OnClustersFound__DelegateSignature");

	ABP_ResourceScanner_C_OnClustersFound__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ClustersFound != nullptr)
		*ClustersFound = params.ClustersFound;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
