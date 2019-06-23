// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Compass_new_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Compass_new.Widget_Compass_new_C.GetCompassObjectWidgetClass
// ()
// Parameters:
// class UFGActorRepresentation** actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UClass* UWidget_Compass_new_C::GetCompassObjectWidgetClass(class UFGActorRepresentation** actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Compass_new.Widget_Compass_new_C.GetCompassObjectWidgetClass");

	UWidget_Compass_new_C_GetCompassObjectWidgetClass_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Compass_new.Widget_Compass_new_C.Construct
// ()

void UWidget_Compass_new_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Compass_new.Widget_Compass_new_C.Construct");

	UWidget_Compass_new_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Compass_new.Widget_Compass_new_C.ExecuteUbergraph_Widget_Compass_new
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Compass_new_C::ExecuteUbergraph_Widget_Compass_new(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Compass_new.Widget_Compass_new_C.ExecuteUbergraph_Widget_Compass_new");

	UWidget_Compass_new_C_ExecuteUbergraph_Widget_Compass_new_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
