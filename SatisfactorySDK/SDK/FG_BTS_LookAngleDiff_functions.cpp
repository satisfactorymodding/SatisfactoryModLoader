// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_LookAngleDiff_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTS_LookAngleDiff.BTS_LookAngleDiff_C.ReceiveTick
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_LookAngleDiff_C::ReceiveTick(class AActor** OwnerActor, float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_LookAngleDiff.BTS_LookAngleDiff_C.ReceiveTick");

	UBTS_LookAngleDiff_C_ReceiveTick_Params params;
	params.OwnerActor = OwnerActor;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTS_LookAngleDiff.BTS_LookAngleDiff_C.ExecuteUbergraph_BTS_LookAngleDiff
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_LookAngleDiff_C::ExecuteUbergraph_BTS_LookAngleDiff(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_LookAngleDiff.BTS_LookAngleDiff_C.ExecuteUbergraph_BTS_LookAngleDiff");

	UBTS_LookAngleDiff_C_ExecuteUbergraph_BTS_LookAngleDiff_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
