#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_Build_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_MaterialEffect_Build.BP_MaterialEffect_Build_C
// 0x03B8 (0x0518 - 0x0160)
class UBP_MaterialEffect_Build_C : public UFGMaterialEffect_Build
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0160(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	int                                                mCurrentStep;                                             // 0x0168(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              mElapsedTime;                                             // 0x016C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mThrowDuration;                                           // 0x0170(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDisplacementDuration;                                    // 0x0174(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaterializeAmountCurrent;                                // 0x0178(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaterializeAmount;                                       // 0x017C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDisplacementAmount;                                      // 0x0180(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0184(0x0004) MISSED OFFSET
	struct FRuntimeFloatCurve                          mThrowCurve;                                              // 0x0188(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	TArray<class UClass*>                              mThrowQueue;                                              // 0x0200(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	int                                                mCostAmountPerThrow;                                      // 0x0210(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mMaterializeAmountPerThrow;                               // 0x0214(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mGlowPower;                                               // 0x0218(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mVolume;                                                  // 0x021C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mElapsedTimeCorrectionBuildup;                            // 0x0220(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0224(0x0004) MISSED OFFSET
	struct FRuntimeFloatCurve                          mOffsetCurve_Buildup;                                     // 0x0228(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FRuntimeFloatCurve                          mOffsetCurve_Drop;                                        // 0x02A0(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FRuntimeFloatCurve                          mGlowPowerCurve;                                          // 0x0318(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FRuntimeFloatCurve                          mVolumeCurve;                                             // 0x0390(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	int                                                mItemsThrown;                                             // 0x0408(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mBoxBounds;                                               // 0x040C(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     mOrigin;                                                  // 0x0418(0x000C) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0424(0x0004) MISSED OFFSET
	struct FRuntimeFloatCurve                          mParticleCurve;                                           // 0x0428(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)
	struct FRuntimeFloatCurve                          mParticleVeloCurve;                                       // 0x04A0(0x0078) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_MaterialEffect_Build.BP_MaterialEffect_Build_C");
		return ptr;
	}


	void PlayThumpSound();
	void InitMaterialParameters();
	void SetupBounds();
	void GotoNextStep();
	void CalcCostQueueNewLength(int* NewLength);
	void DebugFillCostQueue();
	void CalcDisplacementAmount(float* amount);
	void UpdateCostQueue();
	void SetupCostQueue();
	void SetupDuration();
	void SetupMeshes();
	void SpawnFootEmitters();
	void OnUpdate(float* DeltaTime);
	void OnEnded();
	void PreStarted();
	void OnStarted();
	void OnCostActorReachedTarget();
	void ExecuteUbergraph_BP_MaterialEffect_Build(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
