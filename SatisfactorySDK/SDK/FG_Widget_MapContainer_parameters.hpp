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

// Function Widget_MapContainer.Widget_MapContainer_C.ExecuteUbergraph_Widget_MapContainer
struct UWidget_MapContainer_C_ExecuteUbergraph_Widget_MapContainer_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
