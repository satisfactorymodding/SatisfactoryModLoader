// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InviteNotification_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_InviteNotification.Widget_InviteNotification_C.Construct
// ()

void UWidget_InviteNotification_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InviteNotification.Widget_InviteNotification_C.Construct");

	UWidget_InviteNotification_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InviteNotification.Widget_InviteNotification_C.OnInviteReceived
// ()
// Parameters:
// struct FPendingInvite          receivedInvite                 (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_InviteNotification_C::OnInviteReceived(const struct FPendingInvite& receivedInvite)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InviteNotification.Widget_InviteNotification_C.OnInviteReceived");

	UWidget_InviteNotification_C_OnInviteReceived_Params params;
	params.receivedInvite = receivedInvite;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_InviteNotification.Widget_InviteNotification_C.ExecuteUbergraph_Widget_InviteNotification
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_InviteNotification_C::ExecuteUbergraph_Widget_InviteNotification(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_InviteNotification.Widget_InviteNotification_C.ExecuteUbergraph_Widget_InviteNotification");

	UWidget_InviteNotification_C_ExecuteUbergraph_Widget_InviteNotification_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
