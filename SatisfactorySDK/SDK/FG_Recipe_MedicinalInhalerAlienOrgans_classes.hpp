#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Recipe_MedicinalInhalerAlienOrgans_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Recipe_MedicinalInhalerAlienOrgans.Recipe_MedicinalInhalerAlienOrgans_C
// 0x0000 (0x0080 - 0x0080)
class URecipe_MedicinalInhalerAlienOrgans_C : public UFGRecipe
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Recipe_MedicinalInhalerAlienOrgans.Recipe_MedicinalInhalerAlienOrgans_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
