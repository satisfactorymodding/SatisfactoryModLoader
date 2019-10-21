// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SlidingTabs_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetActiveButton
// ()

void UWidget_SlidingTabs_C::SetActiveButton()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetActiveButton");

	UWidget_SlidingTabs_C_SetActiveButton_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetupIndexOffset
// ()

void UWidget_SlidingTabs_C::SetupIndexOffset()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetupIndexOffset");

	UWidget_SlidingTabs_C_SetupIndexOffset_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetActiveIndex
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           Animate                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SlidingTabs_C::SetActiveIndex(int Index, bool Animate)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs.Widget_SlidingTabs_C.SetActiveIndex");

	UWidget_SlidingTabs_C_SetActiveIndex_Params params;
	params.Index = Index;
	params.Animate = Animate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs.Widget_SlidingTabs_C.Construct
// ()

void UWidget_SlidingTabs_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs.Widget_SlidingTabs_C.Construct");

	UWidget_SlidingTabs_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs.Widget_SlidingTabs_C.SlideLerp
// ()

void UWidget_SlidingTabs_C::SlideLerp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs.Widget_SlidingTabs_C.SlideLerp");

	UWidget_SlidingTabs_C_SlideLerp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs.Widget_SlidingTabs_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SlidingTabs_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs.Widget_SlidingTabs_C.PreConstruct");

	UWidget_SlidingTabs_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs.Widget_SlidingTabs_C.ExecuteUbergraph_Widget_SlidingTabs
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SlidingTabs_C::ExecuteUbergraph_Widget_SlidingTabs(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs.Widget_SlidingTabs_C.ExecuteUbergraph_Widget_SlidingTabs");

	UWidget_SlidingTabs_C_ExecuteUbergraph_Widget_SlidingTabs_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
