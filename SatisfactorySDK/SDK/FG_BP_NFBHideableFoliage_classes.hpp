#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_NFBHideableFoliage_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_NFBHideableFoliage.BP_NFBHideableFoliage_C
// 0x0000 (0x0028 - 0x0028)
class UBP_NFBHideableFoliage_C : public UFGFoliageIdentifier_Pickupable
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_NFBHideableFoliage.BP_NFBHideableFoliage_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
