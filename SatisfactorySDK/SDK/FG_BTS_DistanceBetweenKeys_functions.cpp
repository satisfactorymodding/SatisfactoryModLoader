// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_DistanceBetweenKeys_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTS_DistanceBetweenKeys.BTS_DistanceBetweenKeys_C.GetKeyLocation
// ()
// Parameters:
// struct FBlackboardKeySelector  Key                            (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FVector                 Location                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBTS_DistanceBetweenKeys_C::GetKeyLocation(const struct FBlackboardKeySelector& Key, struct FVector* Location)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_DistanceBetweenKeys.BTS_DistanceBetweenKeys_C.GetKeyLocation");

	UBTS_DistanceBetweenKeys_C_GetKeyLocation_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Location != nullptr)
		*Location = params.Location;
}


// Function BTS_DistanceBetweenKeys.BTS_DistanceBetweenKeys_C.ReceiveTickAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_DistanceBetweenKeys_C::ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_DistanceBetweenKeys.BTS_DistanceBetweenKeys_C.ReceiveTickAI");

	UBTS_DistanceBetweenKeys_C_ReceiveTickAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTS_DistanceBetweenKeys.BTS_DistanceBetweenKeys_C.ExecuteUbergraph_BTS_DistanceBetweenKeys
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_DistanceBetweenKeys_C::ExecuteUbergraph_BTS_DistanceBetweenKeys(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_DistanceBetweenKeys.BTS_DistanceBetweenKeys_C.ExecuteUbergraph_BTS_DistanceBetweenKeys");

	UBTS_DistanceBetweenKeys_C_ExecuteUbergraph_BTS_DistanceBetweenKeys_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
