#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Compass_new_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Compass_new.Widget_Compass_new_C.GetCompassObjectWidgetClass
struct UWidget_Compass_new_C_GetCompassObjectWidgetClass_Params
{
	class UFGActorRepresentation**                     actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Compass_new.Widget_Compass_new_C.Construct
struct UWidget_Compass_new_C_Construct_Params
{
};

// Function Widget_Compass_new.Widget_Compass_new_C.ExecuteUbergraph_Widget_Compass_new
struct UWidget_Compass_new_C_ExecuteUbergraph_Widget_Compass_new_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
