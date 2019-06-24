#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceScanner_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_ResourceScanner.BP_ResourceScanner_C
// 0x0058 (0x0448 - 0x03F0)
class ABP_ResourceScanner_C : public AFGResourceScanner
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03F0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      BuildGun;                                                 // 0x03F8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x0400(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              Timeline_0_NewTrack_0_8D03DE94407B43FDF4CBEDAE711F64BC;   // 0x0408(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ETimelineDirection>                    Timeline_0__Direction_8D03DE94407B43FDF4CBEDAE711F64BC;   // 0x040C(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x040D(0x0003) MISSED OFFSET
	class UTimelineComponent*                          Timeline_1;                                               // 0x0410(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget_ResourceScanner_C*                   scannerWidget;                                            // 0x0418(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	float                                              mScannerTravelSpeed;                                      // 0x0420(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                mFakeLoopIndex;                                           // 0x0424(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mAcumulatedDelay;                                         // 0x0428(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mDelayAfterSound;                                         // 0x042C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FScriptMulticastDelegate                    OnClustersFound;                                          // 0x0430(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	class AFGActorRepresentationManager*               mActorRepresentationManager;                              // 0x0440(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_ResourceScanner.BP_ResourceScanner_C");
		return ptr;
	}


	void IsScannerWheelVisible(bool* IsVisible);
	void UserConstructionScript();
	void Timeline_0__FinishedFunc();
	void Timeline_0__UpdateFunc();
	void ShowResourceDescriptorSelectUI();
	void CloseResourceDescriptorSelectUI();
	void PlayClusterEffects(TArray<struct FNodeClusterData>* clusters);
	void Event_Play_Pulse_Effect();
	void CustomEvent_1();
	void ExecuteUbergraph_BP_ResourceScanner(int EntryPoint);
	void OnClustersFound__DelegateSignature(TArray<struct FNodeClusterData>* ClustersFound);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
