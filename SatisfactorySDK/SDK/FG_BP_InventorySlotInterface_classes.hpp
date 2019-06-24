#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_InventorySlotInterface_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_InventorySlotInterface.BP_InventorySlotInterface_C
// 0x0000 (0x0028 - 0x0028)
class UBP_InventorySlotInterface_C : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_InventorySlotInterface.BP_InventorySlotInterface_C");
		return ptr;
	}


	void SubscribeToParentWindow(class UWidget_Window_C* ParentWindow);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
