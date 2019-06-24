// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CaveFloor_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_CaveFloor.BP_CaveFloor_C.GetEntrenceAndExitIndex
// ()
// Parameters:
// int                            entrence                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// int                            Exit                           (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_CaveFloor_C::GetEntrenceAndExitIndex(int* entrence, int* Exit)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CaveFloor.BP_CaveFloor_C.GetEntrenceAndExitIndex");

	ABP_CaveFloor_C_GetEntrenceAndExitIndex_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (entrence != nullptr)
		*entrence = params.entrence;
	if (Exit != nullptr)
		*Exit = params.Exit;
}


// Function BP_CaveFloor.BP_CaveFloor_C.GetStaticMeshForIndex
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UStaticMesh*             NewParam                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_CaveFloor_C::GetStaticMeshForIndex(int Index, class UStaticMesh** NewParam)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CaveFloor.BP_CaveFloor_C.GetStaticMeshForIndex");

	ABP_CaveFloor_C_GetStaticMeshForIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NewParam != nullptr)
		*NewParam = params.NewParam;
}


// Function BP_CaveFloor.BP_CaveFloor_C.BuildCaveElement
// ()

void ABP_CaveFloor_C::BuildCaveElement()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CaveFloor.BP_CaveFloor_C.BuildCaveElement");

	ABP_CaveFloor_C_BuildCaveElement_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CaveFloor.BP_CaveFloor_C.UserConstructionScript
// ()

void ABP_CaveFloor_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CaveFloor.BP_CaveFloor_C.UserConstructionScript");

	ABP_CaveFloor_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
