// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RewardInventoryItems_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RewardInventoryItems.Widget_RewardInventoryItems_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardInventoryItems_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardInventoryItems.Widget_RewardInventoryItems_C.PreConstruct");

	UWidget_RewardInventoryItems_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RewardInventoryItems.Widget_RewardInventoryItems_C.ExecuteUbergraph_Widget_RewardInventoryItems
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RewardInventoryItems_C::ExecuteUbergraph_Widget_RewardInventoryItems(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RewardInventoryItems.Widget_RewardInventoryItems_C.ExecuteUbergraph_Widget_RewardInventoryItems");

	UWidget_RewardInventoryItems_C_ExecuteUbergraph_Widget_RewardInventoryItems_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
