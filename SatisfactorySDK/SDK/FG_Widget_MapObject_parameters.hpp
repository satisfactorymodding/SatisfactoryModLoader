#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MapObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_MapObject.Widget_MapObject_C.mShowActorDetails
struct UWidget_MapObject_C_mShowActorDetails_Params
{
};

// Function Widget_MapObject.Widget_MapObject_C.Tick
struct UWidget_MapObject_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapObject.Widget_MapObject_C.OnObjectFiltered
struct UWidget_MapObject_C_OnObjectFiltered_Params
{
	bool*                                              FilteredIn;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapObject.Widget_MapObject_C.OnObjectMoved
struct UWidget_MapObject_C_OnObjectMoved_Params
{
	struct FVector2D*                                  normalizedLocation;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapObject.Widget_MapObject_C.OnActorRepresentationUpdated
struct UWidget_MapObject_C_OnActorRepresentationUpdated_Params
{
};

// Function Widget_MapObject.Widget_MapObject_C.Construct
struct UWidget_MapObject_C_Construct_Params
{
};

// Function Widget_MapObject.Widget_MapObject_C.DestructionTimer
struct UWidget_MapObject_C_DestructionTimer_Params
{
	float                                              Time;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapObject.Widget_MapObject_C.BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_0_OnUnhovered__DelegateSignature
struct UWidget_MapObject_C_BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_0_OnUnhovered__DelegateSignature_Params
{
};

// Function Widget_MapObject.Widget_MapObject_C.BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_1_OnHovered__DelegateSignature
struct UWidget_MapObject_C_BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_1_OnHovered__DelegateSignature_Params
{
};

// Function Widget_MapObject.Widget_MapObject_C.ShowActorDetailsEvent
struct UWidget_MapObject_C_ShowActorDetailsEvent_Params
{
};

// Function Widget_MapObject.Widget_MapObject_C.ExecuteUbergraph_Widget_MapObject
struct UWidget_MapObject_C_ExecuteUbergraph_Widget_MapObject_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapObject.Widget_MapObject_C.OnUnhovered__DelegateSignature
struct UWidget_MapObject_C_OnUnhovered__DelegateSignature_Params
{
	class UWidget_MapObject_C*                         MapObject;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MapObject.Widget_MapObject_C.OnHovered__DelegateSignature
struct UWidget_MapObject_C_OnHovered__DelegateSignature_Params
{
	class UWidget_MapObject_C*                         MapObject;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
