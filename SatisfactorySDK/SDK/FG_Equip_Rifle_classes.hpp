#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_Rifle_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_Rifle.Equip_Rifle_C
// 0x002D (0x0445 - 0x0418)
class AEquip_Rifle_C : public AFGWeaponInstantFire
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0418(0x0008) (Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Rifle;                                                    // 0x0420(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0428(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FScriptMulticastDelegate                    Fire;                                                     // 0x0430(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	float                                              mLockAngle;                                               // 0x0440(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mHasReloadedOnce;                                         // 0x0444(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, SaveGame, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_Rifle.Equip_Rifle_C");
		return ptr;
	}


	void UserConstructionScript();
	void ReceiveBeginPlay();
	void PlayReloadEffects();
	void WasUnEquipped();
	void PlayFireEffect();
	void WasEquipped();
	void ExecuteUbergraph_Equip_Rifle(int EntryPoint);
	void Fire__DelegateSignature();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
