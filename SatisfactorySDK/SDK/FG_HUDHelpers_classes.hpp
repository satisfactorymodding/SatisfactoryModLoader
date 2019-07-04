#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_HUDHelpers_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass HUDHelpers.HUDHelpers_C
// 0x0000 (0x0028 - 0x0028)
class UHUDHelpers_C : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass HUDHelpers.HUDHelpers_C");
		return ptr;
	}


	void GetDefaultRCO(class APlayerController* OwningPlayer, class UObject* __WorldContext, class UBP_RemoteCallObject_C** RCO);
	void IsInMainMenu(class UObject* WorldContext, class UObject* __WorldContext, bool* IsInMainMenu);
	void GetFGGameUI(class AController* Controller, class UObject* __WorldContext, class UFGGameUI** gameUI);
	void GetNumItemsFromCentralStorage(class APawn* OwningPawn, class UClass* mItemClass, class UObject* __WorldContext, int* NumItems);
	void GetNumItemsOwned(class UObject* __WorldContext);
	void GetFactoryGameLightBlue(class UObject* __WorldContext, struct FLinearColor* Graphics, struct FSlateColor* Text);
	void GetFactoryGameLightGray(class UObject* __WorldContext, struct FSlateColor* Text, struct FLinearColor* Graphics);
	void GetFactoryGameDarkGray(class UObject* __WorldContext, struct FSlateColor* Text, struct FLinearColor* Graphics);
	void SetSliderSteps(class USlider* mSlider, int mSteps, class UObject* __WorldContext);
	void GetScanningObjectName(class APawn* OwningPawn, class UObject* __WorldContext, struct FText* Object_Name);
	void ShowHideHUD(bool isMenuOpen, class APawn* OwningPawn, class AController* Controller, class UObject* __WorldContext);
	void GetNumItemsFromInventory(class UFGInventoryComponent* InventoryComponent, class UClass* mItemClass, class UObject* __WorldContext, int* NumItems);
	void GetFactoryGameOrange(class UObject* __WorldContext, struct FLinearColor* Orange, struct FSlateColor* OrangeText);
	void GetFactoryGameWhite(class UObject* __WorldContext, struct FSlateColor* TextWhite, struct FLinearColor* GraphicsWhite);
	void GetNumItemsFromPlayerInventory(class APawn* OwningPawn, class UClass* mItemClass, class UObject* __WorldContext, int* NumItems);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
