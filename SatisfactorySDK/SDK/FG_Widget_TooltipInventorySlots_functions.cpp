// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TooltipInventorySlots_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TooltipInventorySlots.Widget_TooltipInventorySlots_C.GetExtraInventorySlotText
// ()
// Parameters:
// struct FText                   NewParam                       (Parm, OutParm)

void UWidget_TooltipInventorySlots_C::GetExtraInventorySlotText(struct FText* NewParam)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TooltipInventorySlots.Widget_TooltipInventorySlots_C.GetExtraInventorySlotText");

	UWidget_TooltipInventorySlots_C_GetExtraInventorySlotText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NewParam != nullptr)
		*NewParam = params.NewParam;
}


// Function Widget_TooltipInventorySlots.Widget_TooltipInventorySlots_C.GetExtraArmsSlotText
// ()
// Parameters:
// struct FText                   NewParam                       (Parm, OutParm)

void UWidget_TooltipInventorySlots_C::GetExtraArmsSlotText(struct FText* NewParam)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TooltipInventorySlots.Widget_TooltipInventorySlots_C.GetExtraArmsSlotText");

	UWidget_TooltipInventorySlots_C_GetExtraArmsSlotText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NewParam != nullptr)
		*NewParam = params.NewParam;
}


// Function Widget_TooltipInventorySlots.Widget_TooltipInventorySlots_C.Construct
// ()

void UWidget_TooltipInventorySlots_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TooltipInventorySlots.Widget_TooltipInventorySlots_C.Construct");

	UWidget_TooltipInventorySlots_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TooltipInventorySlots.Widget_TooltipInventorySlots_C.ExecuteUbergraph_Widget_TooltipInventorySlots
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TooltipInventorySlots_C::ExecuteUbergraph_Widget_TooltipInventorySlots(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TooltipInventorySlots.Widget_TooltipInventorySlots_C.ExecuteUbergraph_Widget_TooltipInventorySlots");

	UWidget_TooltipInventorySlots_C_ExecuteUbergraph_Widget_TooltipInventorySlots_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
