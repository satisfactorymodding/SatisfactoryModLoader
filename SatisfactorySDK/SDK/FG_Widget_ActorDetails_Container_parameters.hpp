#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_Container_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_Container.Widget_ActorDetails_Container_C.SetShowPointer
struct UWidget_ActorDetails_Container_C_SetShowPointer_Params
{
	bool                                               ShowPointer;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ActorDetails_Container.Widget_ActorDetails_Container_C.SetTitle
struct UWidget_ActorDetails_Container_C_SetTitle_Params
{
	struct FText                                       mTitle;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_ActorDetails_Container.Widget_ActorDetails_Container_C.PreConstruct
struct UWidget_ActorDetails_Container_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ActorDetails_Container.Widget_ActorDetails_Container_C.Construct
struct UWidget_ActorDetails_Container_C_Construct_Params
{
};

// Function Widget_ActorDetails_Container.Widget_ActorDetails_Container_C.ExecuteUbergraph_Widget_ActorDetails_Container
struct UWidget_ActorDetails_Container_C_ExecuteUbergraph_Widget_ActorDetails_Container_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
