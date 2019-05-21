// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Build_ManufacturerMk2_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ManufacturerMk2.Build_ManufacturerMk2_C.UserConstructionScript
// ()

void ABuild_ManufacturerMk2_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ManufacturerMk2.Build_ManufacturerMk2_C.UserConstructionScript");

	ABuild_ManufacturerMk2_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
