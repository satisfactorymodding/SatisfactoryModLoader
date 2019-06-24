// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Tutorial_ProductionBuildings_Mail_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Tutorial_ProductionBuildings_Mail.Tutorial_ProductionBuildings_Mail_C.Construct
// ()

void UTutorial_ProductionBuildings_Mail_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Tutorial_ProductionBuildings_Mail.Tutorial_ProductionBuildings_Mail_C.Construct");

	UTutorial_ProductionBuildings_Mail_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Tutorial_ProductionBuildings_Mail.Tutorial_ProductionBuildings_Mail_C.ExecuteUbergraph_Tutorial_ProductionBuildings_Mail
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UTutorial_ProductionBuildings_Mail_C::ExecuteUbergraph_Tutorial_ProductionBuildings_Mail(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Tutorial_ProductionBuildings_Mail.Tutorial_ProductionBuildings_Mail_C.ExecuteUbergraph_Tutorial_ProductionBuildings_Mail");

	UTutorial_ProductionBuildings_Mail_C_ExecuteUbergraph_Tutorial_ProductionBuildings_Mail_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
