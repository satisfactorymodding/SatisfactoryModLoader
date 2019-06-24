#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_MedKit_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_MedKit.Equip_MedKit_C
// 0x001C (0x03DC - 0x03C0)
class AEquip_MedKit_C : public AFGConsumableEquipment
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03C0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Medkit_skl;                                               // 0x03C8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x03D0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                mRandomAnim;                                              // 0x03D8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_MedKit.Equip_MedKit_C");
		return ptr;
	}


	void UserConstructionScript();
	void WasEquipped();
	void PlayConsumeEffects(class UFGConsumableDescriptor** consumable);
	void WasUnEquipped();
	void ExecuteUbergraph_Equip_MedKit(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
