// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_RadarTower_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.GetScannedPercentText
// ()
// Parameters:
// struct FText                   Result                         (Parm, OutParm)

void UWidget_ActorDetails_RadarTower_C::GetScannedPercentText(struct FText* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.GetScannedPercentText");

	UWidget_ActorDetails_RadarTower_C_GetScannedPercentText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.GetTimeLeftInText
// ()
// Parameters:
// struct FText                   Result                         (Parm, OutParm)

void UWidget_ActorDetails_RadarTower_C::GetTimeLeftInText(struct FText* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.GetTimeLeftInText");

	UWidget_ActorDetails_RadarTower_C_GetTimeLeftInText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.Construct
// ()

void UWidget_ActorDetails_RadarTower_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.Construct");

	UWidget_ActorDetails_RadarTower_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.UpdateDetails
// ()

void UWidget_ActorDetails_RadarTower_C::UpdateDetails()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.UpdateDetails");

	UWidget_ActorDetails_RadarTower_C_UpdateDetails_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.Destruct
// ()

void UWidget_ActorDetails_RadarTower_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.Destruct");

	UWidget_ActorDetails_RadarTower_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.ExecuteUbergraph_Widget_ActorDetails_RadarTower
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActorDetails_RadarTower_C::ExecuteUbergraph_Widget_ActorDetails_RadarTower(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_RadarTower.Widget_ActorDetails_RadarTower_C.ExecuteUbergraph_Widget_ActorDetails_RadarTower");

	UWidget_ActorDetails_RadarTower_C_ExecuteUbergraph_Widget_ActorDetails_RadarTower_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
