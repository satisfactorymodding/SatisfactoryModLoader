#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_EquipmentDescriptorRifle_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_EquipmentDescriptorRifle.BP_EquipmentDescriptorRifle_C
// 0x0000 (0x0130 - 0x0130)
class UBP_EquipmentDescriptorRifle_C : public UFGEquipmentDescriptor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_EquipmentDescriptorRifle.BP_EquipmentDescriptorRifle_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
