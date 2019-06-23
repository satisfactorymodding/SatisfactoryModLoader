#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DropPod_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_DropPod.BP_DropPod_C
// 0x0058 (0x03A8 - 0x0350)
class ABP_DropPod_C : public AFGDropPod
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0350(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UDecalComponent*                             Decal;                                                    // 0x0358(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGPowerInfoComponent*                       powerInfo;                                                // 0x0360(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UFGPowerConnectionComponent*                 PowerInput;                                               // 0x0368(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        StaticMesh;                                               // 0x0370(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0378(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               mContainsServerRack;                                      // 0x0380(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               mContainsHardDrive;                                       // 0x0381(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0382(0x0002) MISSED OFFSET
	float                                              mPowerConsumption;                                        // 0x0384(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData)
	struct FItemAmount                                 mRepairAmount;                                            // 0x0388(0x0010) (Edit, BlueprintVisible, Net)
	TArray<class UClass*>                              LootItems;                                                // 0x0398(0x0010) (Edit, BlueprintVisible, ZeroConstructor, Transient, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_DropPod.BP_DropPod_C");
		return ptr;
	}


	void Repair(class AFGCharacterPlayer* byCharacter);
	void GetRepairAmount(struct FItemAmount* amount);
	void GetPowerConsumption(float* POWER);
	void NeedsPower(bool* NeedsPower);
	void NeedsRepair(bool* NeedsRepair);
	void UserConstructionScript();
	void RollLoot();
	void OnOpened();
	void StopIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void StartIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void ReceiveBeginPlay();
	void OnUse(class AFGCharacterPlayer** byCharacter, struct FUseState* State);
	void ExecuteUbergraph_BP_DropPod(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
