#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_ColorGun_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass Equip_ColorGun.Equip_ColorGun_C
// 0x0020 (0x04D8 - 0x04B8)
class AEquip_ColorGun_C : public AFGColorGun
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x04B8(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class USkeletalMeshComponent*                      Colorgun_skl;                                             // 0x04C0(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class USceneComponent*                             DefaultSceneRoot;                                         // 0x04C8(0x0008) (BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget_ColorGunUI_C*                        mColorWidget;                                             // 0x04D0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass Equip_ColorGun.Equip_ColorGun_C");
		return ptr;
	}


	void UserConstructionScript();
	void ToggleColorPickerUI();
	void PlayFireEffect();
	void PlayReloadEffects();
	void WasEquipped();
	void Event_Clear_Color_Picker_UI();
	void WasUnEquipped();
	void ExecuteUbergraph_Equip_ColorGun(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
