#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MenuBase_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass BP_MenuBase.BP_MenuBase_C
// 0x0041 (0x0251 - 0x0210)
class UBP_MenuBase_C : public UFGMenuBase
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0210(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UUserWidget*                                 mFocusWidget;                                             // 0x0218(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mHandleEscape;                                            // 0x0220(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0221(0x0007) MISSED OFFSET
	class UBP_MenuBase_C*                              mOwningMenu;                                              // 0x0228(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               UsesSubmenuBackground;                                    // 0x0230(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0231(0x0007) MISSED OFFSET
	class UWidgetAnimation*                            mOnEnterAnimation;                                        // 0x0238(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	TArray<class UWidget_SubMenuBackground_C*>         mSubmenusToAnimate;                                       // 0x0240(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	bool                                               mNeedCustomEnterDone;                                     // 0x0250(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass BP_MenuBase.BP_MenuBase_C");
		return ptr;
	}


	void GatherBackgrounds();
	void PlayBackgroundEnterAnimation();
	void PlayEnterAnimation(class UWidget* prevMenu);
	void ShouldAnimateBackground(class UWidget* prevMenu, bool* Animate);
	void RestoreFocusOnPopupClosed(bool confirm);
	struct FEventReply OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent);
	void OnEscape();
	void MenuExit();
	void MenuEnter(class UBP_MenuBase_C* inOwner);
	void Destruct();
	void Construct();
	void SpawnAnim(bool PlayBackgroundAnim);
	void OnMenuEnter(class UWidget** prevMenu);
	void OnAnimationFinished(class UWidgetAnimation** Animation);
	void OnMenuExit(class UWidget** prevMenu, bool* noAnimation);
	void ExecuteUbergraph_BP_MenuBase(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
