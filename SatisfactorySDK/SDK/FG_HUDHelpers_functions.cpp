// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_HUDHelpers_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function HUDHelpers.HUDHelpers_C.GetDefaultRCO
// ()
// Parameters:
// class APlayerController*       OwningPlayer                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UBP_RemoteCallObject_C*  RCO                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::GetDefaultRCO(class APlayerController* OwningPlayer, class UObject* __WorldContext, class UBP_RemoteCallObject_C** RCO)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetDefaultRCO");

	UHUDHelpers_C_GetDefaultRCO_Params params;
	params.OwningPlayer = OwningPlayer;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (RCO != nullptr)
		*RCO = params.RCO;
}


// Function HUDHelpers.HUDHelpers_C.IsInMainMenu
// ()
// Parameters:
// class UObject*                 WorldContext                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           IsInMainMenu                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::IsInMainMenu(class UObject* WorldContext, class UObject* __WorldContext, bool* IsInMainMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.IsInMainMenu");

	UHUDHelpers_C_IsInMainMenu_Params params;
	params.WorldContext = WorldContext;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsInMainMenu != nullptr)
		*IsInMainMenu = params.IsInMainMenu;
}


// Function HUDHelpers.HUDHelpers_C.GetFGGameUI
// ()
// Parameters:
// class AController*             Controller                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UFGGameUI*               gameUI                         (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UHUDHelpers_C::GetFGGameUI(class AController* Controller, class UObject* __WorldContext, class UFGGameUI** gameUI)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetFGGameUI");

	UHUDHelpers_C_GetFGGameUI_Params params;
	params.Controller = Controller;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (gameUI != nullptr)
		*gameUI = params.gameUI;
}


// Function HUDHelpers.HUDHelpers_C.GetNumItemsFromCentralStorage
// ()
// Parameters:
// class APawn*                   OwningPawn                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  mItemClass                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumItems                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::GetNumItemsFromCentralStorage(class APawn* OwningPawn, class UClass* mItemClass, class UObject* __WorldContext, int* NumItems)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetNumItemsFromCentralStorage");

	UHUDHelpers_C_GetNumItemsFromCentralStorage_Params params;
	params.OwningPawn = OwningPawn;
	params.mItemClass = mItemClass;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NumItems != nullptr)
		*NumItems = params.NumItems;
}


// Function HUDHelpers.HUDHelpers_C.GetNumItemsOwned
// ()
// Parameters:
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::GetNumItemsOwned(class UObject* __WorldContext)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetNumItemsOwned");

	UHUDHelpers_C_GetNumItemsOwned_Params params;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function HUDHelpers.HUDHelpers_C.GetFactoryGameLightBlue
// ()
// Parameters:
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            Graphics                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FSlateColor             Text                           (Parm, OutParm)

void UHUDHelpers_C::GetFactoryGameLightBlue(class UObject* __WorldContext, struct FLinearColor* Graphics, struct FSlateColor* Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetFactoryGameLightBlue");

	UHUDHelpers_C_GetFactoryGameLightBlue_Params params;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Graphics != nullptr)
		*Graphics = params.Graphics;
	if (Text != nullptr)
		*Text = params.Text;
}


// Function HUDHelpers.HUDHelpers_C.GetFactoryGameLightGray
// ()
// Parameters:
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateColor             Text                           (Parm, OutParm)
// struct FLinearColor            Graphics                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::GetFactoryGameLightGray(class UObject* __WorldContext, struct FSlateColor* Text, struct FLinearColor* Graphics)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetFactoryGameLightGray");

	UHUDHelpers_C_GetFactoryGameLightGray_Params params;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Text != nullptr)
		*Text = params.Text;
	if (Graphics != nullptr)
		*Graphics = params.Graphics;
}


// Function HUDHelpers.HUDHelpers_C.GetFactoryGameDarkGray
// ()
// Parameters:
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateColor             Text                           (Parm, OutParm)
// struct FLinearColor            Graphics                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::GetFactoryGameDarkGray(class UObject* __WorldContext, struct FSlateColor* Text, struct FLinearColor* Graphics)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetFactoryGameDarkGray");

	UHUDHelpers_C_GetFactoryGameDarkGray_Params params;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Text != nullptr)
		*Text = params.Text;
	if (Graphics != nullptr)
		*Graphics = params.Graphics;
}


