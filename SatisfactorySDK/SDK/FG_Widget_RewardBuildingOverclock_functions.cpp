// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RewardBuildingOverclock_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.IsValidRewardItem
// ()
// Parameters:
// bool                           IsValid                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardBuildingOverclock_C::IsValidRewardItem(bool* IsValid)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.IsValidRewardItem");

	UWidget_RewardBuildingOverclock_C_IsValidRewardItem_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsValid != nullptr)
		*IsValid = params.IsValid;
}


// Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.UpdateVisibility
// ()

void UWidget_RewardBuildingOverclock_C::UpdateVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.UpdateVisibility");

	UWidget_RewardBuildingOverclock_C_UpdateVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.GetName
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_RewardBuildingOverclock_C::GetName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.GetName");

	UWidget_RewardBuildingOverclock_C_GetName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.GetIcon
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_RewardBuildingOverclock_C::GetIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.GetIcon");

	UWidget_RewardBuildingOverclock_C_GetIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardBuildingOverclock_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.PreConstruct");

	UWidget_RewardBuildingOverclock_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardBuildingOverclock_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.Tick");

	UWidget_RewardBuildingOverclock_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.OnRewardClicked
// ()

void UWidget_RewardBuildingOverclock_C::OnRewardClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.OnRewardClicked");

	UWidget_RewardBuildingOverclock_C_OnRewardClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.ExecuteUbergraph_Widget_RewardBuildingOverclock
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardBuildingOverclock_C::ExecuteUbergraph_Widget_RewardBuildingOverclock(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C.ExecuteUbergraph_Widget_RewardBuildingOverclock");

	UWidget_RewardBuildingOverclock_C_ExecuteUbergraph_Widget_RewardBuildingOverclock_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
