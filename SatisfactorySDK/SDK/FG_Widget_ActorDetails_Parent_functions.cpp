// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_Parent_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_Parent.Widget_ActorDetails_Parent_C.Construct
// ()

void UWidget_ActorDetails_Parent_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Parent.Widget_ActorDetails_Parent_C.Construct");

	UWidget_ActorDetails_Parent_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_Parent.Widget_ActorDetails_Parent_C.ActorDetailsUpdate
// ()

void UWidget_ActorDetails_Parent_C::ActorDetailsUpdate()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Parent.Widget_ActorDetails_Parent_C.ActorDetailsUpdate");

	UWidget_ActorDetails_Parent_C_ActorDetailsUpdate_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_Parent.Widget_ActorDetails_Parent_C.Destruct
// ()

void UWidget_ActorDetails_Parent_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Parent.Widget_ActorDetails_Parent_C.Destruct");

	UWidget_ActorDetails_Parent_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_Parent.Widget_ActorDetails_Parent_C.ExecuteUbergraph_Widget_ActorDetails_Parent
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActorDetails_Parent_C::ExecuteUbergraph_Widget_ActorDetails_Parent(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Parent.Widget_ActorDetails_Parent_C.ExecuteUbergraph_Widget_ActorDetails_Parent");

	UWidget_ActorDetails_Parent_C_ExecuteUbergraph_Widget_ActorDetails_Parent_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
