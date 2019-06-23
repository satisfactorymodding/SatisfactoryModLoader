#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PlayerController_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_PlayerController.BP_PlayerController_C
// 0x00B0 (0x0858 - 0x07A8)
class ABP_PlayerController_C : public AFGPlayerController
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x07A8(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UAudioComponent*                             mDialogueComponent;                                       // 0x07B0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              mRespawnFadeOutTime;                                      // 0x07B8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x07BC(0x0004) MISSED OFFSET
	struct FPopupData                                  mPopupDataTest;                                           // 0x07C0(0x0068) (Edit, BlueprintVisible, DisableEditOnInstance)
	class UWidget_MapContainer_C*                      mMinimapWidget;                                           // 0x0828(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	struct FScriptMulticastDelegate                    OnBeginTypeChat;                                          // 0x0830(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	class UWidget_PhotoMode_C*                         PhotoModeInstructionsWidget;                              // 0x0840(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	struct FScriptMulticastDelegate                    OnRespawnEnd;                                             // 0x0848(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_PlayerController.BP_PlayerController_C");
		return ptr;
	}


	class UAkComponent* OnSetupMovementWind();
	void OnDisabledInputChanged();
	void ToggleMiniMap();
	void DismantlePortableMiner(class ABP_PortableMiner_C* PortableMiner);
	void UserConstructionScript();
	void InpActEvt_Chat_K2Node_InputActionEvent_17(const struct FKey& Key);
	void InpActEvt_Shortcut1_K2Node_InputActionEvent_16(const struct FKey& Key);
	void InpActEvt_Shortcut2_K2Node_InputActionEvent_15(const struct FKey& Key);
	void InpActEvt_Shortcut3_K2Node_InputActionEvent_14(const struct FKey& Key);
	void InpActEvt_Shortcut4_K2Node_InputActionEvent_13(const struct FKey& Key);
	void InpActEvt_Shortcut5_K2Node_InputActionEvent_12(const struct FKey& Key);
	void InpActEvt_Shortcut6_K2Node_InputActionEvent_11(const struct FKey& Key);
	void InpActEvt_Shortcut7_K2Node_InputActionEvent_10(const struct FKey& Key);
	void InpActEvt_Shortcut8_K2Node_InputActionEvent_9(const struct FKey& Key);
	void InpActEvt_Shortcut9_K2Node_InputActionEvent_8(const struct FKey& Key);
	void InpActEvt_Shortcut10_K2Node_InputActionEvent_7(const struct FKey& Key);
	void InpActEvt_PauseGame_K2Node_InputActionEvent_6(const struct FKey& Key);
	void InpActEvt_PhotoMode_K2Node_InputActionEvent_5(const struct FKey& Key);
	void InpActEvt_ToggleMap_BuildGunNoSnapMode_K2Node_InputActionEvent_4(const struct FKey& Key);
	void InpActEvt_Prototype_RagdollPlayer_K2Node_InputActionEvent_3(const struct FKey& Key);
	void InpActEvt_SecondaryFire_K2Node_InputActionEvent_2(const struct FKey& Key);
	void InpActEvt_TogglePhotoModeUIVisibility_K2Node_InputActionEvent_1(const struct FKey& Key);
	void OnFinishRespawn();
	void OnStartRespawn(bool* isJoining);
	void DoPause();
	void CheckAndUpdateGamepad();
	void LocalAudioBeginPlay();
	void ReceiveTick(float* DeltaSeconds);
	void Server_ForceRagdoll();
	void ReceiveBeginPlay();
	void OnDisabledInputGateChanged();
	void CreateSequenceList();
	void TogglePhotoModeInstructionsWidget();
	void PlayPhotoSound();
	void TakePhoto();
	void ExecuteUbergraph_BP_PlayerController(int EntryPoint);
	void OnRespawnEnd__DelegateSignature();
	void OnBeginTypeChat__DelegateSignature();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
