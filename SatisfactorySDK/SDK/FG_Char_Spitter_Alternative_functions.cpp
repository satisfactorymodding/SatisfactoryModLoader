// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Spitter_Alternative_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_Spitter_Alternative.Char_Spitter_Alternative_C.UserConstructionScript
// ()

void AChar_Spitter_Alternative_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter_Alternative.Char_Spitter_Alternative_C.UserConstructionScript");

	AChar_Spitter_Alternative_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter_Alternative.Char_Spitter_Alternative_C.OnStrafeEnded_0__DelegateSignature
// ()

void AChar_Spitter_Alternative_C::OnStrafeEnded_0__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter_Alternative.Char_Spitter_Alternative_C.OnStrafeEnded_0__DelegateSignature");

	AChar_Spitter_Alternative_C_OnStrafeEnded_0__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
