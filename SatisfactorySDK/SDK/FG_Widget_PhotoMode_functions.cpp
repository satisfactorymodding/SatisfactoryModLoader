// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PhotoMode_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PhotoMode.Widget_PhotoMode_C.ToggleVisibility
// ()

void UWidget_PhotoMode_C::ToggleVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PhotoMode.Widget_PhotoMode_C.ToggleVisibility");

	UWidget_PhotoMode_C_ToggleVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PhotoMode.Widget_PhotoMode_C.FadePhotoTakenText
// ()
// Parameters:
// float                          DeltaTime                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PhotoMode_C::FadePhotoTakenText(float DeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PhotoMode.Widget_PhotoMode_C.FadePhotoTakenText");

	UWidget_PhotoMode_C_FadePhotoTakenText_Params params;
	params.DeltaTime = DeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PhotoMode.Widget_PhotoMode_C.PhotoTaken
// ()

void UWidget_PhotoMode_C::PhotoTaken()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PhotoMode.Widget_PhotoMode_C.PhotoTaken");

	UWidget_PhotoMode_C_PhotoTaken_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PhotoMode.Widget_PhotoMode_C.UpdateHiResMode
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_PhotoMode_C::UpdateHiResMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PhotoMode.Widget_PhotoMode_C.UpdateHiResMode");

	UWidget_PhotoMode_C_UpdateHiResMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PhotoMode.Widget_PhotoMode_C.UpdateFOV
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_PhotoMode_C::UpdateFOV()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PhotoMode.Widget_PhotoMode_C.UpdateFOV");

	UWidget_PhotoMode_C_UpdateFOV_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PhotoMode.Widget_PhotoMode_C.Construct
// ()

void UWidget_PhotoMode_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PhotoMode.Widget_PhotoMode_C.Construct");

	UWidget_PhotoMode_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PhotoMode.Widget_PhotoMode_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PhotoMode_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PhotoMode.Widget_PhotoMode_C.Tick");

	UWidget_PhotoMode_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PhotoMode.Widget_PhotoMode_C.ExecuteUbergraph_Widget_PhotoMode
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PhotoMode_C::ExecuteUbergraph_Widget_PhotoMode(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PhotoMode.Widget_PhotoMode_C.ExecuteUbergraph_Widget_PhotoMode");

	UWidget_PhotoMode_C_ExecuteUbergraph_Widget_PhotoMode_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
