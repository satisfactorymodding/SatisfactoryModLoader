#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_ObjectScanner_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_ObjectScanner.Equip_ObjectScanner_C
// 0x0040 (0x04B8 - 0x0478)
class AEquip_ObjectScanner_C : public AFGObjectScanner
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0478(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UPointLightComponent*                        PointLight;                                               // 0x0480(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USkeletalMeshComponent*                      CrystalScanner_skl;                                       // 0x0488(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             SomeDumbShitThatFixesScaleOrSomething;                    // 0x0490(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget_ObjectScannerMenu_C*                 mObjectScannerMenu;                                       // 0x0498(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UAkComponent*                                mAKLoopingSound;                                          // 0x04A0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mPlayingSound;                                            // 0x04A8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x04A9(0x0007) MISSED OFFSET
	class AActor*                                      mSoundAttachedTo;                                         // 0x04B0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_ObjectScanner.Equip_ObjectScanner_C");
		return ptr;
	}


	void UserConstructionScript();
	void InpActEvt_PrimaryFire_K2Node_InputActionEvent_3(const struct FKey& Key);
	void InpActEvt_PrimaryFire_K2Node_InputActionEvent_2(const struct FKey& Key);
	void InpActEvt_SecondaryFire_K2Node_InputActionEvent_1(const struct FKey& Key);
	void PlayBeep(bool* isObjectInRange);
	void ReceiveTick(float* DeltaSeconds);
	void UpdateScannerVisuals(bool* wasChange);
	void WasEquipped();
	void WasUnEquipped();
	void ExecuteUbergraph_Equip_ObjectScanner(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
