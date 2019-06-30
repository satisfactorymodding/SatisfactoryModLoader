#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Locomotive_Menu_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.UpdatePowerStatus
struct UWidget_Locomotive_Menu_C_UpdatePowerStatus_Params
{
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.GetLocomotiveSpeed
struct UWidget_Locomotive_Menu_C_GetLocomotiveSpeed_Params
{
	class AFGLocomotive*                               Locomotive;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.GetPowerConsumption
struct UWidget_Locomotive_Menu_C_GetPowerConsumption_Params
{
	class AFGLocomotive*                               Locomotive;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Construct
struct UWidget_Locomotive_Menu_C_Construct_Params
{
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Init
struct UWidget_Locomotive_Menu_C_Init_Params
{
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.Destruct
struct UWidget_Locomotive_Menu_C_Destruct_Params
{
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.UpdateLocomotiveStats
struct UWidget_Locomotive_Menu_C_UpdateLocomotiveStats_Params
{
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnEscapePressed
struct UWidget_Locomotive_Menu_C_OnEscapePressed_Params
{
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnNameChanged
struct UWidget_Locomotive_Menu_C_OnNameChanged_Params
{
	struct FText                                       mName;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.ExecuteUbergraph_Widget_Locomotive_Menu
struct UWidget_Locomotive_Menu_C_ExecuteUbergraph_Widget_Locomotive_Menu_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnTrainNameChanged__DelegateSignature
struct UWidget_Locomotive_Menu_C_OnTrainNameChanged__DelegateSignature_Params
{
};

// Function Widget_Locomotive_Menu.Widget_Locomotive_Menu_C.OnClose__DelegateSignature
struct UWidget_Locomotive_Menu_C_OnClose__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
