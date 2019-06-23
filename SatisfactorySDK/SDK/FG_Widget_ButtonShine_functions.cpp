// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ButtonShine_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ButtonShine.Widget_ButtonShine_C.Construct
// ()

void UWidget_ButtonShine_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonShine.Widget_ButtonShine_C.Construct");

	UWidget_ButtonShine_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonShine.Widget_ButtonShine_C.HoverCheck
// ()

void UWidget_ButtonShine_C::HoverCheck()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonShine.Widget_ButtonShine_C.HoverCheck");

	UWidget_ButtonShine_C_HoverCheck_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonShine.Widget_ButtonShine_C.Destruct
// ()

void UWidget_ButtonShine_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonShine.Widget_ButtonShine_C.Destruct");

	UWidget_ButtonShine_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonShine.Widget_ButtonShine_C.PlayShineAnim
// ()

void UWidget_ButtonShine_C::PlayShineAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonShine.Widget_ButtonShine_C.PlayShineAnim");

	UWidget_ButtonShine_C_PlayShineAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonShine.Widget_ButtonShine_C.ExecuteUbergraph_Widget_ButtonShine
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ButtonShine_C::ExecuteUbergraph_Widget_ButtonShine(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonShine.Widget_ButtonShine_C.ExecuteUbergraph_Widget_ButtonShine");

	UWidget_ButtonShine_C_ExecuteUbergraph_Widget_ButtonShine_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
