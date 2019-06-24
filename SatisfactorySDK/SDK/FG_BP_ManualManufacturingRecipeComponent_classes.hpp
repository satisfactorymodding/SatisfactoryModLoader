#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ManualManufacturingRecipeComponent_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_ManualManufacturingRecipeComponent.BP_ManualManufacturingRecipeComponent_C
// 0x0000 (0x0288 - 0x0288)
class UBP_ManualManufacturingRecipeComponent_C : public UBP_ManualManufacturingComponent_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_ManualManufacturingRecipeComponent.BP_ManualManufacturingRecipeComponent_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
