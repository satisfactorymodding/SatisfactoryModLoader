// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RewardProduct_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RewardProduct.Widget_RewardProduct_C.IsValidRewardItem
// ()
// Parameters:
// bool                           IsValid                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardProduct_C::IsValidRewardItem(bool* IsValid)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardProduct.Widget_RewardProduct_C.IsValidRewardItem");

	UWidget_RewardProduct_C_IsValidRewardItem_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsValid != nullptr)
		*IsValid = params.IsValid;
}


// Function Widget_RewardProduct.Widget_RewardProduct_C.GetName
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_RewardProduct_C::GetName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardProduct.Widget_RewardProduct_C.GetName");

	UWidget_RewardProduct_C_GetName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RewardProduct.Widget_RewardProduct_C.GetIcon
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_RewardProduct_C::GetIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardProduct.Widget_RewardProduct_C.GetIcon");

	UWidget_RewardProduct_C_GetIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RewardProduct.Widget_RewardProduct_C.OnRewardClicked
// ()

void UWidget_RewardProduct_C::OnRewardClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardProduct.Widget_RewardProduct_C.OnRewardClicked");

	UWidget_RewardProduct_C_OnRewardClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardProduct.Widget_RewardProduct_C.Construct
// ()

void UWidget_RewardProduct_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardProduct.Widget_RewardProduct_C.Construct");

	UWidget_RewardProduct_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardProduct.Widget_RewardProduct_C.ExecuteUbergraph_Widget_RewardProduct
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardProduct_C::ExecuteUbergraph_Widget_RewardProduct(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardProduct.Widget_RewardProduct_C.ExecuteUbergraph_Widget_RewardProduct");

	UWidget_RewardProduct_C_ExecuteUbergraph_Widget_RewardProduct_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
