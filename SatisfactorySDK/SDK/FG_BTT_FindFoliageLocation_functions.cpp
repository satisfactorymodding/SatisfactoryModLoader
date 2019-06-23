// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FindFoliageLocation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_FindFoliageLocation.BTT_FindFoliageLocation_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_FindFoliageLocation_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FindFoliageLocation.BTT_FindFoliageLocation_C.ReceiveExecuteAI");

	UBTT_FindFoliageLocation_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_FindFoliageLocation.BTT_FindFoliageLocation_C.ExecuteUbergraph_BTT_FindFoliageLocation
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_FindFoliageLocation_C::ExecuteUbergraph_BTT_FindFoliageLocation(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FindFoliageLocation.BTT_FindFoliageLocation_C.ExecuteUbergraph_BTT_FindFoliageLocation");

	UBTT_FindFoliageLocation_C_ExecuteUbergraph_BTT_FindFoliageLocation_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
