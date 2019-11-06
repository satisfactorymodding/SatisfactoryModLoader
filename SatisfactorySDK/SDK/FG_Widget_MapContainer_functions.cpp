// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MapContainer_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_MapContainer.Widget_MapContainer_C.UpdateBeaconViewDistances
// ()

void UWidget_MapContainer_C::UpdateBeaconViewDistances()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.UpdateBeaconViewDistances");

	UWidget_MapContainer_C_UpdateBeaconViewDistances_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.SetupBeaconBindings
// ()
// Parameters:
// class UWidget_BeaconViewdistanceSlider_C* WidgetBeaconViewdistanceSlider (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapContainer_C::SetupBeaconBindings(class UWidget_BeaconViewdistanceSlider_C* WidgetBeaconViewdistanceSlider)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.SetupBeaconBindings");

	UWidget_MapContainer_C_SetupBeaconBindings_Params params;
	params.WidgetBeaconViewdistanceSlider = WidgetBeaconViewdistanceSlider;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.ClearSearch
// ()

void UWidget_MapContainer_C::ClearSearch()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.ClearSearch");

	UWidget_MapContainer_C_ClearSearch_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.PopulateSearchResults
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_MapContainer_C::PopulateSearchResults(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.PopulateSearchResults");

	UWidget_MapContainer_C_PopulateSearchResults_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.GetBeacons
// ()
// Parameters:
// struct FMapFilterStruct        BeaconCategory                 (Parm, OutParm, ZeroConstructor)

void UWidget_MapContainer_C::GetBeacons(struct FMapFilterStruct* BeaconCategory)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.GetBeacons");

	UWidget_MapContainer_C_GetBeacons_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (BeaconCategory != nullptr)
		*BeaconCategory = params.BeaconCategory;
}


// Function Widget_MapContainer.Widget_MapContainer_C.AddChildToBeacons
// ()
// Parameters:
// class UFGActorRepresentation*  actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::AddChildToBeacons(class UFGActorRepresentation* actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.AddChildToBeacons");

	UWidget_MapContainer_C_AddChildToBeacons_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.RemoveActorRepresentationFromFilterCategories
// ()
// Parameters:
// class UFGActorRepresentation*  actorRepresentation            (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)

void UWidget_MapContainer_C::RemoveActorRepresentationFromFilterCategories(class UFGActorRepresentation* actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.RemoveActorRepresentationFromFilterCategories");

	UWidget_MapContainer_C_RemoveActorRepresentationFromFilterCategories_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.UglyFixForActorName
// ()
// Parameters:
// ERepresentationType            actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_MapContainer_C::UglyFixForActorName(ERepresentationType actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.UglyFixForActorName");

	UWidget_MapContainer_C_UglyFixForActorName_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MapContainer.Widget_MapContainer_C.UpdateMapObjectVisibility
// ()
// Parameters:
// ERepresentationType            Type                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::UpdateMapObjectVisibility(ERepresentationType Type)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.UpdateMapObjectVisibility");

	UWidget_MapContainer_C_UpdateMapObjectVisibility_Params params;
	params.Type = Type;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.GetCompassRepresentation
// ()
// Parameters:
// ERepresentationType            Type                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_MapContainer_C::GetCompassRepresentation(ERepresentationType Type)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.GetCompassRepresentation");

	UWidget_MapContainer_C_GetCompassRepresentation_Params params;
	params.Type = Type;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MapContainer.Widget_MapContainer_C.GetMapRepresentation
// ()
// Parameters:
// ERepresentationType            Type                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_MapContainer_C::GetMapRepresentation(ERepresentationType Type)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.GetMapRepresentation");

	UWidget_MapContainer_C_GetMapRepresentation_Params params;
	params.Type = Type;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MapContainer.Widget_MapContainer_C.SetCompassRepresentation
// ()
// Parameters:
// ERepresentationType            Type                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           visible                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::SetCompassRepresentation(ERepresentationType Type, bool visible)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.SetCompassRepresentation");

	UWidget_MapContainer_C_SetCompassRepresentation_Params params;
	params.Type = Type;
	params.visible = visible;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.SetMapRepresentation
// ()
// Parameters:
// ERepresentationType            Type                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           visible                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::SetMapRepresentation(ERepresentationType Type, bool visible)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.SetMapRepresentation");

	UWidget_MapContainer_C_SetMapRepresentation_Params params;
	params.Type = Type;
	params.visible = visible;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.GetIndexInParent
// ()
// Parameters:
// class UWidget*                 Widget                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UWidget_MapContainer_C::GetIndexInParent(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.GetIndexInParent");

	UWidget_MapContainer_C_GetIndexInParent_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MapContainer.Widget_MapContainer_C.AddUniqueToFilterCategories
// ()
// Parameters:
// class UFGActorRepresentation*  actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_MapObject_C*     WidgetMapObject                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           CreatedNewCategory             (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::AddUniqueToFilterCategories(class UFGActorRepresentation* actorRepresentation, class UWidget_MapObject_C* WidgetMapObject, bool* CreatedNewCategory)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.AddUniqueToFilterCategories");

	UWidget_MapContainer_C_AddUniqueToFilterCategories_Params params;
	params.actorRepresentation = actorRepresentation;
	params.WidgetMapObject = WidgetMapObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (CreatedNewCategory != nullptr)
		*CreatedNewCategory = params.CreatedNewCategory;
}


