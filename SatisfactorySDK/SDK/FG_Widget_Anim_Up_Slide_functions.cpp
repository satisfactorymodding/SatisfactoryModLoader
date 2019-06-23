// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Anim_Up_Slide_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Anim_Up_Slide.Widget_Anim_Up_Slide_C.Construct
// ()

void UWidget_Anim_Up_Slide_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Anim_Up_Slide.Widget_Anim_Up_Slide_C.Construct");

	UWidget_Anim_Up_Slide_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Anim_Up_Slide.Widget_Anim_Up_Slide_C.CloseAnim
// ()

void UWidget_Anim_Up_Slide_C::CloseAnim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Anim_Up_Slide.Widget_Anim_Up_Slide_C.CloseAnim");

	UWidget_Anim_Up_Slide_C_CloseAnim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Anim_Up_Slide.Widget_Anim_Up_Slide_C.Destruct
// ()

void UWidget_Anim_Up_Slide_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Anim_Up_Slide.Widget_Anim_Up_Slide_C.Destruct");

	UWidget_Anim_Up_Slide_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Anim_Up_Slide.Widget_Anim_Up_Slide_C.ExecuteUbergraph_Widget_Anim_Up_Slide
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Anim_Up_Slide_C::ExecuteUbergraph_Widget_Anim_Up_Slide(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Anim_Up_Slide.Widget_Anim_Up_Slide_C.ExecuteUbergraph_Widget_Anim_Up_Slide");

	UWidget_Anim_Up_Slide_C_ExecuteUbergraph_Widget_Anim_Up_Slide_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
