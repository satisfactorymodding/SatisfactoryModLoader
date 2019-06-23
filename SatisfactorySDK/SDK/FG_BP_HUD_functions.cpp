// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_HUD_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_HUD.BP_HUD_C.IsInventoryOpen
// ()
// Parameters:
// bool                           IsOpen                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_HUD_C::IsInventoryOpen(bool* IsOpen)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.IsInventoryOpen");

	ABP_HUD_C_IsInventoryOpen_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsOpen != nullptr)
		*IsOpen = params.IsOpen;
}


// Function BP_HUD.BP_HUD_C.GetBP_GameUI
// ()
// Parameters:
// class UBP_GameUI_C*            BPGameUI                       (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void ABP_HUD_C::GetBP_GameUI(class UBP_GameUI_C** BPGameUI)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.GetBP_GameUI");

	ABP_HUD_C_GetBP_GameUI_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (BPGameUI != nullptr)
		*BPGameUI = params.BPGameUI;
}


// Function BP_HUD.BP_HUD_C.SetupFrontEnd
// ()

void ABP_HUD_C::SetupFrontEnd()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.SetupFrontEnd");

	ABP_HUD_C_SetupFrontEnd_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.UserConstructionScript
// ()

void ABP_HUD_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.UserConstructionScript");

	ABP_HUD_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.ToggleInventoryUI
// ()

void ABP_HUD_C::ToggleInventoryUI()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.ToggleInventoryUI");

	ABP_HUD_C_ToggleInventoryUI_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.OpenInventoryUI
// ()

void ABP_HUD_C::OpenInventoryUI()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.OpenInventoryUI");

	ABP_HUD_C_OpenInventoryUI_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.OpenInteractUI
// ()
// Parameters:
// class UClass**                 WidgetClass                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UObject**                interactObject                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_HUD_C::OpenInteractUI(class UClass** WidgetClass, class UObject** interactObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.OpenInteractUI");

	ABP_HUD_C_OpenInteractUI_Params params;
	params.WidgetClass = WidgetClass;
	params.interactObject = interactObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.RemovePawnHUD
// ()

void ABP_HUD_C::RemovePawnHUD()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.RemovePawnHUD");

	ABP_HUD_C_RemovePawnHUD_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.AddEquipmentHUD
// ()
// Parameters:
// class UClass**                 WidgetClass                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// EEquipmentSlot*                Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_HUD_C::AddEquipmentHUD(class UClass** WidgetClass, EEquipmentSlot* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.AddEquipmentHUD");

	ABP_HUD_C_AddEquipmentHUD_Params params;
	params.WidgetClass = WidgetClass;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.RemoveEquipmentHUD
// ()
// Parameters:
// EEquipmentSlot*                Slot                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_HUD_C::RemoveEquipmentHUD(EEquipmentSlot* Slot)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.RemoveEquipmentHUD");

	ABP_HUD_C_RemoveEquipmentHUD_Params params;
	params.Slot = Slot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.CloseInteractUIIfOpen
// ()

void ABP_HUD_C::CloseInteractUIIfOpen()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.CloseInteractUIIfOpen");

	ABP_HUD_C_CloseInteractUIIfOpen_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_HUD.BP_HUD_C.ExecuteUbergraph_BP_HUD
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_HUD_C::ExecuteUbergraph_BP_HUD(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_HUD.BP_HUD_C.ExecuteUbergraph_BP_HUD");

	ABP_HUD_C_ExecuteUbergraph_BP_HUD_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
