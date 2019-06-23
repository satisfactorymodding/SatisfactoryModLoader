// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Smoke_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Smoke.Widget_Smoke_C.Construct
// ()

void UWidget_Smoke_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Smoke.Widget_Smoke_C.Construct");

	UWidget_Smoke_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Smoke.Widget_Smoke_C.OnAnimEnd
// ()

void UWidget_Smoke_C::OnAnimEnd()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Smoke.Widget_Smoke_C.OnAnimEnd");

	UWidget_Smoke_C_OnAnimEnd_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Smoke.Widget_Smoke_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Smoke_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Smoke.Widget_Smoke_C.Tick");

	UWidget_Smoke_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Smoke.Widget_Smoke_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Smoke_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Smoke.Widget_Smoke_C.PreConstruct");

	UWidget_Smoke_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Smoke.Widget_Smoke_C.ExecuteUbergraph_Widget_Smoke
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Smoke_C::ExecuteUbergraph_Widget_Smoke(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Smoke.Widget_Smoke_C.ExecuteUbergraph_Widget_Smoke");

	UWidget_Smoke_C_ExecuteUbergraph_Widget_Smoke_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
