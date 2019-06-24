#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_NobeliskDetonator_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_NobeliskDetonator.Equip_NobeliskDetonator_C
// 0x0018 (0x0498 - 0x0480)
class AEquip_NobeliskDetonator_C : public AFGNobeliskDetonator
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0480(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      NobeliskDetonator_Skl_01;                                 // 0x0488(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0490(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_NobeliskDetonator.Equip_NobeliskDetonator_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayReloadEffects();
	void PlayFireEffect();
	void WasUnEquipped();
	void WasEquipped();
	void OnSecondaryFirePressed();
	void PlayFireReleasedEffects();
	void ExecuteUbergraph_Equip_NobeliskDetonator(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
