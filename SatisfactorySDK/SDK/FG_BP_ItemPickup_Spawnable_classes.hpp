#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ItemPickup_Spawnable_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C
// 0x0010 (0x03B0 - 0x03A0)
class ABP_ItemPickup_Spawnable_C : public AFGItemPickup_Spawnable
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03A0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UAkAudioEvent*                               mPickupEvent;                                             // 0x03A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_ItemPickup_Spawnable.BP_ItemPickup_Spawnable_C");
		return ptr;
	}


	void UserConstructionScript();
	void PlayPickupEffect();
	void PlaySpawnEffect();
	void ExecuteUbergraph_BP_ItemPickup_Spawnable(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
