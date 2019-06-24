#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Desc_AluminumPlateReinforced_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Desc_AluminumPlateReinforced.Desc_AluminumPlateReinforced_C
// 0x0000 (0x0128 - 0x0128)
class UDesc_AluminumPlateReinforced_C : public UFGItemDescriptor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Desc_AluminumPlateReinforced.Desc_AluminumPlateReinforced_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
