#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_HUD_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass BP_HUD.BP_HUD_C
// 0x0020 (0x04F8 - 0x04D8)
class ABP_HUD_C : public AFGHUD
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x04D8(0x0008) (Transient, DuplicateTransient)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x04E0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAkAudioEvent*                               mOpenInventorySound;                                      // 0x04E8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UAkAudioEvent*                               mCloseInventorySound;                                     // 0x04F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass BP_HUD.BP_HUD_C");
		return ptr;
	}


	void IsInventoryOpen(bool* IsOpen);
	void GetBP_GameUI(class UBP_GameUI_C** BPGameUI);
	void SetupFrontEnd();
	void UserConstructionScript();
	void ToggleInventoryUI();
	void OpenInventoryUI();
	void OpenInteractUI(class UClass** WidgetClass, class UObject** interactObject);
	void RemovePawnHUD();
	void AddEquipmentHUD(class UClass** WidgetClass, EEquipmentSlot* Slot);
	void RemoveEquipmentHUD(EEquipmentSlot* Slot);
	void CloseInteractUIIfOpen();
	void ExecuteUbergraph_BP_HUD(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
