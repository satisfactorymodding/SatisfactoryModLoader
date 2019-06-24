#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FrontEnd_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_FrontEnd.BP_FrontEnd_C.CreatePopupWidget
struct UBP_FrontEnd_C_CreatePopupWidget_Params
{
	struct FPopupData*                                 PopupData;                                                // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UFGPopupWidget*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShutdown
struct UBP_FrontEnd_C_ShouldShutdown_Params
{
	bool                                               Shutdown;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.GetErrorButtonText
struct UBP_FrontEnd_C_GetErrorButtonText_Params
{
	struct FText                                       ButtonText;                                               // (Parm, OutParm)
};

// Function BP_FrontEnd.BP_FrontEnd_C.HasMoreErrors
struct UBP_FrontEnd_C_HasMoreErrors_Params
{
	bool                                               moreErrors;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShutdownAfterThisError
struct UBP_FrontEnd_C_ShouldShutdownAfterThisError_Params
{
	bool                                               Shutdown;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowLogin
struct UBP_FrontEnd_C_Internal_ShouldShowLogin_Params
{
	bool                                               ShouldShow;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowLogin
struct UBP_FrontEnd_C_ShouldShowLogin_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.SetNextErrorMessage
struct UBP_FrontEnd_C_SetNextErrorMessage_Params
{
	class UFGErrorMessage*                             newError;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.GetNextErrorMessage
struct UBP_FrontEnd_C_GetNextErrorMessage_Params
{
	class UFGErrorMessage*                             errorMessage;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShowErrorMessage
struct UBP_FrontEnd_C_Internal_ShowErrorMessage_Params
{
	bool                                               ShouldShow;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowMainMenu
struct UBP_FrontEnd_C_Internal_ShouldShowMainMenu_Params
{
	bool                                               ShouldShow;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.Internal_ShouldShowAlphaInfo
struct UBP_FrontEnd_C_Internal_ShouldShowAlphaInfo_Params
{
	bool                                               ShouldShow;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowErrorPopup
struct UBP_FrontEnd_C_ShouldShowErrorPopup_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowMainMenu
struct UBP_FrontEnd_C_ShouldShowMainMenu_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.ShouldShowAlphaInfo
struct UBP_FrontEnd_C_ShouldShowAlphaInfo_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FrontEnd.BP_FrontEnd_C.SetupMainMenu
struct UBP_FrontEnd_C_SetupMainMenu_Params
{
};

// Function BP_FrontEnd.BP_FrontEnd_C.Construct
struct UBP_FrontEnd_C_Construct_Params
{
};

// Function BP_FrontEnd.BP_FrontEnd_C.BndEvt__Widget_ErrorMessage_K2Node_ComponentBoundEvent_0_mOnClicked__DelegateSignature
struct UBP_FrontEnd_C_BndEvt__Widget_ErrorMessage_K2Node_ComponentBoundEvent_0_mOnClicked__DelegateSignature_Params
{
};

// Function BP_FrontEnd.BP_FrontEnd_C.GetAndSetNewError
struct UBP_FrontEnd_C_GetAndSetNewError_Params
{
};

// Function BP_FrontEnd.BP_FrontEnd_C.ConditionallySetNewError
struct UBP_FrontEnd_C_ConditionallySetNewError_Params
{
};

// Function BP_FrontEnd.BP_FrontEnd_C.Destruct
struct UBP_FrontEnd_C_Destruct_Params
{
};

// Function BP_FrontEnd.BP_FrontEnd_C.ClosePopup
struct UBP_FrontEnd_C_ClosePopup_Params
{
};

// Function BP_FrontEnd.BP_FrontEnd_C.ExecuteUbergraph_BP_FrontEnd
struct UBP_FrontEnd_C_ExecuteUbergraph_BP_FrontEnd_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
