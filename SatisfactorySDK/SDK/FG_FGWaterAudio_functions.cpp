// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_FGWaterAudio_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function FGWaterAudio.FGWaterAudio_C.OnCameraExitedWater
// ()
// Parameters:
// class AFGWaterVolume**         waterVolume                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                exitLocation                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AFGPlayerController**    PC                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UFGWaterAudio_C::OnCameraExitedWater(class AFGWaterVolume** waterVolume, struct FVector* exitLocation, class AFGPlayerController** PC)
{
	static auto fn = UObject::FindObject<UFunction>("Function FGWaterAudio.FGWaterAudio_C.OnCameraExitedWater");

	UFGWaterAudio_C_OnCameraExitedWater_Params params;
	params.waterVolume = waterVolume;
	params.exitLocation = exitLocation;
	params.PC = PC;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function FGWaterAudio.FGWaterAudio_C.OnCameraEnteredWater
// ()
// Parameters:
// class AFGWaterVolume**         waterVolume                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                enterLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AFGPlayerController**    PC                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UFGWaterAudio_C::OnCameraEnteredWater(class AFGWaterVolume** waterVolume, struct FVector* enterLocation, class AFGPlayerController** PC)
{
	static auto fn = UObject::FindObject<UFunction>("Function FGWaterAudio.FGWaterAudio_C.OnCameraEnteredWater");

	UFGWaterAudio_C_OnCameraEnteredWater_Params params;
	params.waterVolume = waterVolume;
	params.enterLocation = enterLocation;
	params.PC = PC;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
