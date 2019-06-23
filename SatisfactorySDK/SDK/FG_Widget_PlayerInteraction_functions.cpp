// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerInteraction_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.GetInteractionText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_PlayerInteraction_C::GetInteractionText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.GetInteractionText");

	UWidget_PlayerInteraction_C_GetInteractionText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.Construct
// ()

void UWidget_PlayerInteraction_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.Construct");

	UWidget_PlayerInteraction_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerInteraction_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.Tick");

	UWidget_PlayerInteraction_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.ExecuteUbergraph_Widget_PlayerInteraction
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PlayerInteraction_C::ExecuteUbergraph_Widget_PlayerInteraction(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PlayerInteraction.Widget_PlayerInteraction_C.ExecuteUbergraph_Widget_PlayerInteraction");

	UWidget_PlayerInteraction_C_ExecuteUbergraph_Widget_PlayerInteraction_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
