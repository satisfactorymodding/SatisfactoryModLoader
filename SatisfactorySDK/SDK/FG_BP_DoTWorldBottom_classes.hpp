#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DoTWorldBottom_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_DoTWorldBottom.BP_DoTWorldBottom_C
// 0x0000 (0x0048 - 0x0048)
class UBP_DoTWorldBottom_C : public UFGDamageOverTime
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_DoTWorldBottom.BP_DoTWorldBottom_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