// Function Widget_MapContainer.Widget_MapContainer_C.AddChildToFilters
// ()
// Parameters:
// ERepresentationType            actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::AddChildToFilters(ERepresentationType actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.AddChildToFilters");

	UWidget_MapContainer_C_AddChildToFilters_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.NormalizedValueToZoomValue
// ()
// Parameters:
// float                          NormalizedValue                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ZoomValue                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::NormalizedValueToZoomValue(float NormalizedValue, struct FVector2D* ZoomValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.NormalizedValueToZoomValue");

	UWidget_MapContainer_C_NormalizedValueToZoomValue_Params params;
	params.NormalizedValue = NormalizedValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ZoomValue != nullptr)
		*ZoomValue = params.ZoomValue;
}


// Function Widget_MapContainer.Widget_MapContainer_C.UpdateZoomSlider
// ()

void UWidget_MapContainer_C::UpdateZoomSlider()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.UpdateZoomSlider");

	UWidget_MapContainer_C_UpdateZoomSlider_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.SetOpenMap
// ()
// Parameters:
// bool                           OpenMap                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::SetOpenMap(bool OpenMap)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.SetOpenMap");

	UWidget_MapContainer_C_SetOpenMap_Params params;
	params.OpenMap = OpenMap;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.Construct
// ()

void UWidget_MapContainer_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.Construct");

	UWidget_MapContainer_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.CloseMap
// ()

void UWidget_MapContainer_C::CloseMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.CloseMap");

	UWidget_MapContainer_C_CloseMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnEscapePressed
// ()

void UWidget_MapContainer_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnEscapePressed");

	UWidget_MapContainer_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.Destruct
// ()

void UWidget_MapContainer_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.Destruct");

	UWidget_MapContainer_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_MapContainer_C_BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.SetInputMode
// ()

void UWidget_MapContainer_C::SetInputMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.SetInputMode");

	UWidget_MapContainer_C_SetInputMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_1_OnObjectAddedToMapDispatch__DelegateSignature
// ()
// Parameters:
// class UFGActorRepresentation*  actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_MapObject_C*     WidgetMapObject                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapContainer_C::BndEvt__Widget_Map_K2Node_ComponentBoundEvent_1_OnObjectAddedToMapDispatch__DelegateSignature(class UFGActorRepresentation* actorRepresentation, class UWidget_MapObject_C* WidgetMapObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_1_OnObjectAddedToMapDispatch__DelegateSignature");

	UWidget_MapContainer_C_BndEvt__Widget_Map_K2Node_ComponentBoundEvent_1_OnObjectAddedToMapDispatch__DelegateSignature_Params params;
	params.actorRepresentation = actorRepresentation;
	params.WidgetMapObject = WidgetMapObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_2_OnObjectUpdatedOnMapDispatch__DelegateSignature
// ()
// Parameters:
// class UFGActorRepresentation*  actorRepresentation            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::BndEvt__Widget_Map_K2Node_ComponentBoundEvent_2_OnObjectUpdatedOnMapDispatch__DelegateSignature(class UFGActorRepresentation* actorRepresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_2_OnObjectUpdatedOnMapDispatch__DelegateSignature");

	UWidget_MapContainer_C_BndEvt__Widget_Map_K2Node_ComponentBoundEvent_2_OnObjectUpdatedOnMapDispatch__DelegateSignature_Params params;
	params.actorRepresentation = actorRepresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_3_OnObjectRemovedFromMapDispatch__DelegateSignature
// ()
// Parameters:
// class UFGActorRepresentation*  ActorRespresentation           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::BndEvt__Widget_Map_K2Node_ComponentBoundEvent_3_OnObjectRemovedFromMapDispatch__DelegateSignature(class UFGActorRepresentation* ActorRespresentation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_K2Node_ComponentBoundEvent_3_OnObjectRemovedFromMapDispatch__DelegateSignature");

	UWidget_MapContainer_C_BndEvt__Widget_Map_K2Node_ComponentBoundEvent_3_OnObjectRemovedFromMapDispatch__DelegateSignature_Params params;
	params.ActorRespresentation = ActorRespresentation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnFilterHovered
