#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ResearchRecipe_Mycelia_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass ResearchRecipe_Mycelia.ResearchRecipe_Mycelia_C
// 0x0000 (0x00D8 - 0x00D8)
class UResearchRecipe_Mycelia_C : public UFGResearchRecipe
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass ResearchRecipe_Mycelia.ResearchRecipe_Mycelia_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
