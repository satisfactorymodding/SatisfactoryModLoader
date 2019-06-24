// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ObjectScannerMenuItem_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.GetButtonFeedback
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ObjectScannerMenuItem_C::GetButtonFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.GetButtonFeedback");

	UWidget_ObjectScannerMenuItem_C_GetButtonFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.GetTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_ObjectScannerMenuItem_C::GetTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.GetTextColor");

	UWidget_ObjectScannerMenuItem_C_GetTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.OnItemSelected__DelegateSignature
// ()
// Parameters:
// class UClass*                  scannedActorClass              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ObjectScannerMenuItem_C::OnItemSelected__DelegateSignature(class UClass* scannedActorClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.OnItemSelected__DelegateSignature");

	UWidget_ObjectScannerMenuItem_C_OnItemSelected__DelegateSignature_Params params;
	params.scannedActorClass = scannedActorClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
