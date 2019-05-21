// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_Machinegun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Machinegun.Widget_Machinegun_C.GetAmmoAvailable
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_Machinegun_C::GetAmmoAvailable()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Machinegun.Widget_Machinegun_C.GetAmmoAvailable");

	UWidget_Machinegun_C_GetAmmoAvailable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Machinegun.Widget_Machinegun_C.GetAmmoText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_Machinegun_C::GetAmmoText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Machinegun.Widget_Machinegun_C.GetAmmoText");

	UWidget_Machinegun_C_GetAmmoText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Machinegun.Widget_Machinegun_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Machinegun_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Machinegun.Widget_Machinegun_C.Tick");

	UWidget_Machinegun_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Machinegun.Widget_Machinegun_C.ExecuteUbergraph_Widget_Machinegun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Machinegun_C::ExecuteUbergraph_Widget_Machinegun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Machinegun.Widget_Machinegun_C.ExecuteUbergraph_Widget_Machinegun");

	UWidget_Machinegun_C_ExecuteUbergraph_Widget_Machinegun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
