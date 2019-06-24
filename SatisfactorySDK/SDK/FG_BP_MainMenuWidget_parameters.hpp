#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MainMenuWidget_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetExperimentalVisibility
struct UBP_MainMenuWidget_C_GetExperimentalVisibility_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.UpdateUsername
struct UBP_MainMenuWidget_C_UpdateUsername_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.UpdateVersionString
struct UBP_MainMenuWidget_C_UpdateVersionString_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetMostRecentSave
struct UBP_MainMenuWidget_C_GetMostRecentSave_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.GetVersionString
struct UBP_MainMenuWidget_C_GetVersionString_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnEscape
struct UBP_MainMenuWidget_C_OnEscape_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonQuit_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UBP_MainMenuWidget_C_BndEvt__mButtonQuit_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.Construct
struct UBP_MainMenuWidget_C_Construct_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonContinue_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UBP_MainMenuWidget_C_BndEvt__mButtonContinue_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.BndEvt__mButtonMP_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
struct UBP_MainMenuWidget_C_BndEvt__mButtonMP_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnExit
struct UBP_MainMenuWidget_C_OnExit_Params
{
	bool                                               Bool;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.NATTypeUpdated
struct UBP_MainMenuWidget_C_NATTypeUpdated_Params
{
	ECachedNATType                                     natType;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.Destruct
struct UBP_MainMenuWidget_C_Destruct_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnMenuEnter
struct UBP_MainMenuWidget_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.LoginStateChanged
struct UBP_MainMenuWidget_C_LoginStateChanged_Params
{
	TEnumAsByte<ELoginState>                           oldState;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ELoginState>                           newState;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.ExecuteUbergraph_BP_MainMenuWidget
struct UBP_MainMenuWidget_C_ExecuteUbergraph_BP_MainMenuWidget_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnCreditsClicked__DelegateSignature
struct UBP_MainMenuWidget_C_OnCreditsClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnModsClicked__DelegateSignature
struct UBP_MainMenuWidget_C_OnModsClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnOptionsClicked__DelegateSignature
struct UBP_MainMenuWidget_C_OnOptionsClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnLoadClicked__DelegateSignature
struct UBP_MainMenuWidget_C_OnLoadClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnExitClicked__DelegateSignature
struct UBP_MainMenuWidget_C_OnExitClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnBrowseClicked__DelegateSignature
struct UBP_MainMenuWidget_C_OnBrowseClicked__DelegateSignature_Params
{
};

// Function BP_MainMenuWidget.BP_MainMenuWidget_C.OnPlayClicked__DelegateSignature
struct UBP_MainMenuWidget_C_OnPlayClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
