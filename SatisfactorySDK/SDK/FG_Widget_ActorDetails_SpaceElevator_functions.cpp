// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_SpaceElevator_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_SpaceElevator.Widget_ActorDetails_SpaceElevator_C.SetupInventory
// ()

void UWidget_ActorDetails_SpaceElevator_C::SetupInventory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_SpaceElevator.Widget_ActorDetails_SpaceElevator_C.SetupInventory");

	UWidget_ActorDetails_SpaceElevator_C_SetupInventory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_SpaceElevator.Widget_ActorDetails_SpaceElevator_C.Construct
// ()

void UWidget_ActorDetails_SpaceElevator_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_SpaceElevator.Widget_ActorDetails_SpaceElevator_C.Construct");

	UWidget_ActorDetails_SpaceElevator_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_SpaceElevator.Widget_ActorDetails_SpaceElevator_C.InitCostSlots
// ()

void UWidget_ActorDetails_SpaceElevator_C::InitCostSlots()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_SpaceElevator.Widget_ActorDetails_SpaceElevator_C.InitCostSlots");

	UWidget_ActorDetails_SpaceElevator_C_InitCostSlots_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_SpaceElevator.Widget_ActorDetails_SpaceElevator_C.ExecuteUbergraph_Widget_ActorDetails_SpaceElevator
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActorDetails_SpaceElevator_C::ExecuteUbergraph_Widget_ActorDetails_SpaceElevator(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_SpaceElevator.Widget_ActorDetails_SpaceElevator_C.ExecuteUbergraph_Widget_ActorDetails_SpaceElevator");

	UWidget_ActorDetails_SpaceElevator_C_ExecuteUbergraph_Widget_ActorDetails_SpaceElevator_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
