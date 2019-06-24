#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ProfileSpline_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_ProfileSpline.BP_ProfileSpline_C
// 0x003C (0x036C - 0x0330)
class ABP_ProfileSpline_C : public AFGProfileSpline
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0330(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USplineComponent*                            Spline;                                                   // 0x0338(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               bInitialized;                                             // 0x0340(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0341(0x0007) MISSED OFFSET
	struct FTimerHandle                                FindControllerTimer;                                      // 0x0348(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	class AFGPlayerController*                         FGCharacter;                                              // 0x0350(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	struct FTimerHandle                                FinalizeSpawningPlayer;                                   // 0x0358(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	class ACameraActor*                                CameraActor;                                              // 0x0360(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	float                                              CurrenTime;                                               // 0x0368(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_ProfileSpline.BP_ProfileSpline_C");
		return ptr;
	}


	void CheckDoneRespawning(bool* bDoneSpawning);
	void GetPlayerController(bool* bIsValid, class APlayerController** PlayerController);
	void UserConstructionScript();
	void ReceiveTick(float* DeltaSeconds);
	void FetchPlayerPawn();
	void StartProfile();
	void EnsurePlayerDoneSpawning();
	void ExecuteUbergraph_BP_ProfileSpline(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
