// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ManufacturerMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ManufacturerMk1.Build_ManufacturerMk1_C.SetText
// ()
// Parameters:
// class FString                  intText                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)

void ABuild_ManufacturerMk1_C::SetText(const class FString& intText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ManufacturerMk1.Build_ManufacturerMk1_C.SetText");

	ABuild_ManufacturerMk1_C_SetText_Params params;
	params.intText = intText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ManufacturerMk1.Build_ManufacturerMk1_C.UserConstructionScript
// ()

void ABuild_ManufacturerMk1_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ManufacturerMk1.Build_ManufacturerMk1_C.UserConstructionScript");

	ABuild_ManufacturerMk1_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
