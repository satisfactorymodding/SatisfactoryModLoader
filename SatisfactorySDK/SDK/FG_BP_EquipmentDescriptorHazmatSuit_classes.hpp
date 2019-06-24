#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_EquipmentDescriptorHazmatSuit_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_EquipmentDescriptorHazmatSuit.BP_EquipmentDescriptorHazmatSuit_C
// 0x0000 (0x0130 - 0x0130)
class UBP_EquipmentDescriptorHazmatSuit_C : public UFGEquipmentDescriptor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_EquipmentDescriptorHazmatSuit.BP_EquipmentDescriptorHazmatSuit_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
