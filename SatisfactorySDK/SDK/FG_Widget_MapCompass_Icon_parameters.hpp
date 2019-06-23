#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MapCompass_Icon_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.UpdateRadarTowerTime
struct UWidget_MapCompass_Icon_C_UpdateRadarTowerTime_Params
{
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.SetScale
struct UWidget_MapCompass_Icon_C_SetScale_Params
{
	float                                              Scale;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.UpdateActor
struct UWidget_MapCompass_Icon_C_UpdateActor_Params
{
	class UFGActorRepresentation*                      actorRepresentation;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               mIsCompassObject;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.SetIconType
struct UWidget_MapCompass_Icon_C_SetIconType_Params
{
	ERepresentationType                                mRepresentationType;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.TestFunction
struct UWidget_MapCompass_Icon_C_TestFunction_Params
{
	struct FLinearColor                                Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	ERepresentationType                                mRepresentationType;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UTexture2D*                                  Icon;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.SetDescription
struct UWidget_MapCompass_Icon_C_SetDescription_Params
{
	struct FText                                       mDescriptionText;                                         // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.SetRepresentatoinType
struct UWidget_MapCompass_Icon_C_SetRepresentatoinType_Params
{
	ERepresentationType                                mRepresentationType;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.SetRotation
struct UWidget_MapCompass_Icon_C_SetRotation_Params
{
	float                                              Angle;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.SetIcon
struct UWidget_MapCompass_Icon_C_SetIcon_Params
{
	class UTexture2D*                                  Texture;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.SetColor
struct UWidget_MapCompass_Icon_C_SetColor_Params
{
	struct FLinearColor                                InColorAndOpacity;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_MapCompass_Icon_C_BndEvt__Button_1_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.PreConstruct
struct UWidget_MapCompass_Icon_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.DynamicDescriptionUpdate
struct UWidget_MapCompass_Icon_C_DynamicDescriptionUpdate_Params
{
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.Construct
struct UWidget_MapCompass_Icon_C_Construct_Params
{
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.BndEvt__Button_1_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
struct UWidget_MapCompass_Icon_C_BndEvt__Button_1_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.ExecuteUbergraph_Widget_MapCompass_Icon
struct UWidget_MapCompass_Icon_C_ExecuteUbergraph_Widget_MapCompass_Icon_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.OnUnhovered__DelegateSignature
struct UWidget_MapCompass_Icon_C_OnUnhovered__DelegateSignature_Params
{
};

// Function Widget_MapCompass_Icon.Widget_MapCompass_Icon_C.OnHovered__DelegateSignature
struct UWidget_MapCompass_Icon_C_OnHovered__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
