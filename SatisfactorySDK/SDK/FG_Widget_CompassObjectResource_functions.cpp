// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CompassObjectResource_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.GetText_1
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CompassObjectResource_C::GetText_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.GetText_1");

	UWidget_CompassObjectResource_C_GetText_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnCompassObjectAddedToPanel
// ()
// Parameters:
// class UCanvasPanelSlot**       parentSlot                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_CompassObjectResource_C::OnCompassObjectAddedToPanel(class UCanvasPanelSlot** parentSlot)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnCompassObjectAddedToPanel");

	UWidget_CompassObjectResource_C_OnCompassObjectAddedToPanel_Params params;
	params.parentSlot = parentSlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.Construct
// ()

void UWidget_CompassObjectResource_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.Construct");

	UWidget_CompassObjectResource_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnCompassObjectUpdated
// ()

void UWidget_CompassObjectResource_C::OnCompassObjectUpdated()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnCompassObjectUpdated");

	UWidget_CompassObjectResource_C_OnCompassObjectUpdated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CompassObjectResource_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.Tick");

	UWidget_CompassObjectResource_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnObjectCentered
// ()
// Parameters:
// bool*                          centered                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CompassObjectResource_C::OnObjectCentered(bool* centered)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.OnObjectCentered");

	UWidget_CompassObjectResource_C_OnObjectCentered_Params params;
	params.centered = centered;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.ExecuteUbergraph_Widget_CompassObjectResource
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CompassObjectResource_C::ExecuteUbergraph_Widget_CompassObjectResource(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectResource.Widget_CompassObjectResource_C.ExecuteUbergraph_Widget_CompassObjectResource");

	UWidget_CompassObjectResource_C_ExecuteUbergraph_Widget_CompassObjectResource_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
