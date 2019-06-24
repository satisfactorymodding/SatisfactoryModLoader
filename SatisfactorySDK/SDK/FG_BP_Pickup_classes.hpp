#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Pickup_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Pickup.BP_Pickup_C
// 0x0018 (0x03A8 - 0x0390)
class ABP_Pickup_C : public AFGItemPickup
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0390(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UStaticMeshComponent*                        StaticMesh;                                               // 0x0398(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAkAudioEvent*                               mPickupEvent;                                             // 0x03A0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Pickup.BP_Pickup_C");
		return ptr;
	}


	void UserConstructionScript();
	void StartIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void StopIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void ReceiveBeginPlay();
	void GainedSignificance();
	void LostSignificance();
	void PlayPickupEffect();
	void ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason);
	void ExecuteUbergraph_BP_Pickup(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
