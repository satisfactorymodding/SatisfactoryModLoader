// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MenuHUD_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MenuHUD.BP_MenuHUD_C.UserConstructionScript
// ()

void ABP_MenuHUD_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuHUD.BP_MenuHUD_C.UserConstructionScript");

	ABP_MenuHUD_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuHUD.BP_MenuHUD_C.ReceiveBeginPlay
// ()

void ABP_MenuHUD_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuHUD.BP_MenuHUD_C.ReceiveBeginPlay");

	ABP_MenuHUD_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MenuHUD.BP_MenuHUD_C.ExecuteUbergraph_BP_MenuHUD
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_MenuHUD_C::ExecuteUbergraph_BP_MenuHUD(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MenuHUD.BP_MenuHUD_C.ExecuteUbergraph_BP_MenuHUD");

	ABP_MenuHUD_C_ExecuteUbergraph_BP_MenuHUD_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
