// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_Consumable_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.Construct
// ()

void UWidget_HUDBox_Consumable_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.Construct");

	UWidget_HUDBox_Consumable_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Consumable_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.Tick");

	UWidget_HUDBox_Consumable_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.ExecuteUbergraph_Widget_HUDBox_Consumable
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Consumable_C::ExecuteUbergraph_Widget_HUDBox_Consumable(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Consumable.Widget_HUDBox_Consumable_C.ExecuteUbergraph_Widget_HUDBox_Consumable");

	UWidget_HUDBox_Consumable_C_ExecuteUbergraph_Widget_HUDBox_Consumable_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
