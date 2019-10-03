#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MapContainer_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_MapContainer.Widget_MapContainer_C.UpdateBeaconViewDistances
struct UWidget_MapContainer_C_UpdateBeaconViewDistances_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.SetupBeaconBindings
struct UWidget_MapContainer_C_SetupBeaconBindings_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          WidgetBeaconViewdistanceSlider;                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.ClearSearch
struct UWidget_MapContainer_C_ClearSearch_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.PopulateSearchResults
struct UWidget_MapContainer_C_PopulateSearchResults_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_MapContainer.Widget_MapContainer_C.GetBeacons
struct UWidget_MapContainer_C_GetBeacons_Params
{
	struct FMapFilterStruct                            BeaconCategory;                                           // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_MapContainer.Widget_MapContainer_C.AddChildToBeacons
struct UWidget_MapContainer_C_AddChildToBeacons_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.RemoveActorRepresentationFromFilterCategories
struct UWidget_MapContainer_C_RemoveActorRepresentationFromFilterCategories_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.UglyFixForActorName
struct UWidget_MapContainer_C_UglyFixForActorName_Params
{
	ERepresentationType                                actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_MapContainer.Widget_MapContainer_C.UpdateMapObjectVisibility
struct UWidget_MapContainer_C_UpdateMapObjectVisibility_Params
{
	ERepresentationType                                Type;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.GetCompassRepresentation
struct UWidget_MapContainer_C_GetCompassRepresentation_Params
{
	ERepresentationType                                Type;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.GetMapRepresentation
struct UWidget_MapContainer_C_GetMapRepresentation_Params
{
	ERepresentationType                                Type;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.SetCompassRepresentation
struct UWidget_MapContainer_C_SetCompassRepresentation_Params
{
	ERepresentationType                                Type;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               visible;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.SetMapRepresentation
struct UWidget_MapContainer_C_SetMapRepresentation_Params
{
	ERepresentationType                                Type;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               visible;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.GetIndexInParent
struct UWidget_MapContainer_C_GetIndexInParent_Params
{
	class UWidget*                                     Widget;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.AddUniqueToFilterCategories
struct UWidget_MapContainer_C_AddUniqueToFilterCategories_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_MapObject_C*                         WidgetMapObject;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               CreatedNewCategory;                                       // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.AddChildToFilters
struct UWidget_MapContainer_C_AddChildToFilters_Params
{
	ERepresentationType                                actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.NormalizedValueToZoomValue
struct UWidget_MapContainer_C_NormalizedValueToZoomValue_Params
{
	float                                              NormalizedValue;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ZoomValue;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.UpdateZoomSlider
struct UWidget_MapContainer_C_UpdateZoomSlider_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.SetOpenMap
struct UWidget_MapContainer_C_SetOpenMap_Params
{
	bool                                               OpenMap;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.Construct
struct UWidget_MapContainer_C_Construct_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.CloseMap
struct UWidget_MapContainer_C_CloseMap_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.OnEscapePressed
struct UWidget_MapContainer_C_OnEscapePressed_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.Destruct
struct UWidget_MapContainer_C_Destruct_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature
struct UWidget_MapContainer_C_BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.SetInputMode
struct UWidget_MapContainer_C_SetInputMode_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_1_OnObjectAddedToMapDispatch__DelegateSignature
struct UWidget_MapContainer_C_BndEvt__Widget_Map_K2Node_ComponentBoundEvent_1_OnObjectAddedToMapDispatch__DelegateSignature_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_MapObject_C*                         WidgetMapObject;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_2_OnObjectUpdatedOnMapDispatch__DelegateSignature
struct UWidget_MapContainer_C_BndEvt__Widget_Map_K2Node_ComponentBoundEvent_2_OnObjectUpdatedOnMapDispatch__DelegateSignature_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_3_OnObjectRemovedFromMapDispatch__DelegateSignature
struct UWidget_MapContainer_C_BndEvt__Widget_Map_K2Node_ComponentBoundEvent_3_OnObjectRemovedFromMapDispatch__DelegateSignature_Params
{
	class UFGActorRepresentation*                      ActorRespresentation;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.OnFilterHovered
struct UWidget_MapContainer_C_OnFilterHovered_Params
{
	class UWidget_FilterButton_C*                      Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.OnFilterUnhovered
struct UWidget_MapContainer_C_OnFilterUnhovered_Params
{
	class UWidget_FilterButton_C*                      Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.onFilterShowOnMapChanged
struct UWidget_MapContainer_C_onFilterShowOnMapChanged_Params
{
	class UWidget_FilterButton_C*                      Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               ShowOnMap;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.onFilterShowOnCompassChanged
struct UWidget_MapContainer_C_onFilterShowOnCompassChanged_Params
{
	class UWidget_FilterButton_C*                      Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               ShowOnCompass;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature
struct UWidget_MapContainer_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconViewDistanceChanged
struct UWidget_MapContainer_C_OnBeaconViewDistanceChanged_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	ECompassViewDistance                               NewViewDistance;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconHovered
struct UWidget_MapContainer_C_OnBeaconHovered_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigaotr;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconUnhovered
struct UWidget_MapContainer_C_OnBeaconUnhovered_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconVeiwDistanceHovered
struct UWidget_MapContainer_C_OnBeaconVeiwDistanceHovered_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	ECompassViewDistance                               viewDistance;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconViewDistanceUnhovered
struct UWidget_MapContainer_C_OnBeaconViewDistanceUnhovered_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_5_OnBeaconSearchChanged__DelegateSignature
struct UWidget_MapContainer_C_BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_5_OnBeaconSearchChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_6_OnClearSearchResults__DelegateSignature
struct UWidget_MapContainer_C_BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_6_OnClearSearchResults__DelegateSignature_Params
{
};

// Function Widget_MapContainer.Widget_MapContainer_C.ExecuteUbergraph_Widget_MapContainer
struct UWidget_MapContainer_C_ExecuteUbergraph_Widget_MapContainer_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
