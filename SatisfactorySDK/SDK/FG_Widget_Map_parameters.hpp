#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Map_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Map.Widget_Map_C.DiscardInput
struct UWidget_Map_C_DiscardInput_Params
{
};

// Function Widget_Map.Widget_Map_C.ListenForInputActions
struct UWidget_Map_C_ListenForInputActions_Params
{
};

// Function Widget_Map.Widget_Map_C.UpdateObjectOnMap
struct UWidget_Map_C_UpdateObjectOnMap_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.CenterMapOnPlayer
struct UWidget_Map_C_CenterMapOnPlayer_Params
{
	struct FVector2D                                   normalizedWorldLocation;                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.OnIconUnhover
struct UWidget_Map_C_OnIconUnhover_Params
{
	class UWidget_MapObject_C*                         MapObject;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.OnIconHover
struct UWidget_Map_C_OnIconHover_Params
{
	class UWidget_MapObject_C*                         MapObject;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.AddObjectToMap
struct UWidget_Map_C_AddObjectToMap_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.RemoveObjectFromMap
struct UWidget_Map_C_RemoveObjectFromMap_Params
{
	class UFGActorRepresentation*                      ActorRepresentationToRemove;                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.ClearScrollMap
struct UWidget_Map_C_ClearScrollMap_Params
{
};

// Function Widget_Map.Widget_Map_C.OnMouseButtonUp
struct UWidget_Map_C_OnMouseButtonUp_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Map.Widget_Map_C.ScrollMap
struct UWidget_Map_C_ScrollMap_Params
{
	struct FVector2D                                   MouseOrigin;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   MapOrigin;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.OnMouseButtonDown
struct UWidget_Map_C_OnMouseButtonDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Map.Widget_Map_C.ZoomMap
struct UWidget_Map_C_ZoomMap_Params
{
	struct FVector2D                                   ZoomValue;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.OnMouseWheel
struct UWidget_Map_C_OnMouseWheel_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Map.Widget_Map_C.OnMouseLeave
struct UWidget_Map_C_OnMouseLeave_Params
{
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_Map.Widget_Map_C.Construct
struct UWidget_Map_C_Construct_Params
{
};

// Function Widget_Map.Widget_Map_C.OnFocusLost
struct UWidget_Map_C_OnFocusLost_Params
{
	struct FFocusEvent*                                InFocusEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Map.Widget_Map_C.Tick
struct UWidget_Map_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.OnObjectAddedToMap
struct UWidget_Map_C_OnObjectAddedToMap_Params
{
	class UFGActorRepresentation**                     actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.OnObjectRemovedFromMap
struct UWidget_Map_C_OnObjectRemovedFromMap_Params
{
	class UFGActorRepresentation**                     actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.Destruct
struct UWidget_Map_C_Destruct_Params
{
};

// Function Widget_Map.Widget_Map_C.OnObjectUpdatedOnMap
struct UWidget_Map_C_OnObjectUpdatedOnMap_Params
{
	class UFGActorRepresentation**                     actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.OnMapCentered
struct UWidget_Map_C_OnMapCentered_Params
{
	struct FVector2D*                                  normalizedWorldLocation;                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.ExecuteUbergraph_Widget_Map
struct UWidget_Map_C_ExecuteUbergraph_Widget_Map_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map.Widget_Map_C.ZoomChanged__DelegateSignature
struct UWidget_Map_C_ZoomChanged__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
