// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ParachuteMesh_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function ParachuteMesh.ParachuteMesh_C.UserConstructionScript
// ()

void AParachuteMesh_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function ParachuteMesh.ParachuteMesh_C.UserConstructionScript");

	AParachuteMesh_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
