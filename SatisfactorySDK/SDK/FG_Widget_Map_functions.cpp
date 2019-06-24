// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Map_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Map.Widget_Map_C.DiscardInput
// ()

void UWidget_Map_C::DiscardInput()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.DiscardInput");

	UWidget_Map_C_DiscardInput_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.ListenForInputActions
// ()

void UWidget_Map_C::ListenForInputActions()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.ListenForInputActions");

	UWidget_Map_C_ListenForInputActions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.UpdateObjectOnMap
// ()
// Parameters:
// class UFGActorRepresentation*  actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::UpdateObjectOnMap(class UFGActorRepresentation* actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.UpdateObjectOnMap");

	UWidget_Map_C_UpdateObjectOnMap_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.CenterMapOnPlayer
// ()
// Parameters:
// struct FVector2D               normalizedWorldLocation        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::CenterMapOnPlayer(const struct FVector2D& normalizedWorldLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.CenterMapOnPlayer");

	UWidget_Map_C_CenterMapOnPlayer_Params params;
	params.normalizedWorldLocation = normalizedWorldLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnIconUnhover
// ()
// Parameters:
// class UWidget_MapObject_C*     MapObject                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Map_C::OnIconUnhover(class UWidget_MapObject_C* MapObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnIconUnhover");

	UWidget_Map_C_OnIconUnhover_Params params;
	params.MapObject = MapObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnIconHover
// ()
// Parameters:
// class UWidget_MapObject_C*     MapObject                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Map_C::OnIconHover(class UWidget_MapObject_C* MapObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnIconHover");

	UWidget_Map_C_OnIconHover_Params params;
	params.MapObject = MapObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.AddObjectToMap
// ()
// Parameters:
// class UFGActorRepresentation*  actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::AddObjectToMap(class UFGActorRepresentation* actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.AddObjectToMap");

	UWidget_Map_C_AddObjectToMap_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.RemoveObjectFromMap
// ()
// Parameters:
// class UFGActorRepresentation*  ActorRepresentationToRemove    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::RemoveObjectFromMap(class UFGActorRepresentation* ActorRepresentationToRemove)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.RemoveObjectFromMap");

	UWidget_Map_C_RemoveObjectFromMap_Params params;
	params.ActorRepresentationToRemove = ActorRepresentationToRemove;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.ClearScrollMap
// ()

void UWidget_Map_C::ClearScrollMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.ClearScrollMap");

	UWidget_Map_C_ClearScrollMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnMouseButtonUp
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_Map_C::OnMouseButtonUp(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnMouseButtonUp");

	UWidget_Map_C_OnMouseButtonUp_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Map.Widget_Map_C.ScrollMap
// ()
// Parameters:
// struct FVector2D               MouseOrigin                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               MapOrigin                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::ScrollMap(const struct FVector2D& MouseOrigin, const struct FVector2D& MapOrigin)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.ScrollMap");

	UWidget_Map_C_ScrollMap_Params params;
	params.MouseOrigin = MouseOrigin;
	params.MapOrigin = MapOrigin;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnMouseButtonDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_Map_C::OnMouseButtonDown(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnMouseButtonDown");

	UWidget_Map_C_OnMouseButtonDown_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Map.Widget_Map_C.ZoomMap
// ()
// Parameters:
// struct FVector2D               ZoomValue                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::ZoomMap(const struct FVector2D& ZoomValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.ZoomMap");

	UWidget_Map_C_ZoomMap_Params params;
	params.ZoomValue = ZoomValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnMouseWheel
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_Map_C::OnMouseWheel(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnMouseWheel");

	UWidget_Map_C_OnMouseWheel_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Map.Widget_Map_C.OnMouseLeave
// ()
// Parameters:
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_Map_C::OnMouseLeave(struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnMouseLeave");

	UWidget_Map_C_OnMouseLeave_Params params;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.Construct
// ()

void UWidget_Map_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.Construct");

	UWidget_Map_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnFocusLost
// ()
// Parameters:
// struct FFocusEvent*            InFocusEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Map_C::OnFocusLost(struct FFocusEvent* InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnFocusLost");

	UWidget_Map_C_OnFocusLost_Params params;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.Tick");

	UWidget_Map_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnObjectAddedToMap
// ()
// Parameters:
// class UFGActorRepresentation** actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::OnObjectAddedToMap(class UFGActorRepresentation** actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnObjectAddedToMap");

	UWidget_Map_C_OnObjectAddedToMap_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnObjectRemovedFromMap
// ()
// Parameters:
// class UFGActorRepresentation** actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::OnObjectRemovedFromMap(class UFGActorRepresentation** actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnObjectRemovedFromMap");

	UWidget_Map_C_OnObjectRemovedFromMap_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.Destruct
// ()

void UWidget_Map_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.Destruct");

	UWidget_Map_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnObjectUpdatedOnMap
// ()
// Parameters:
// class UFGActorRepresentation** actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::OnObjectUpdatedOnMap(class UFGActorRepresentation** actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnObjectUpdatedOnMap");

	UWidget_Map_C_OnObjectUpdatedOnMap_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.OnMapCentered
// ()
// Parameters:
// struct FVector2D*              normalizedWorldLocation        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::OnMapCentered(struct FVector2D* normalizedWorldLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.OnMapCentered");

	UWidget_Map_C_OnMapCentered_Params params;
	params.normalizedWorldLocation = normalizedWorldLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.ExecuteUbergraph_Widget_Map
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Map_C::ExecuteUbergraph_Widget_Map(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.ExecuteUbergraph_Widget_Map");

	UWidget_Map_C_ExecuteUbergraph_Widget_Map_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Map.Widget_Map_C.ZoomChanged__DelegateSignature
// ()

void UWidget_Map_C::ZoomChanged__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Map.Widget_Map_C.ZoomChanged__DelegateSignature");

	UWidget_Map_C_ZoomChanged__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
