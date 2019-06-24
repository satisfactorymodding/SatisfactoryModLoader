#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_EquipChild_NobeliskDetonator_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass EquipChild_NobeliskDetonator.EquipChild_NobeliskDetonator_C
// 0x0018 (0x0358 - 0x0340)
class AEquipChild_NobeliskDetonator_C : public AFGWeaponChild
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0340(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Explosive_skel;                                           // 0x0348(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0350(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass EquipChild_NobeliskDetonator.EquipChild_NobeliskDetonator_C");
		return ptr;
	}


	void UserConstructionScript();
	void NotifyReloadComplete();
	void NotifyEndPrimaryFire();
	void NotifyReloading();
	void NotifyBeginPrimaryFire();
	void OnEquip(class AFGCharacterPlayer** Character);
	void NotifyPrimaryFireExecuted();
	void ExecuteUbergraph_EquipChild_NobeliskDetonator(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