// Function HUDHelpers.HUDHelpers_C.SetSliderSteps
// ()
// Parameters:
// class USlider*                 mSlider                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            mSteps                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::SetSliderSteps(class USlider* mSlider, int mSteps, class UObject* __WorldContext)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.SetSliderSteps");

	UHUDHelpers_C_SetSliderSteps_Params params;
	params.mSlider = mSlider;
	params.mSteps = mSteps;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function HUDHelpers.HUDHelpers_C.GetScanningObjectName
// ()
// Parameters:
// class APawn*                   OwningPawn                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   Object_Name                    (Parm, OutParm)

void UHUDHelpers_C::GetScanningObjectName(class APawn* OwningPawn, class UObject* __WorldContext, struct FText* Object_Name)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetScanningObjectName");

	UHUDHelpers_C_GetScanningObjectName_Params params;
	params.OwningPawn = OwningPawn;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Object_Name != nullptr)
		*Object_Name = params.Object_Name;
}


// Function HUDHelpers.HUDHelpers_C.ShowHideHUD
// ()
// Parameters:
// bool                           isMenuOpen                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn*                   OwningPawn                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController*             Controller                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::ShowHideHUD(bool isMenuOpen, class APawn* OwningPawn, class AController* Controller, class UObject* __WorldContext)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.ShowHideHUD");

	UHUDHelpers_C_ShowHideHUD_Params params;
	params.isMenuOpen = isMenuOpen;
	params.OwningPawn = OwningPawn;
	params.Controller = Controller;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function HUDHelpers.HUDHelpers_C.GetNumItemsFromInventory
// ()
// Parameters:
// class UFGInventoryComponent*   InventoryComponent             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UClass*                  mItemClass                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumItems                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::GetNumItemsFromInventory(class UFGInventoryComponent* InventoryComponent, class UClass* mItemClass, class UObject* __WorldContext, int* NumItems)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetNumItemsFromInventory");

	UHUDHelpers_C_GetNumItemsFromInventory_Params params;
	params.InventoryComponent = InventoryComponent;
	params.mItemClass = mItemClass;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NumItems != nullptr)
		*NumItems = params.NumItems;
}


// Function HUDHelpers.HUDHelpers_C.GetFactoryGameOrange
// ()
// Parameters:
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            Orange                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FSlateColor             OrangeText                     (Parm, OutParm)

void UHUDHelpers_C::GetFactoryGameOrange(class UObject* __WorldContext, struct FLinearColor* Orange, struct FSlateColor* OrangeText)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetFactoryGameOrange");

	UHUDHelpers_C_GetFactoryGameOrange_Params params;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Orange != nullptr)
		*Orange = params.Orange;
	if (OrangeText != nullptr)
		*OrangeText = params.OrangeText;
}


// Function HUDHelpers.HUDHelpers_C.GetFactoryGameWhite
// ()
// Parameters:
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateColor             TextWhite                      (Parm, OutParm)
// struct FLinearColor            GraphicsWhite                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::GetFactoryGameWhite(class UObject* __WorldContext, struct FSlateColor* TextWhite, struct FLinearColor* GraphicsWhite)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetFactoryGameWhite");

	UHUDHelpers_C_GetFactoryGameWhite_Params params;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (TextWhite != nullptr)
		*TextWhite = params.TextWhite;
	if (GraphicsWhite != nullptr)
		*GraphicsWhite = params.GraphicsWhite;
}


// Function HUDHelpers.HUDHelpers_C.GetNumItemsFromPlayerInventory
// ()
// Parameters:
// class APawn*                   OwningPawn                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  mItemClass                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumItems                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UHUDHelpers_C::GetNumItemsFromPlayerInventory(class APawn* OwningPawn, class UClass* mItemClass, class UObject* __WorldContext, int* NumItems)
{
	static auto fn = UObject::FindObject<UFunction>("Function HUDHelpers.HUDHelpers_C.GetNumItemsFromPlayerInventory");

	UHUDHelpers_C_GetNumItemsFromPlayerInventory_Params params;
	params.OwningPawn = OwningPawn;
	params.mItemClass = mItemClass;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NumItems != nullptr)
		*NumItems = params.NumItems;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
