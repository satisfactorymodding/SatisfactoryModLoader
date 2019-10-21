// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BPHUDHelpers_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BPHUDHelpers.BPHUDHelpers_C.ShowHideHUD
// ()
// Parameters:
// bool                           isMenuOpen                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn*                   OwningPawn                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController*             Controller                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBPHUDHelpers_C::ShowHideHUD(bool isMenuOpen, class APawn* OwningPawn, class AController* Controller, class UObject* __WorldContext)
{
	static auto fn = UObject::FindObject<UFunction>("Function BPHUDHelpers.BPHUDHelpers_C.ShowHideHUD");

	UBPHUDHelpers_C_ShowHideHUD_Params params;
	params.isMenuOpen = isMenuOpen;
	params.OwningPawn = OwningPawn;
	params.Controller = Controller;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BPHUDHelpers.BPHUDHelpers_C.PopStackWidget
// ()
// Parameters:
// class AController*             instigatingController          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UFGInteractWidget*       Stack_Widget                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBPHUDHelpers_C::PopStackWidget(class AController* instigatingController, class UFGInteractWidget* Stack_Widget, class UObject* __WorldContext)
{
	static auto fn = UObject::FindObject<UFunction>("Function BPHUDHelpers.BPHUDHelpers_C.PopStackWidget");

	UBPHUDHelpers_C_PopStackWidget_Params params;
	params.instigatingController = instigatingController;
	params.Stack_Widget = Stack_Widget;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BPHUDHelpers.BPHUDHelpers_C.PushStackWidget
// ()
// Parameters:
// class AController*             instigatingController          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UFGInteractWidget*       stackWidget                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBPHUDHelpers_C::PushStackWidget(class AController* instigatingController, class UFGInteractWidget* stackWidget, class UObject* __WorldContext)
{
	static auto fn = UObject::FindObject<UFunction>("Function BPHUDHelpers.BPHUDHelpers_C.PushStackWidget");

	UBPHUDHelpers_C_PushStackWidget_Params params;
	params.instigatingController = instigatingController;
	params.stackWidget = stackWidget;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BPHUDHelpers.BPHUDHelpers_C.GetBPHUD
// ()
// Parameters:
// class AController*             Controller                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 __WorldContext                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class ABP_HUD_C*               outHUD                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBPHUDHelpers_C::GetBPHUD(class AController* Controller, class UObject* __WorldContext, class ABP_HUD_C** outHUD)
{
	static auto fn = UObject::FindObject<UFunction>("Function BPHUDHelpers.BPHUDHelpers_C.GetBPHUD");

	UBPHUDHelpers_C_GetBPHUD_Params params;
	params.Controller = Controller;
	params.__WorldContext = __WorldContext;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (outHUD != nullptr)
		*outHUD = params.outHUD;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
