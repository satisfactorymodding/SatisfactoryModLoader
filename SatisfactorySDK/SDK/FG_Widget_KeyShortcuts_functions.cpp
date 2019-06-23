// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_KeyShortcuts_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.UpdateShortcutText
// ()

void UWidget_KeyShortcuts_C::UpdateShortcutText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.UpdateShortcutText");

	UWidget_KeyShortcuts_C_UpdateShortcutText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.GetKeyForAction
// ()
// Parameters:
// struct FName                   ActionName                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   keyText                        (Parm, OutParm)

void UWidget_KeyShortcuts_C::GetKeyForAction(const struct FName& ActionName, struct FText* keyText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.GetKeyForAction");

	UWidget_KeyShortcuts_C_GetKeyForAction_Params params;
	params.ActionName = ActionName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (keyText != nullptr)
		*keyText = params.keyText;
}


// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.Construct
// ()

void UWidget_KeyShortcuts_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.Construct");

	UWidget_KeyShortcuts_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.UpdateShortcutAvilability
// ()
// Parameters:
// class UClass*                  Unused                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_KeyShortcuts_C::UpdateShortcutAvilability(class UClass* Unused)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.UpdateShortcutAvilability");

	UWidget_KeyShortcuts_C_UpdateShortcutAvilability_Params params;
	params.Unused = Unused;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.ExecuteUbergraph_Widget_KeyShortcuts
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_KeyShortcuts_C::ExecuteUbergraph_Widget_KeyShortcuts(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.ExecuteUbergraph_Widget_KeyShortcuts");

	UWidget_KeyShortcuts_C_ExecuteUbergraph_Widget_KeyShortcuts_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
