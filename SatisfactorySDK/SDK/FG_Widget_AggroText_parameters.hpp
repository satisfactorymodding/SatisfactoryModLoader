#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AggroText_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_AggroText.Widget_AggroText_C.Get_Text_Text_1
struct UWidget_AggroText_C_Get_Text_Text_1_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_AggroText.Widget_AggroText_C.SetAggroData
struct UWidget_AggroText_C_SetAggroData_Params
{
	float                                              Aggro;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      ActorName;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	class FString                                      Status;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function Widget_AggroText.Widget_AggroText_C.Tick
struct UWidget_AggroText_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AggroText.Widget_AggroText_C.ExecuteUbergraph_Widget_AggroText
struct UWidget_AggroText_C_ExecuteUbergraph_Widget_AggroText_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
