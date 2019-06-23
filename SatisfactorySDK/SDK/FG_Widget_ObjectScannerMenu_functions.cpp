// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ObjectScannerMenu_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.GetScannableIcon
// ()
// Parameters:
// struct FScannableDetails       ScannableDetails               (BlueprintVisible, BlueprintReadOnly, Parm)
// class UTexture*                Texture                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ObjectScannerMenu_C::GetScannableIcon(const struct FScannableDetails& ScannableDetails, class UTexture** Texture)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.GetScannableIcon");

	UWidget_ObjectScannerMenu_C_GetScannableIcon_Params params;
	params.ScannableDetails = ScannableDetails;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Texture != nullptr)
		*Texture = params.Texture;
}


// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Get_RingHighlighter_Visibility_1
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ObjectScannerMenu_C::Get_RingHighlighter_Visibility_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Get_RingHighlighter_Visibility_1");

	UWidget_ObjectScannerMenu_C_Get_RingHighlighter_Visibility_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.GetPositionInCircle
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               Translation                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ObjectScannerMenu_C::GetPositionInCircle(int Index, struct FVector2D* Translation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.GetPositionInCircle");

	UWidget_ObjectScannerMenu_C_GetPositionInCircle_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Translation != nullptr)
		*Translation = params.Translation;
}


// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.OnAnimationFinished
// ()
// Parameters:
// class UWidgetAnimation**       Animation                      (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ObjectScannerMenu_C::OnAnimationFinished(class UWidgetAnimation** Animation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.OnAnimationFinished");

	UWidget_ObjectScannerMenu_C_OnAnimationFinished_Params params;
	params.Animation = Animation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.OnItemSelected
// ()
// Parameters:
// class UClass*                  scannedActorClass              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ObjectScannerMenu_C::OnItemSelected(class UClass* scannedActorClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.OnItemSelected");

	UWidget_ObjectScannerMenu_C_OnItemSelected_Params params;
	params.scannedActorClass = scannedActorClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Destruct
// ()

void UWidget_ObjectScannerMenu_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Destruct");

	UWidget_ObjectScannerMenu_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Construct
// ()

void UWidget_ObjectScannerMenu_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Construct");

	UWidget_ObjectScannerMenu_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ObjectScannerMenu_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Tick");

	UWidget_ObjectScannerMenu_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.ExecuteUbergraph_Widget_ObjectScannerMenu
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ObjectScannerMenu_C::ExecuteUbergraph_Widget_ObjectScannerMenu(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.ExecuteUbergraph_Widget_ObjectScannerMenu");

	UWidget_ObjectScannerMenu_C_ExecuteUbergraph_Widget_ObjectScannerMenu_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
