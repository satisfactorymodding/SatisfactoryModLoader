#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_EquipmentDescriptorBeacon_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_EquipmentDescriptorBeacon.BP_EquipmentDescriptorBeacon_C
// 0x0000 (0x0168 - 0x0168)
class UBP_EquipmentDescriptorBeacon_C : public UFGConsumableDescriptor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_EquipmentDescriptorBeacon.BP_EquipmentDescriptorBeacon_C");
		return ptr;
	}


	void ConsumedBy(class AFGCharacterPlayer** Player);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
