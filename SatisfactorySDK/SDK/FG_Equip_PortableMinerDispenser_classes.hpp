#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_PortableMinerDispenser_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_PortableMinerDispenser.Equip_PortableMinerDispenser_C
// 0x0018 (0x0400 - 0x03E8)
class AEquip_PortableMinerDispenser_C : public AFGPortableMinerDispenser
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03E8(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      _1P_PortableMiner;                                        // 0x03F0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x03F8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_PortableMinerDispenser.Equip_PortableMinerDispenser_C");
		return ptr;
	}


	void UserConstructionScript();
	void SpawnPortableMiner(class AFGResourceNode** resourceNode);
	void PlaySpawnEffects(class ABP_PortableMiner_C* PortableMiner);
	void WasEquipped();
	void WasUnEquipped();
	void ExecuteUbergraph_Equip_PortableMinerDispenser(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
