// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_JetPack_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_JetPack.Widget_JetPack_C.GetFuelText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_JetPack_C::GetFuelText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_JetPack.Widget_JetPack_C.GetFuelText");

	UWidget_JetPack_C_GetFuelText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_JetPack.Widget_JetPack_C.GetJetPack
// ()
// Parameters:
// class AEquip_JetPack_C*        Jetpack                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_JetPack_C::GetJetPack(class AEquip_JetPack_C** Jetpack)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_JetPack.Widget_JetPack_C.GetJetPack");

	UWidget_JetPack_C_GetJetPack_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Jetpack != nullptr)
		*Jetpack = params.Jetpack;
}


// Function Widget_JetPack.Widget_JetPack_C.GetFuelColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_JetPack_C::GetFuelColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_JetPack.Widget_JetPack_C.GetFuelColor");

	UWidget_JetPack_C_GetFuelColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_JetPack.Widget_JetPack_C.GetFuelPct
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_JetPack_C::GetFuelPct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_JetPack.Widget_JetPack_C.GetFuelPct");

	UWidget_JetPack_C_GetFuelPct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_JetPack.Widget_JetPack_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_JetPack_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_JetPack.Widget_JetPack_C.Tick");

	UWidget_JetPack_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_JetPack.Widget_JetPack_C.ExecuteUbergraph_Widget_JetPack
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_JetPack_C::ExecuteUbergraph_Widget_JetPack(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_JetPack.Widget_JetPack_C.ExecuteUbergraph_Widget_JetPack");

	UWidget_JetPack_C_ExecuteUbergraph_Widget_JetPack_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
