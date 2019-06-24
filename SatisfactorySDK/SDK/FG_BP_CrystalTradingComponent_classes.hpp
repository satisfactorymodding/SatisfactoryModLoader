#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CrystalTradingComponent_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_CrystalTradingComponent.BP_CrystalTradingComponent_C
// 0x0000 (0x0288 - 0x0288)
class UBP_CrystalTradingComponent_C : public UBP_ManualManufacturingComponent_C
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_CrystalTradingComponent.BP_CrystalTradingComponent_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
