// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ObjectScannerDescription_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ObjectScannerDescription.Widget_ObjectScannerDescription_C.Get_mDescription_Text_1
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ObjectScannerDescription_C::Get_mDescription_Text_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerDescription.Widget_ObjectScannerDescription_C.Get_mDescription_Text_1");

	UWidget_ObjectScannerDescription_C_Get_mDescription_Text_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ObjectScannerDescription.Widget_ObjectScannerDescription_C.Construct
// ()

void UWidget_ObjectScannerDescription_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerDescription.Widget_ObjectScannerDescription_C.Construct");

	UWidget_ObjectScannerDescription_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ObjectScannerDescription.Widget_ObjectScannerDescription_C.ExecuteUbergraph_Widget_ObjectScannerDescription
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ObjectScannerDescription_C::ExecuteUbergraph_Widget_ObjectScannerDescription(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ObjectScannerDescription.Widget_ObjectScannerDescription_C.ExecuteUbergraph_Widget_ObjectScannerDescription");

	UWidget_ObjectScannerDescription_C_ExecuteUbergraph_Widget_ObjectScannerDescription_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
