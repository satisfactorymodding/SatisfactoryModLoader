#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SpitterProjectileSingle_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C
// 0x0038 (0x03E0 - 0x03A8)
class ABP_SpitterProjectileSingle_C : public AFGProjectile
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03A8(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UParticleSystemComponent*                    Projectile;                                               // 0x03B0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        Sphere;                                                   // 0x03B8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              Gravity_Scale_over_Time_Gravity_Scale_02A6598A4993DE75B793A890687A4F4F;// 0x03C0(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ETimelineDirection>                    Gravity_Scale_over_Time__Direction_02A6598A4993DE75B793A890687A4F4F;// 0x03C4(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x03C5(0x0003) MISSED OFFSET
	class UTimelineComponent*                          Gravity_Scale_over_Time;                                  // 0x03C8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mSpeedAdjustment;                                         // 0x03D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mDoSplit;                                                 // 0x03D4(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x03D5(0x0003) MISSED OFFSET
	int                                                mNumberofSplitProjectiles;                                // 0x03D8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSplitConeHalfAngle;                                      // 0x03DC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_SpitterProjectileSingle.BP_SpitterProjectileSingle_C");
		return ptr;
	}


	void UserConstructionScript();
	void Gravity_Scale_over_Time__FinishedFunc();
	void Gravity_Scale_over_Time__UpdateFunc();
	void ReceiveBeginPlay();
	void BndEvt__mProjectileMovement_K2Node_ComponentBoundEvent_0_ActorComponentActivatedSignature__DelegateSignature(class UActorComponent* component, bool bReset);
	void PlayExplosionEffects();
	void ExecuteUbergraph_BP_SpitterProjectileSingle(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