// ()
// Parameters:
// class UWidget_FilterButton_C*  Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapContainer_C::OnFilterHovered(class UWidget_FilterButton_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnFilterHovered");

	UWidget_MapContainer_C_OnFilterHovered_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnFilterUnhovered
// ()
// Parameters:
// class UWidget_FilterButton_C*  Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapContainer_C::OnFilterUnhovered(class UWidget_FilterButton_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnFilterUnhovered");

	UWidget_MapContainer_C_OnFilterUnhovered_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.onFilterShowOnMapChanged
// ()
// Parameters:
// class UWidget_FilterButton_C*  Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           ShowOnMap                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::onFilterShowOnMapChanged(class UWidget_FilterButton_C* Instigator, bool ShowOnMap)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.onFilterShowOnMapChanged");

	UWidget_MapContainer_C_onFilterShowOnMapChanged_Params params;
	params.Instigator = Instigator;
	params.ShowOnMap = ShowOnMap;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.onFilterShowOnCompassChanged
// ()
// Parameters:
// class UWidget_FilterButton_C*  Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           ShowOnCompass                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::onFilterShowOnCompassChanged(class UWidget_FilterButton_C* Instigator, bool ShowOnCompass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.onFilterShowOnCompassChanged");

	UWidget_MapContainer_C_onFilterShowOnCompassChanged_Params params;
	params.Instigator = Instigator;
	params.ShowOnCompass = ShowOnCompass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_MapContainer_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature");

	UWidget_MapContainer_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconViewDistanceChanged
// ()
// Parameters:
// class UWidget_BeaconViewdistanceSlider_C* Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// ECompassViewDistance           NewViewDistance                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::OnBeaconViewDistanceChanged(class UWidget_BeaconViewdistanceSlider_C* Instigator, ECompassViewDistance NewViewDistance)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconViewDistanceChanged");

	UWidget_MapContainer_C_OnBeaconViewDistanceChanged_Params params;
	params.Instigator = Instigator;
	params.NewViewDistance = NewViewDistance;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconHovered
// ()
// Parameters:
// class UWidget_BeaconViewdistanceSlider_C* Instigaotr                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapContainer_C::OnBeaconHovered(class UWidget_BeaconViewdistanceSlider_C* Instigaotr)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconHovered");

	UWidget_MapContainer_C_OnBeaconHovered_Params params;
	params.Instigaotr = Instigaotr;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconUnhovered
// ()
// Parameters:
// class UWidget_BeaconViewdistanceSlider_C* Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapContainer_C::OnBeaconUnhovered(class UWidget_BeaconViewdistanceSlider_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconUnhovered");

	UWidget_MapContainer_C_OnBeaconUnhovered_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconVeiwDistanceHovered
// ()
// Parameters:
// class UWidget_BeaconViewdistanceSlider_C* Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// ECompassViewDistance           viewDistance                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::OnBeaconVeiwDistanceHovered(class UWidget_BeaconViewdistanceSlider_C* Instigator, ECompassViewDistance viewDistance)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconVeiwDistanceHovered");

	UWidget_MapContainer_C_OnBeaconVeiwDistanceHovered_Params params;
	params.Instigator = Instigator;
	params.viewDistance = viewDistance;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconViewDistanceUnhovered
// ()
// Parameters:
// class UWidget_BeaconViewdistanceSlider_C* Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapContainer_C::OnBeaconViewDistanceUnhovered(class UWidget_BeaconViewdistanceSlider_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnBeaconViewDistanceUnhovered");

	UWidget_MapContainer_C_OnBeaconViewDistanceUnhovered_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_5_OnBeaconSearchChanged__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_MapContainer_C::BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_5_OnBeaconSearchChanged__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_5_OnBeaconSearchChanged__DelegateSignature");

	UWidget_MapContainer_C_BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_5_OnBeaconSearchChanged__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_6_OnClearSearchResults__DelegateSignature
// ()

void UWidget_MapContainer_C::BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_6_OnClearSearchResults__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_6_OnClearSearchResults__DelegateSignature");

	UWidget_MapContainer_C_BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_6_OnClearSearchResults__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.ExecuteUbergraph_Widget_MapContainer
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::ExecuteUbergraph_Widget_MapContainer(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.ExecuteUbergraph_Widget_MapContainer");

	UWidget_MapContainer_C_ExecuteUbergraph_Widget_MapContainer_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
