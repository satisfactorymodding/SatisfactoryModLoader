// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HotbarContainer_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HotbarContainer.Widget_HotbarContainer_C.Construct
// ()

void UWidget_HotbarContainer_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.Construct");

	UWidget_HotbarContainer_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarContainer.Widget_HotbarContainer_C.Destruct
// ()

void UWidget_HotbarContainer_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.Destruct");

	UWidget_HotbarContainer_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnHotbarUpdated
// ()

void UWidget_HotbarContainer_C::OnHotbarUpdated()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnHotbarUpdated");

	UWidget_HotbarContainer_C_OnHotbarUpdated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnHotbarLayoutUpdated
// ()

void UWidget_HotbarContainer_C::OnHotbarLayoutUpdated()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnHotbarLayoutUpdated");

	UWidget_HotbarContainer_C_OnHotbarLayoutUpdated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarContainer.Widget_HotbarContainer_C.ShowNotification
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HotbarContainer_C::ShowNotification(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.ShowNotification");

	UWidget_HotbarContainer_C_ShowNotification_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarContainer.Widget_HotbarContainer_C.ListenForPurchasedSchematics
// ()

void UWidget_HotbarContainer_C::ListenForPurchasedSchematics()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.ListenForPurchasedSchematics");

	UWidget_HotbarContainer_C_ListenForPurchasedSchematics_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnPurchasedSchematic
// ()
// Parameters:
// class UClass*                  purchasedSchematic             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HotbarContainer_C::OnPurchasedSchematic(class UClass* purchasedSchematic)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.OnPurchasedSchematic");

	UWidget_HotbarContainer_C_OnPurchasedSchematic_Params params;
	params.purchasedSchematic = purchasedSchematic;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarContainer.Widget_HotbarContainer_C.StopListenForPurchasedSchematics
// ()

void UWidget_HotbarContainer_C::StopListenForPurchasedSchematics()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.StopListenForPurchasedSchematics");

	UWidget_HotbarContainer_C_StopListenForPurchasedSchematics_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HotbarContainer.Widget_HotbarContainer_C.ExecuteUbergraph_Widget_HotbarContainer
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HotbarContainer_C::ExecuteUbergraph_Widget_HotbarContainer(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HotbarContainer.Widget_HotbarContainer_C.ExecuteUbergraph_Widget_HotbarContainer");

	UWidget_HotbarContainer_C_ExecuteUbergraph_Widget_HotbarContainer_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
