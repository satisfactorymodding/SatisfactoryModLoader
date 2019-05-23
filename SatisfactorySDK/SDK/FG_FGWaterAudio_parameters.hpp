#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_FGWaterAudio_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function FGWaterAudio.FGWaterAudio_C.OnCameraExitedWater
struct UFGWaterAudio_C_OnCameraExitedWater_Params
{
	class AFGWaterVolume**                             waterVolume;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    exitLocation;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	class AFGPlayerController**                        PC;                                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function FGWaterAudio.FGWaterAudio_C.OnCameraEnteredWater
struct UFGWaterAudio_C_OnCameraEnteredWater_Params
{
	class AFGWaterVolume**                             waterVolume;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    enterLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	class AFGPlayerController**                        PC;                                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
