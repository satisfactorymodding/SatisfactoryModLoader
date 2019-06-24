#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DoTWorldPerimeter_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_DoTWorldPerimeter.BP_DoTWorldPerimeter_C
// 0x0000 (0x0048 - 0x0048)
class UBP_DoTWorldPerimeter_C : public UFGDamageOverTime
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_DoTWorldPerimeter.BP_DoTWorldPerimeter_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
