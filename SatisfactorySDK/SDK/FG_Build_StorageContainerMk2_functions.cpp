// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_StorageContainerMk2_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_StorageContainerMk2.Build_StorageContainerMk2_C.UserConstructionScript
// ()

void ABuild_StorageContainerMk2_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_StorageContainerMk2.Build_StorageContainerMk2_C.UserConstructionScript");

	ABuild_StorageContainerMk2_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
