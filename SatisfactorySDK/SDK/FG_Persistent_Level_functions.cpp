// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Persistent_Level_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Persistent_Level.Persistent_Level_C.PartyMode
// ()

void APersistent_Level_C::PartyMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function Persistent_Level.Persistent_Level_C.PartyMode");

	APersistent_Level_C_PartyMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Persistent_Level.Persistent_Level_C.TeleportPlayer
// ()

void APersistent_Level_C::TeleportPlayer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Persistent_Level.Persistent_Level_C.TeleportPlayer");

	APersistent_Level_C_TeleportPlayer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Persistent_Level.Persistent_Level_C.ExecuteUbergraph_Persistent_Level
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void APersistent_Level_C::ExecuteUbergraph_Persistent_Level(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Persistent_Level.Persistent_Level_C.ExecuteUbergraph_Persistent_Level");

	APersistent_Level_C_ExecuteUbergraph_Persistent_Level_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
