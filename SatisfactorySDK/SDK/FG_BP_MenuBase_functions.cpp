// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MenuBase_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MenuBase.BP_MenuBase_C.GatherBackgrounds
// ()

void UBP_MenuBase_C::GatherBackgrounds()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.GatherBackgrounds");

	UBP_MenuBase_C_GatherBackgrounds_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.PlayBackgroundEnterAnimation
// ()

void UBP_MenuBase_C::PlayBackgroundEnterAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.PlayBackgroundEnterAnimation");

	UBP_MenuBase_C_PlayBackgroundEnterAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.PlayEnterAnimation
// ()
// Parameters:
// class UWidget*                 prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_MenuBase_C::PlayEnterAnimation(class UWidget* prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.PlayEnterAnimation");

	UBP_MenuBase_C_PlayEnterAnimation_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.ShouldAnimateBackground
// ()
// Parameters:
// class UWidget*                 prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           Animate                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_MenuBase_C::ShouldAnimateBackground(class UWidget* prevMenu, bool* Animate)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.ShouldAnimateBackground");

	UBP_MenuBase_C_ShouldAnimateBackground_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Animate != nullptr)
		*Animate = params.Animate;
}


// Function BP_MenuBase.BP_MenuBase_C.RestoreFocusOnPopupClosed
// ()
// Parameters:
// bool                           confirm                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MenuBase_C::RestoreFocusOnPopupClosed(bool confirm)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.RestoreFocusOnPopupClosed");

	UBP_MenuBase_C_RestoreFocusOnPopupClosed_Params params;
	params.confirm = confirm;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UBP_MenuBase_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.OnKeyDown");

	UBP_MenuBase_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_MenuBase.BP_MenuBase_C.OnEscape
// ()

void UBP_MenuBase_C::OnEscape()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.OnEscape");

	UBP_MenuBase_C_OnEscape_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.MenuExit
// ()

void UBP_MenuBase_C::MenuExit()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.MenuExit");

	UBP_MenuBase_C_MenuExit_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.MenuEnter
// ()
// Parameters:
// class UBP_MenuBase_C*          inOwner                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_MenuBase_C::MenuEnter(class UBP_MenuBase_C* inOwner)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.MenuEnter");

	UBP_MenuBase_C_MenuEnter_Params params;
	params.inOwner = inOwner;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.Destruct
// ()

void UBP_MenuBase_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.Destruct");

	UBP_MenuBase_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.Construct
// ()

void UBP_MenuBase_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.Construct");

	UBP_MenuBase_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.SpawnAnim
// ()
// Parameters:
// bool                           PlayBackgroundAnim             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MenuBase_C::SpawnAnim(bool PlayBackgroundAnim)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.SpawnAnim");

	UBP_MenuBase_C_SpawnAnim_Params params;
	params.PlayBackgroundAnim = PlayBackgroundAnim;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.OnMenuEnter
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_MenuBase_C::OnMenuEnter(class UWidget** prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.OnMenuEnter");

	UBP_MenuBase_C_OnMenuEnter_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.OnAnimationFinished
// ()
// Parameters:
// class UWidgetAnimation**       Animation                      (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_MenuBase_C::OnAnimationFinished(class UWidgetAnimation** Animation)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.OnAnimationFinished");

	UBP_MenuBase_C_OnAnimationFinished_Params params;
	params.Animation = Animation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.OnMenuExit
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool*                          noAnimation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MenuBase_C::OnMenuExit(class UWidget** prevMenu, bool* noAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.OnMenuExit");

	UBP_MenuBase_C_OnMenuExit_Params params;
	params.prevMenu = prevMenu;
	params.noAnimation = noAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuBase.BP_MenuBase_C.ExecuteUbergraph_BP_MenuBase
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MenuBase_C::ExecuteUbergraph_BP_MenuBase(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuBase.BP_MenuBase_C.ExecuteUbergraph_BP_MenuBase");

	UBP_MenuBase_C_ExecuteUbergraph_BP_MenuBase_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
