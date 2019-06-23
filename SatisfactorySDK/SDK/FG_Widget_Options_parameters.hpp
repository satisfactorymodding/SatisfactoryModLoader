#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Options_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Options.Widget_Options_C.BindEventsForGameplayOptions
struct UWidget_Options_C_BindEventsForGameplayOptions_Params
{
};

// Function Widget_Options.Widget_Options_C.ResetMouseSensitivity
struct UWidget_Options_C_ResetMouseSensitivity_Params
{
};

// Function Widget_Options.Widget_Options_C.ResetAudioSettings
struct UWidget_Options_C_ResetAudioSettings_Params
{
};

// Function Widget_Options.Widget_Options_C.UpdateGameplaySettings
struct UWidget_Options_C_UpdateGameplaySettings_Params
{
};

// Function Widget_Options.Widget_Options_C.SetCurrentAnalyticsSetting
struct UWidget_Options_C_SetCurrentAnalyticsSetting_Params
{
};

// Function Widget_Options.Widget_Options_C.SetCurrentHeadbobScale
struct UWidget_Options_C_SetCurrentHeadbobScale_Params
{
};

// Function Widget_Options.Widget_Options_C.UpdatePostProcessValues
struct UWidget_Options_C_UpdatePostProcessValues_Params
{
};

