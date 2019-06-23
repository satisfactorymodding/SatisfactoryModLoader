// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpaceRabbitSettings_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SpaceRabbitSettings.BP_SpaceRabbitSettings_C.GetRandomLoot
// ()
// Parameters:
// int                            Loot_Index                     (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)

void UBP_SpaceRabbitSettings_C::GetRandomLoot(int* Loot_Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SpaceRabbitSettings.BP_SpaceRabbitSettings_C.GetRandomLoot");

	UBP_SpaceRabbitSettings_C_GetRandomLoot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Loot_Index != nullptr)
		*Loot_Index = params.Loot_Index;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
