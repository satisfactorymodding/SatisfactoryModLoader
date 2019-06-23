#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Explorer_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_Explorer.BP_Explorer_C
// 0x0050 (0x08B0 - 0x0860)
class ABP_Explorer_C : public ABP_WheeledVehicle4W_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0860(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Workbench;                                                // 0x0868(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USpotLightComponent*                         SpotLight;                                                // 0x0870(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UBP_WorkBenchComponent_C*                    BP_WorkBenchComponent;                                    // 0x0878(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UPostProcessComponent*                       PostProcess;                                              // 0x0880(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UCameraComponent*                            Camera;                                                   // 0x0888(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USpringArmComponent*                         SpringArm;                                                // 0x0890(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              throttleval;                                              // 0x0898(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               mFlashlightOn;                                            // 0x089C(0x0001) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x089D(0x0003) MISSED OFFSET
	float                                              mSuspensionLoadTimer;                                     // 0x08A0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSuspensionLoadTimerDefault;                              // 0x08A4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSuspensionTick;                                          // 0x08A8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              mSuspensionTickDefault;                                   // 0x08AC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_Explorer.BP_Explorer_C");
		return ptr;
	}


	struct FText GetActorRepresentationText();
	class UTexture2D* GetActorRepresentationTexture();
	void CheckSuspension(float InDeltaTime);
	void OnRep_mFlashlightOn();
	struct FVector GetAttackLocation();
	float GetEnemyTargetDesirability(class AFGEnemyController** forController);
	bool ShouldAutoregisterAsTargetable();
	void UserConstructionScript();
	void InpActEvt_Flashlight_K2Node_InputActionEvent_1(const struct FKey& Key);
	void InpActEvt_Y_K2Node_InputKeyEvent_3(const struct FKey& Key);
	void InpActEvt_NumPadZero_K2Node_InputKeyEvent_2(const struct FKey& Key);
	void InpActEvt_NumPadOne_K2Node_InputKeyEvent_1(const struct FKey& Key);
	void ReceiveTick(float* DeltaSeconds);
	void CloseTrunk();
	void OpenTrunk();
	void InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1(float AxisValue);
	void Server_SetFlashlightOn(bool FlashlightOn);
	void ExecuteUbergraph_BP_Explorer(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
