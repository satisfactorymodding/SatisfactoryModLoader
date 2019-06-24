// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_3PColorGun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_3PColorGun.Anim_3PColorGun_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_3PColorGun_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_3PColorGun.Anim_3PColorGun_C.BlueprintUpdateAnimation");

	UAnim_3PColorGun_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_3PColorGun.Anim_3PColorGun_C.ExecuteUbergraph_Anim_3PColorGun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_3PColorGun_C::ExecuteUbergraph_Anim_3PColorGun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_3PColorGun.Anim_3PColorGun_C.ExecuteUbergraph_Anim_3PColorGun");

	UAnim_3PColorGun_C_ExecuteUbergraph_Anim_3PColorGun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
