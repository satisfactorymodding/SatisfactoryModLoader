#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpaceRabbitSettings_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_SpaceRabbitSettings.BP_SpaceRabbitSettings_C
// 0x0010 (0x0038 - 0x0028)
class UBP_SpaceRabbitSettings_C : public UFGLootSettings
{
public:
	TArray<struct FInventoryStack>                     mLootTable;                                               // 0x0028(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_SpaceRabbitSettings.BP_SpaceRabbitSettings_C");
		return ptr;
	}


	void GetRandomLoot(int* Loot_Index);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
