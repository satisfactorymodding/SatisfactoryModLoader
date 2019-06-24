#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CreatureSeat_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_CreatureSeat.BP_CreatureSeat_C
// 0x0028 (0x03F8 - 0x03D0)
class ABP_CreatureSeat_C : public AFGCreatureSeat
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x03D0(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UCameraComponent*                            Camera;                                                   // 0x03D8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USpringArmComponent*                         SpringArm;                                                // 0x03E0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UStaticMeshComponent*                        Cube;                                                     // 0x03E8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x03F0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_CreatureSeat.BP_CreatureSeat_C");
		return ptr;
	}


	void UserConstructionScript();
	void InpActEvt_Use_K2Node_InputActionEvent_2(const struct FKey& Key);
	void InpActEvt_Jump_Drift_K2Node_InputActionEvent_1(const struct FKey& Key);
	void InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1(float AxisValue);
	void UpdateCamera();
	void ReceiveTick(float* DeltaSeconds);
	void ReceivePossessed(class AController** NewController);
	void ClientSetupHUD(class AFGPlayerController* Controller);
	void Server_Leave();
	void Server_DoAction();
	void Multicast_PlayClap();
	void Server_PlayClap();
	void PlayClap();
	void ExecuteUbergraph_BP_CreatureSeat(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
