#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CostEffectActor_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_CostEffectActor.BP_CostEffectActor_C
// 0x01D8 (0x0500 - 0x0328)
class ABP_CostEffectActor_C : public AActor
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0328(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UParticleSystemComponent*                    TrailEffect;                                              // 0x0330(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        ItemMesh;                                                 // 0x0338(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0340(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FVector                                     mTargetLocation;                                          // 0x0348(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mTargetExtent;                                            // 0x0354(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UClass*                                      mItemDescriptor;                                          // 0x0358(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    mRotationRate;                                            // 0x0360(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x036C(0x0004) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnReachedTarget;                                          // 0x0370(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	float                                              mTravelLength;                                            // 0x0380(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mArcOffset;                                               // 0x0384(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FRuntimeFloatCurve                          mArcCurveX;                                               // 0x0390(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FRuntimeFloatCurve                          mArcCurveY;                                               // 0x0408(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FRuntimeFloatCurve                          mArcCurve_SAFE;                                           // 0x0480(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	class UParticleSystemComponent*                    mTrailVfx;                                                // 0x04F8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_CostEffectActor.BP_CostEffectActor_C");
		return ptr;
	}


	void UserConstructionScript();
	void ReceiveBeginPlay();
	void ReceiveTick(float* DeltaSeconds);
	void ExecuteUbergraph_BP_CostEffectActor(int EntryPoint);
	void OnReachedTarget__DelegateSignature();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
