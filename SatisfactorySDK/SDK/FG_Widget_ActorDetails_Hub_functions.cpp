// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_Hub_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.FromSecondsToText
// ()
// Parameters:
// float                          Seconds                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   Result                         (Parm, OutParm)

void UWidget_ActorDetails_Hub_C::FromSecondsToText(float Seconds, struct FText* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.FromSecondsToText");

	UWidget_ActorDetails_Hub_C_FromSecondsToText_Params params;
	params.Seconds = Seconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateInfo
// ()

void UWidget_ActorDetails_Hub_C::UpdateInfo()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateInfo");

	UWidget_ActorDetails_Hub_C_UpdateInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.Construct
// ()

void UWidget_ActorDetails_Hub_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.Construct");

	UWidget_ActorDetails_Hub_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateInfoEvent
// ()

void UWidget_ActorDetails_Hub_C::UpdateInfoEvent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateInfoEvent");

	UWidget_ActorDetails_Hub_C_UpdateInfoEvent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateMAMInfo
// ()

void UWidget_ActorDetails_Hub_C::UpdateMAMInfo()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.UpdateMAMInfo");

	UWidget_ActorDetails_Hub_C_UpdateMAMInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.ExecuteUbergraph_Widget_ActorDetails_Hub
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActorDetails_Hub_C::ExecuteUbergraph_Widget_ActorDetails_Hub(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_Hub.Widget_ActorDetails_Hub_C.ExecuteUbergraph_Widget_ActorDetails_Hub");

	UWidget_ActorDetails_Hub_C_ExecuteUbergraph_Widget_ActorDetails_Hub_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
