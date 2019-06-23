// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_StorageIntegrated_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_StorageIntegrated.Build_StorageIntegrated_C.CanDismantle
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_StorageIntegrated_C::CanDismantle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_StorageIntegrated.Build_StorageIntegrated_C.CanDismantle");

	ABuild_StorageIntegrated_C_CanDismantle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_StorageIntegrated.Build_StorageIntegrated_C.UserConstructionScript
// ()

void ABuild_StorageIntegrated_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_StorageIntegrated.Build_StorageIntegrated_C.UserConstructionScript");

	ABuild_StorageIntegrated_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
