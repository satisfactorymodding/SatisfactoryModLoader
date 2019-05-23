#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FoilagePickup_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_FoilagePickup.BP_FoilagePickup_C
// 0x0010 (0x0358 - 0x0348)
class ABP_FoilagePickup_C : public AFGFoliagePickup
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0348(0x0008) (Transient, DuplicateTransient)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0350(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_FoilagePickup.BP_FoilagePickup_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayPickupEffect(class UFGFoliageResourceUserData** foliageUserData, struct FVector* atLocation);
	void ExecuteUbergraph_BP_FoilagePickup(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
