#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MenuBase_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_MenuBase.BP_MenuBase_C.GatherBackgrounds
struct UBP_MenuBase_C_GatherBackgrounds_Params
{
};

// Function BP_MenuBase.BP_MenuBase_C.PlayBackgroundEnterAnimation
struct UBP_MenuBase_C_PlayBackgroundEnterAnimation_Params
{
};

// Function BP_MenuBase.BP_MenuBase_C.PlayEnterAnimation
struct UBP_MenuBase_C_PlayEnterAnimation_Params
{
	class UWidget*                                     prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_MenuBase.BP_MenuBase_C.ShouldAnimateBackground
struct UBP_MenuBase_C_ShouldAnimateBackground_Params
{
	class UWidget*                                     prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               Animate;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MenuBase.BP_MenuBase_C.RestoreFocusOnPopupClosed
struct UBP_MenuBase_C_RestoreFocusOnPopupClosed_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MenuBase.BP_MenuBase_C.OnKeyDown
struct UBP_MenuBase_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_MenuBase.BP_MenuBase_C.OnEscape
struct UBP_MenuBase_C_OnEscape_Params
{
};

// Function BP_MenuBase.BP_MenuBase_C.MenuExit
struct UBP_MenuBase_C_MenuExit_Params
{
};

// Function BP_MenuBase.BP_MenuBase_C.MenuEnter
struct UBP_MenuBase_C_MenuEnter_Params
{
	class UBP_MenuBase_C*                              inOwner;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_MenuBase.BP_MenuBase_C.Destruct
struct UBP_MenuBase_C_Destruct_Params
{
};

// Function BP_MenuBase.BP_MenuBase_C.Construct
struct UBP_MenuBase_C_Construct_Params
{
};

// Function BP_MenuBase.BP_MenuBase_C.SpawnAnim
struct UBP_MenuBase_C_SpawnAnim_Params
{
	bool                                               PlayBackgroundAnim;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MenuBase.BP_MenuBase_C.OnMenuEnter
struct UBP_MenuBase_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_MenuBase.BP_MenuBase_C.OnAnimationFinished
struct UBP_MenuBase_C_OnAnimationFinished_Params
{
	class UWidgetAnimation**                           Animation;                                                // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_MenuBase.BP_MenuBase_C.OnMenuExit
struct UBP_MenuBase_C_OnMenuExit_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool*                                              noAnimation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_MenuBase.BP_MenuBase_C.ExecuteUbergraph_BP_MenuBase
struct UBP_MenuBase_C_ExecuteUbergraph_BP_MenuBase_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
