// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SchematicRewardItem_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.SetCategoryIconColor
// ()

void UWidget_SchematicRewardItem_C::SetCategoryIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.SetCategoryIconColor");

	UWidget_SchematicRewardItem_C_SetCategoryIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetLockedIcon
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SchematicRewardItem_C::GetLockedIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetLockedIcon");

	UWidget_SchematicRewardItem_C_GetLockedIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.SetCategoryTexture
// ()
// Parameters:
// class UClass*                  ItemClass                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SchematicRewardItem_C::SetCategoryTexture(class UClass* ItemClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.SetCategoryTexture");

	UWidget_SchematicRewardItem_C_SetCategoryTexture_Params params;
	params.ItemClass = ItemClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetCategoryIcon
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_SchematicRewardItem_C::GetCategoryIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetCategoryIcon");

	UWidget_SchematicRewardItem_C_GetCategoryIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetLinesColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SchematicRewardItem_C::GetLinesColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetLinesColor");

	UWidget_SchematicRewardItem_C_GetLinesColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetButtonColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SchematicRewardItem_C::GetButtonColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetButtonColor");

	UWidget_SchematicRewardItem_C_GetButtonColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetCategoryIconBackgroundColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_SchematicRewardItem_C::GetCategoryIconBackgroundColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetCategoryIconBackgroundColor");

	UWidget_SchematicRewardItem_C_GetCategoryIconBackgroundColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetHoverColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_SchematicRewardItem_C::GetHoverColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetHoverColor");

	UWidget_SchematicRewardItem_C_GetHoverColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.IsValidRewardItem
// ()
// Parameters:
// bool                           IsValid                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_SchematicRewardItem_C::IsValidRewardItem(bool* IsValid)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.IsValidRewardItem");

	UWidget_SchematicRewardItem_C_IsValidRewardItem_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsValid != nullptr)
		*IsValid = params.IsValid;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.OnRewardClicked
// ()

void UWidget_SchematicRewardItem_C::OnRewardClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.OnRewardClicked");

	UWidget_SchematicRewardItem_C_OnRewardClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetName
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_SchematicRewardItem_C::GetName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetName");

	UWidget_SchematicRewardItem_C_GetName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetIcon
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_SchematicRewardItem_C::GetIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.GetIcon");

	UWidget_SchematicRewardItem_C_GetIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SchematicRewardItem_C::BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_SchematicRewardItem_C_BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SchematicRewardItem_C::BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_SchematicRewardItem_C_BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_19_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SchematicRewardItem_C::BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_19_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_19_OnButtonHoverEvent__DelegateSignature");

	UWidget_SchematicRewardItem_C_BndEvt__mSchematicRecipeButton_K2Node_ComponentBoundEvent_19_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.Construct
// ()

void UWidget_SchematicRewardItem_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.Construct");

	UWidget_SchematicRewardItem_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.ExecuteUbergraph_Widget_SchematicRewardItem
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SchematicRewardItem_C::ExecuteUbergraph_Widget_SchematicRewardItem(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SchematicRewardItem.Widget_SchematicRewardItem_C.ExecuteUbergraph_Widget_SchematicRewardItem");

	UWidget_SchematicRewardItem_C_ExecuteUbergraph_Widget_SchematicRewardItem_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
