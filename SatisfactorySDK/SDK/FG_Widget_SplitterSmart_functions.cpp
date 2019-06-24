// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SplitterSmart_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SplitterSmart.Widget_SplitterSmart_C.Construct
// ()

void UWidget_SplitterSmart_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterSmart.Widget_SplitterSmart_C.Construct");

	UWidget_SplitterSmart_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterSmart.Widget_SplitterSmart_C.Destruct
// ()

void UWidget_SplitterSmart_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterSmart.Widget_SplitterSmart_C.Destruct");

	UWidget_SplitterSmart_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterSmart.Widget_SplitterSmart_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterSmart_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterSmart.Widget_SplitterSmart_C.PreConstruct");

	UWidget_SplitterSmart_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SplitterSmart.Widget_SplitterSmart_C.ExecuteUbergraph_Widget_SplitterSmart
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SplitterSmart_C::ExecuteUbergraph_Widget_SplitterSmart(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SplitterSmart.Widget_SplitterSmart_C.ExecuteUbergraph_Widget_SplitterSmart");

	UWidget_SplitterSmart_C_ExecuteUbergraph_Widget_SplitterSmart_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
