#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_MinerMk3_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Anim_MinerMk3.Anim_MinerMk3_C.CalculateAnimGraphVariables
struct UAnim_MinerMk3_C_CalculateAnimGraphVariables_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.ReloadTimer
struct UAnim_MinerMk3_C_ReloadTimer_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.SetupReloadTimer
struct UAnim_MinerMk3_C_SetupReloadTimer_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.BlueprintUpdateAnimation
struct UAnim_MinerMk3_C_BlueprintUpdateAnimation_Params
{
	float*                                             DeltaTimeX;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_StartDrillVFX
struct UAnim_MinerMk3_C_AnimNotify_StartDrillVFX_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_StopDrillVfx
struct UAnim_MinerMk3_C_AnimNotify_StopDrillVfx_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.BlueprintInitializeAnimation
struct UAnim_MinerMk3_C_BlueprintInitializeAnimation_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_MinerIndustrialEnteredReloadState
struct UAnim_MinerMk3_C_AnimNotify_MinerIndustrialEnteredReloadState_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_MinerIndustrialEnteredOutputFullState
struct UAnim_MinerMk3_C_AnimNotify_MinerIndustrialEnteredOutputFullState_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_MinerIndustrialLeftOutputFullState
struct UAnim_MinerMk3_C_AnimNotify_MinerIndustrialLeftOutputFullState_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_MinerIndustrialAudioStartSpin
struct UAnim_MinerMk3_C_AnimNotify_MinerIndustrialAudioStartSpin_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_MinerIndustrialAudioDrillDown
struct UAnim_MinerMk3_C_AnimNotify_MinerIndustrialAudioDrillDown_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_MinerIndustrialAudioStopDrill
struct UAnim_MinerMk3_C_AnimNotify_MinerIndustrialAudioStopDrill_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_MinerIndustrialAudioLowpassOn
struct UAnim_MinerMk3_C_AnimNotify_MinerIndustrialAudioLowpassOn_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.AnimNotify_MinerIndustrialAudioLowpassOff
struct UAnim_MinerMk3_C_AnimNotify_MinerIndustrialAudioLowpassOff_Params
{
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.HasPowerChanged
struct UAnim_MinerMk3_C_HasPowerChanged_Params
{
	bool                                               State;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Anim_MinerMk3.Anim_MinerMk3_C.ExecuteUbergraph_Anim_MinerMk3
struct UAnim_MinerMk3_C_ExecuteUbergraph_Anim_MinerMk3_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
