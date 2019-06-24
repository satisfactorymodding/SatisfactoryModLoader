#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_NavQuery_WalkingAI_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass NavQuery_WalkingAI.NavQuery_WalkingAI_C
// 0x0000 (0x0048 - 0x0048)
class UNavQuery_WalkingAI_C : public UNavigationQueryFilter
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass NavQuery_WalkingAI.NavQuery_WalkingAI_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
