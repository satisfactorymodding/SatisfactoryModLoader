// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_EquipmentDescriptorBeacon_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_EquipmentDescriptorBeacon.BP_EquipmentDescriptorBeacon_C.ConsumedBy
// ()
// Parameters:
// class AFGCharacterPlayer**     Player                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_EquipmentDescriptorBeacon_C::ConsumedBy(class AFGCharacterPlayer** Player)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_EquipmentDescriptorBeacon.BP_EquipmentDescriptorBeacon_C.ConsumedBy");

	UBP_EquipmentDescriptorBeacon_C_ConsumedBy_Params params;
	params.Player = Player;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
