// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_CheatResourceSpawner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.InternalGetOutput
// ()
// Parameters:
// class UClass*                  Type                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  Output                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABuild_CheatResourceSpawner_C::InternalGetOutput(class UClass* Type, class UClass** Output)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.InternalGetOutput");

	ABuild_CheatResourceSpawner_C_InternalGetOutput_Params params;
	params.Type = Type;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Output != nullptr)
		*Output = params.Output;
}


// Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.Factory_GrabOutput
// ()
// Parameters:
// class UFGFactoryConnectionComponent** Connection                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FInventoryItem          out_item                       (Parm, OutParm)
// float                          out_OffsetBeyond               (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// class UClass**                 Type                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_CheatResourceSpawner_C::Factory_GrabOutput(class UFGFactoryConnectionComponent** Connection, class UClass** Type, struct FInventoryItem* out_item, float* out_OffsetBeyond)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.Factory_GrabOutput");

	ABuild_CheatResourceSpawner_C_Factory_GrabOutput_Params params;
	params.Connection = Connection;
	params.Type = Type;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_item != nullptr)
		*out_item = params.out_item;
	if (out_OffsetBeyond != nullptr)
		*out_OffsetBeyond = params.out_OffsetBeyond;

	return params.ReturnValue;
}


// Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.Factory_PeekOutput
// ()
// Parameters:
// class UFGFactoryConnectionComponent** Connection                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// TArray<struct FInventoryItem>  out_items                      (Parm, OutParm, ZeroConstructor)
// class UClass**                 Type                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_CheatResourceSpawner_C::Factory_PeekOutput(class UFGFactoryConnectionComponent** Connection, class UClass** Type, TArray<struct FInventoryItem>* out_items)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.Factory_PeekOutput");

	ABuild_CheatResourceSpawner_C_Factory_PeekOutput_Params params;
	params.Connection = Connection;
	params.Type = Type;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_items != nullptr)
		*out_items = params.out_items;

	return params.ReturnValue;
}


// Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.UserConstructionScript
// ()

void ABuild_CheatResourceSpawner_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.UserConstructionScript");

	ABuild_CheatResourceSpawner_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
