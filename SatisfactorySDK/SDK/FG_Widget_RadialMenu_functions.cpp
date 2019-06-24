// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RadialMenu_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RadialMenu.Widget_RadialMenu_C.Update Button Angles
// ()
// Parameters:
// float                          MenuAngle                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadialMenu_C::Update_Button_Angles(float MenuAngle)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.Update Button Angles");

	UWidget_RadialMenu_C_Update_Button_Angles_Params params;
	params.MenuAngle = MenuAngle;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadialMenu.Widget_RadialMenu_C.Set Angle
// ()

void UWidget_RadialMenu_C::Set_Angle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.Set Angle");

	UWidget_RadialMenu_C_Set_Angle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadialMenu.Widget_RadialMenu_C.Close Radial Menu
// ()

void UWidget_RadialMenu_C::Close_Radial_Menu()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.Close Radial Menu");

	UWidget_RadialMenu_C_Close_Radial_Menu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadialMenu.Widget_RadialMenu_C.Open Radial Menu
// ()

void UWidget_RadialMenu_C::Open_Radial_Menu()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.Open Radial Menu");

	UWidget_RadialMenu_C_Open_Radial_Menu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadialMenu.Widget_RadialMenu_C.Generate Radial Menu
// ()

void UWidget_RadialMenu_C::Generate_Radial_Menu()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.Generate Radial Menu");

	UWidget_RadialMenu_C_Generate_Radial_Menu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadialMenu.Widget_RadialMenu_C.Destruct
// ()

void UWidget_RadialMenu_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.Destruct");

	UWidget_RadialMenu_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadialMenu.Widget_RadialMenu_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadialMenu_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.Tick");

	UWidget_RadialMenu_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadialMenu.Widget_RadialMenu_C.Create Radial Menu
// ()

void UWidget_RadialMenu_C::Create_Radial_Menu()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.Create Radial Menu");

	UWidget_RadialMenu_C_Create_Radial_Menu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadialMenu.Widget_RadialMenu_C.ExecuteUbergraph_Widget_RadialMenu
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadialMenu_C::ExecuteUbergraph_Widget_RadialMenu(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadialMenu.Widget_RadialMenu_C.ExecuteUbergraph_Widget_RadialMenu");

	UWidget_RadialMenu_C_ExecuteUbergraph_Widget_RadialMenu_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
