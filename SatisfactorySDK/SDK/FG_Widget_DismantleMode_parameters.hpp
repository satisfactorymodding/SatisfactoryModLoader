#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_DismantleMode_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_DismantleMode.Widget_DismantleMode_C.GetReticleVisibility
struct UWidget_DismantleMode_C_GetReticleVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_DismantleMode.Widget_DismantleMode_C.SetDismantleRefunds
struct UWidget_DismantleMode_C_SetDismantleRefunds_Params
{
};

// Function Widget_DismantleMode.Widget_DismantleMode_C.OnEscapePressed
struct UWidget_DismantleMode_C_OnEscapePressed_Params
{
};

// Function Widget_DismantleMode.Widget_DismantleMode_C.Init
struct UWidget_DismantleMode_C_Init_Params
{
};

// Function Widget_DismantleMode.Widget_DismantleMode_C.Tick
struct UWidget_DismantleMode_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_DismantleMode.Widget_DismantleMode_C.Construct
struct UWidget_DismantleMode_C_Construct_Params
{
};

// Function Widget_DismantleMode.Widget_DismantleMode_C.OnDismantleRefundChanged
struct UWidget_DismantleMode_C_OnDismantleRefundChanged_Params
{
	class UFGBuildGunStateDismantle*                   dismantleGun;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_DismantleMode.Widget_DismantleMode_C.ExecuteUbergraph_Widget_DismantleMode
struct UWidget_DismantleMode_C_ExecuteUbergraph_Widget_DismantleMode_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
