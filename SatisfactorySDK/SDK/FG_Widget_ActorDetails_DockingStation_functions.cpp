// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_DockingStation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_DockingStation.Widget_ActorDetails_DockingStation_C.Construct
// ()

void UWidget_ActorDetails_DockingStation_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_DockingStation.Widget_ActorDetails_DockingStation_C.Construct");

	UWidget_ActorDetails_DockingStation_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_DockingStation.Widget_ActorDetails_DockingStation_C.Destruct
// ()

void UWidget_ActorDetails_DockingStation_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_DockingStation.Widget_ActorDetails_DockingStation_C.Destruct");

	UWidget_ActorDetails_DockingStation_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_DockingStation.Widget_ActorDetails_DockingStation_C.ExecuteUbergraph_Widget_ActorDetails_DockingStation
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActorDetails_DockingStation_C::ExecuteUbergraph_Widget_ActorDetails_DockingStation(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_DockingStation.Widget_ActorDetails_DockingStation_C.ExecuteUbergraph_Widget_ActorDetails_DockingStation");

	UWidget_ActorDetails_DockingStation_C_ExecuteUbergraph_Widget_ActorDetails_DockingStation_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
