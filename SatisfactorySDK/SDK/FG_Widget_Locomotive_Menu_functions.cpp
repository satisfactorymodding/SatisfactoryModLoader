// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Locomotive_Menu_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.UpdatePowerStatus
// ()

void UWidget_Locomotive_Menu_C::UpdatePowerStatus()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.UpdatePowerStatus");

	UWidget_Locomotive_Menu_C_UpdatePowerStatus_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.GetLocomotiveSpeed
// ()
// Parameters:
// class AFGLocomotive*           Locomotive                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Locomotive_Menu_C::GetLocomotiveSpeed(class AFGLocomotive* Locomotive)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.GetLocomotiveSpeed");

	UWidget_Locomotive_Menu_C_GetLocomotiveSpeed_Params params;
	params.Locomotive = Locomotive;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.GetPowerConsumption
// ()
// Parameters:
// class AFGLocomotive*           Locomotive                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Locomotive_Menu_C::GetPowerConsumption(class AFGLocomotive* Locomotive)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.GetPowerConsumption");

	UWidget_Locomotive_Menu_C_GetPowerConsumption_Params params;
	params.Locomotive = Locomotive;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Construct
// ()

void UWidget_Locomotive_Menu_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Construct");

	UWidget_Locomotive_Menu_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Init
// ()

void UWidget_Locomotive_Menu_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Init");

	UWidget_Locomotive_Menu_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Destruct
// ()

void UWidget_Locomotive_Menu_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Destruct");

	UWidget_Locomotive_Menu_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.UpdateLocomotiveStats
// ()

void UWidget_Locomotive_Menu_C::UpdateLocomotiveStats()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.UpdateLocomotiveStats");

	UWidget_Locomotive_Menu_C_UpdateLocomotiveStats_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnEscapePressed
// ()

void UWidget_Locomotive_Menu_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnEscapePressed");

	UWidget_Locomotive_Menu_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnNameChanged
// ()
// Parameters:
// struct FText                   mName                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Locomotive_Menu_C::OnNameChanged(const struct FText& mName)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnNameChanged");

	UWidget_Locomotive_Menu_C_OnNameChanged_Params params;
	params.mName = mName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.ExecuteUbergraph_Widget_Locomotive_Menu
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Locomotive_Menu_C::ExecuteUbergraph_Widget_Locomotive_Menu(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.ExecuteUbergraph_Widget_Locomotive_Menu");

	UWidget_Locomotive_Menu_C_ExecuteUbergraph_Widget_Locomotive_Menu_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnTrainNameChanged__DelegateSignature
// ()

void UWidget_Locomotive_Menu_C::OnTrainNameChanged__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnTrainNameChanged__DelegateSignature");

	UWidget_Locomotive_Menu_C_OnTrainNameChanged__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnClose__DelegateSignature
// ()

void UWidget_Locomotive_Menu_C::OnClose__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnClose__DelegateSignature");

	UWidget_Locomotive_Menu_C_OnClose__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
