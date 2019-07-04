#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_HUDHelpers_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function HUDHelpers.HUDHelpers_C.GetDefaultRCO
struct UHUDHelpers_C_GetDefaultRCO_Params
{
	class APlayerController*                           OwningPlayer;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UBP_RemoteCallObject_C*                      RCO;                                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.IsInMainMenu
struct UHUDHelpers_C_IsInMainMenu_Params
{
	class UObject*                                     WorldContext;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsInMainMenu;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetFGGameUI
struct UHUDHelpers_C_GetFGGameUI_Params
{
	class AController*                                 Controller;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGGameUI*                                   gameUI;                                                   // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetNumItemsFromCentralStorage
struct UHUDHelpers_C_GetNumItemsFromCentralStorage_Params
{
	class APawn*                                       OwningPawn;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      mItemClass;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumItems;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetNumItemsOwned
struct UHUDHelpers_C_GetNumItemsOwned_Params
{
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetFactoryGameLightBlue
struct UHUDHelpers_C_GetFactoryGameLightBlue_Params
{
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                Graphics;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 Text;                                                     // (Parm, OutParm)
};

// Function HUDHelpers.HUDHelpers_C.GetFactoryGameLightGray
struct UHUDHelpers_C_GetFactoryGameLightGray_Params
{
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 Text;                                                     // (Parm, OutParm)
	struct FLinearColor                                Graphics;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetFactoryGameDarkGray
struct UHUDHelpers_C_GetFactoryGameDarkGray_Params
{
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 Text;                                                     // (Parm, OutParm)
	struct FLinearColor                                Graphics;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.SetSliderSteps
struct UHUDHelpers_C_SetSliderSteps_Params
{
	class USlider*                                     mSlider;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                mSteps;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetScanningObjectName
struct UHUDHelpers_C_GetScanningObjectName_Params
{
	class APawn*                                       OwningPawn;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Object_Name;                                              // (Parm, OutParm)
};

// Function HUDHelpers.HUDHelpers_C.ShowHideHUD
struct UHUDHelpers_C_ShowHideHUD_Params
{
	bool                                               isMenuOpen;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn*                                       OwningPawn;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 Controller;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetNumItemsFromInventory
struct UHUDHelpers_C_GetNumItemsFromInventory_Params
{
	class UFGInventoryComponent*                       InventoryComponent;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UClass*                                      mItemClass;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumItems;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetFactoryGameOrange
struct UHUDHelpers_C_GetFactoryGameOrange_Params
{
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                Orange;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 OrangeText;                                               // (Parm, OutParm)
};

// Function HUDHelpers.HUDHelpers_C.GetFactoryGameWhite
struct UHUDHelpers_C_GetFactoryGameWhite_Params
{
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FSlateColor                                 TextWhite;                                                // (Parm, OutParm)
	struct FLinearColor                                GraphicsWhite;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function HUDHelpers.HUDHelpers_C.GetNumItemsFromPlayerInventory
struct UHUDHelpers_C_GetNumItemsFromPlayerInventory_Params
{
	class APawn*                                       OwningPawn;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      mItemClass;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UObject*                                     __WorldContext;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumItems;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
