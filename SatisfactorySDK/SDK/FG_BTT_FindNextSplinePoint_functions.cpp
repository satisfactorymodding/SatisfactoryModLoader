// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FindNextSplinePoint_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_FindNextSplinePoint.BTT_FindNextSplinePoint_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_FindNextSplinePoint_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FindNextSplinePoint.BTT_FindNextSplinePoint_C.ReceiveExecuteAI");

	UBTT_FindNextSplinePoint_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_FindNextSplinePoint.BTT_FindNextSplinePoint_C.ExecuteUbergraph_BTT_FindNextSplinePoint
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_FindNextSplinePoint_C::ExecuteUbergraph_BTT_FindNextSplinePoint(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FindNextSplinePoint.BTT_FindNextSplinePoint_C.ExecuteUbergraph_BTT_FindNextSplinePoint");

	UBTT_FindNextSplinePoint_C_ExecuteUbergraph_BTT_FindNextSplinePoint_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