// Function Widget_Options.Widget_Options_C.SetupSubmenuOptionsForSpawnAnim
struct UWidget_Options_C_SetupSubmenuOptionsForSpawnAnim_Params
{
	TArray<class UUserWidget*>                         ActiveOptions;                                            // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_Options.Widget_Options_C.OnAudioValueChanged
struct UWidget_Options_C_OnAudioValueChanged_Params
{
	float                                              NewParam;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.OnResolutionChanged
struct UWidget_Options_C_OnResolutionChanged_Params
{
	class FString                                      selected_item;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	TEnumAsByte<ESelectInfo>                           selection_type;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.OnDefaultKeybindPressed
struct UWidget_Options_C_OnDefaultKeybindPressed_Params
{
};

// Function Widget_Options.Widget_Options_C.UpdateControlSettings
struct UWidget_Options_C_UpdateControlSettings_Params
{
};

// Function Widget_Options.Widget_Options_C.SetCurrentArachnophobiaMode
struct UWidget_Options_C_SetCurrentArachnophobiaMode_Params
{
};

// Function Widget_Options.Widget_Options_C.SetCurrentLanguage
struct UWidget_Options_C_SetCurrentLanguage_Params
{
};

// Function Widget_Options.Widget_Options_C.ApplyControlsSettings
struct UWidget_Options_C_ApplyControlsSettings_Params
{
};

// Function Widget_Options.Widget_Options_C.ApplyAudioSettings
struct UWidget_Options_C_ApplyAudioSettings_Params
{
};

// Function Widget_Options.Widget_Options_C.ApplyGameplaySettings
struct UWidget_Options_C_ApplyGameplaySettings_Params
{
};

// Function Widget_Options.Widget_Options_C.ApplyAudioSliders
struct UWidget_Options_C_ApplyAudioSliders_Params
{
};

// Function Widget_Options.Widget_Options_C.CacheAudioSliders
struct UWidget_Options_C_CacheAudioSliders_Params
{
};

// Function Widget_Options.Widget_Options_C.UpdateAudioSettings
struct UWidget_Options_C_UpdateAudioSettings_Params
{
};

// Function Widget_Options.Widget_Options_C.BindEventsForVolumeSliders
struct UWidget_Options_C_BindEventsForVolumeSliders_Params
{
};

// Function Widget_Options.Widget_Options_C.ClampedNextIndex
struct UWidget_Options_C_ClampedNextIndex_Params
{
	int                                                currentIndex;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	TArray<struct FText>                               settingsArray;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
	int                                                nextIndex;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.BindEventsToAllButtonsForVideoSettings
struct UWidget_Options_C_BindEventsToAllButtonsForVideoSettings_Params
{
};

// Function Widget_Options.Widget_Options_C.UpdateVideoSettings
struct UWidget_Options_C_UpdateVideoSettings_Params
{
};

// Function Widget_Options.Widget_Options_C.PopulateLanguageBox
struct UWidget_Options_C_PopulateLanguageBox_Params
{
};

// Function Widget_Options.Widget_Options_C.PopulateResolutionBox
struct UWidget_Options_C_PopulateResolutionBox_Params
{
};

// Function Widget_Options.Widget_Options_C.PostProcessingNext
struct UWidget_Options_C_PostProcessingNext_Params
{
};

// Function Widget_Options.Widget_Options_C.PostProcessingPrevious
struct UWidget_Options_C_PostProcessingPrevious_Params
{
};

// Function Widget_Options.Widget_Options_C.ShadowQualityNext
struct UWidget_Options_C_ShadowQualityNext_Params
{
};

// Function Widget_Options.Widget_Options_C.ShadowQualityPrevious
struct UWidget_Options_C_ShadowQualityPrevious_Params
{
};

// Function Widget_Options.Widget_Options_C.FoliagePrevious
struct UWidget_Options_C_FoliagePrevious_Params
{
};

// Function Widget_Options.Widget_Options_C.FoliageNext
struct UWidget_Options_C_FoliageNext_Params
{
};

// Function Widget_Options.Widget_Options_C.TextureQualityNext
struct UWidget_Options_C_TextureQualityNext_Params
{
};

// Function Widget_Options.Widget_Options_C.TextureQualityPrevious
struct UWidget_Options_C_TextureQualityPrevious_Params
{
};

// Function Widget_Options.Widget_Options_C.ViewDistanceNext
struct UWidget_Options_C_ViewDistanceNext_Params
{
};

// Function Widget_Options.Widget_Options_C.ViewDistancePrevious
struct UWidget_Options_C_ViewDistancePrevious_Params
{
};

// Function Widget_Options.Widget_Options_C.VFXQualityNext
struct UWidget_Options_C_VFXQualityNext_Params
{
};

// Function Widget_Options.Widget_Options_C.VFXQualityPrevious
struct UWidget_Options_C_VFXQualityPrevious_Params
{
};

// Function Widget_Options.Widget_Options_C.OnVSyncChecked
struct UWidget_Options_C_OnVSyncChecked_Params
{
	bool                                               bIsChecked;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.OnFullScreenChecked
struct UWidget_Options_C_OnFullScreenChecked_Params
{
	bool                                               bIsChecked;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.ResetVideoSettings
struct UWidget_Options_C_ResetVideoSettings_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.OnEscape
struct UWidget_Options_C_OnEscape_Params
{
};

// Function Widget_Options.Widget_Options_C.SaveChanges
struct UWidget_Options_C_SaveChanges_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.DoVolumeThings
struct UWidget_Options_C_DoVolumeThings_Params
{
	float                                              VolumeThingsValue;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.OnFOVChanged
struct UWidget_Options_C_OnFOVChanged_Params
{
	float                                              NewFOV;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.ShowConfirmResetPopup
struct UWidget_Options_C_ShowConfirmResetPopup_Params
{
};

// Function Widget_Options.Widget_Options_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_Options_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Options.Widget_Options_C.BndEvt__Widget_FrontEnd_Button_C_0_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature
struct UWidget_Options_C_BndEvt__Widget_FrontEnd_Button_C_0_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Options.Widget_Options_C.ShowConfirmChangesPopup
struct UWidget_Options_C_ShowConfirmChangesPopup_Params
{
};

// Function Widget_Options.Widget_Options_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_Options_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_Options.Widget_Options_C.Init
struct UWidget_Options_C_Init_Params
{
};

// Function Widget_Options.Widget_Options_C.OnMotionBlurChecked
struct UWidget_Options_C_OnMotionBlurChecked_Params
{
	bool                                               Checked;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.AntiAliasNext
struct UWidget_Options_C_AntiAliasNext_Params
{
};

// Function Widget_Options.Widget_Options_C.AntiAliasPrevious
struct UWidget_Options_C_AntiAliasPrevious_Params
{
};

// Function Widget_Options.Widget_Options_C.BndEvt__mSwitcher_K2Node_ComponentBoundEvent_4_OnActiveWidgetSet__DelegateSignature
struct UWidget_Options_C_BndEvt__mSwitcher_K2Node_ComponentBoundEvent_4_OnActiveWidgetSet__DelegateSignature_Params
{
	class UWidget*                                     oldWidget;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget*                                     newWidget;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.NetworkQualityPrevious
struct UWidget_Options_C_NetworkQualityPrevious_Params
{
};

// Function Widget_Options.Widget_Options_C.NetworkQualityNext
struct UWidget_Options_C_NetworkQualityNext_Params
{
};

// Function Widget_Options.Widget_Options_C.SaveSettings
struct UWidget_Options_C_SaveSettings_Params
{
};

// Function Widget_Options.Widget_Options_C.OnMenuExit
struct UWidget_Options_C_OnMenuExit_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool*                                              noAnimation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.CheckResolutionChanges
struct UWidget_Options_C_CheckResolutionChanges_Params
{
};

// Function Widget_Options.Widget_Options_C.ResolutionChangedAccepted
struct UWidget_Options_C_ResolutionChangedAccepted_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.OpenRequireRestartIfRequired
struct UWidget_Options_C_OpenRequireRestartIfRequired_Params
{
};

// Function Widget_Options.Widget_Options_C.Construct
struct UWidget_Options_C_Construct_Params
{
};

// Function Widget_Options.Widget_Options_C.ExecuteUbergraph_Widget_Options
struct UWidget_Options_C_ExecuteUbergraph_Widget_Options_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options.Widget_Options_C.OnBackClicked__DelegateSignature
struct UWidget_Options_C_OnBackClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
