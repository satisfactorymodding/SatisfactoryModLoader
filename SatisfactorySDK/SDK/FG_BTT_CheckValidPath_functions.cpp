// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_CheckValidPath_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_CheckValidPath.BTT_CheckValidPath_C.ReceiveExecute
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_CheckValidPath_C::ReceiveExecute(class AActor** OwnerActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_CheckValidPath.BTT_CheckValidPath_C.ReceiveExecute");

	UBTT_CheckValidPath_C_ReceiveExecute_Params params;
	params.OwnerActor = OwnerActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_CheckValidPath.BTT_CheckValidPath_C.ExecuteUbergraph_BTT_CheckValidPath
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_CheckValidPath_C::ExecuteUbergraph_BTT_CheckValidPath(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_CheckValidPath.BTT_CheckValidPath_C.ExecuteUbergraph_BTT_CheckValidPath");

	UBTT_CheckValidPath_C_ExecuteUbergraph_BTT_CheckValidPath_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
