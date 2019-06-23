// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SpaceElevator_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SpaceElevator.Widget_SpaceElevator_C.DisplayEarlyAccessBlocker
// ()

void UWidget_SpaceElevator_C::DisplayEarlyAccessBlocker()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.DisplayEarlyAccessBlocker");

	UWidget_SpaceElevator_C_DisplayEarlyAccessBlocker_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.UpdateHeaderText
// ()

void UWidget_SpaceElevator_C::UpdateHeaderText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.UpdateHeaderText");

	UWidget_SpaceElevator_C_UpdateHeaderText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetStatusText
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)
// bool                           Pulsing                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_C::SetStatusText(const struct FText& Text, bool Pulsing)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetStatusText");

	UWidget_SpaceElevator_C_SetStatusText_Params params;
	params.Text = Text;
	params.Pulsing = Pulsing;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.UpdatePhaseInfo
// ()

void UWidget_SpaceElevator_C::UpdatePhaseInfo()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.UpdatePhaseInfo");

	UWidget_SpaceElevator_C_UpdatePhaseInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetUnlockTiers
// ()
// Parameters:
// int                            FirstUnlockTier                (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// int                            LastUnlockTier                 (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_C::SetUnlockTiers(int* FirstUnlockTier, int* LastUnlockTier)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetUnlockTiers");

	UWidget_SpaceElevator_C_SetUnlockTiers_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (FirstUnlockTier != nullptr)
		*FirstUnlockTier = params.FirstUnlockTier;
	if (LastUnlockTier != nullptr)
		*LastUnlockTier = params.LastUnlockTier;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.ClearInactiveLeverSelections
// ()
// Parameters:
// class UWidgetAnimation*        ActiveAnimation                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SpaceElevator_C::ClearInactiveLeverSelections(class UWidgetAnimation* ActiveAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.ClearInactiveLeverSelections");

	UWidget_SpaceElevator_C_ClearInactiveLeverSelections_Params params;
	params.ActiveAnimation = ActiveAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.DropInventorySlotStack");

	UWidget_SpaceElevator_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.GetPayOffContainerVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SpaceElevator_C::GetPayOffContainerVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.GetPayOffContainerVisibility");

	UWidget_SpaceElevator_C_GetPayOffContainerVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetupPayOffWidgets
// ()

void UWidget_SpaceElevator_C::SetupPayOffWidgets()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.SetupPayOffWidgets");

	UWidget_SpaceElevator_C_SetupPayOffWidgets_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.Construct
// ()

void UWidget_SpaceElevator_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.Construct");

	UWidget_SpaceElevator_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.Init
// ()

void UWidget_SpaceElevator_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.Init");

	UWidget_SpaceElevator_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.PollAndSetupInventory
// ()

void UWidget_SpaceElevator_C::PollAndSetupInventory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.PollAndSetupInventory");

	UWidget_SpaceElevator_C_PollAndSetupInventory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.OnGamePhaseChanged
// ()
// Parameters:
// TEnumAsByte<EGamePhase>        NewGamePhase                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_C::OnGamePhaseChanged(TEnumAsByte<EGamePhase> NewGamePhase)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.OnGamePhaseChanged");

	UWidget_SpaceElevator_C_OnGamePhaseChanged_Params params;
	params.NewGamePhase = NewGamePhase;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.On Lever Select
// ()
// Parameters:
// int                            SelectionIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_C::On_Lever_Select(int SelectionIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.On Lever Select");

	UWidget_SpaceElevator_C_On_Lever_Select_Params params;
	params.SelectionIndex = SelectionIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.OnUpgrade
// ()

void UWidget_SpaceElevator_C::OnUpgrade()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.OnUpgrade");

	UWidget_SpaceElevator_C_OnUpgrade_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.Tick");

	UWidget_SpaceElevator_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.ActivateSend
// ()

void UWidget_SpaceElevator_C::ActivateSend()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.ActivateSend");

	UWidget_SpaceElevator_C_ActivateSend_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSmoke
// ()

void UWidget_SpaceElevator_C::SpawnSmoke()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSmoke");

	UWidget_SpaceElevator_C_SpawnSmoke_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSparksRight
// ()

void UWidget_SpaceElevator_C::SpawnSparksRight()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSparksRight");

	UWidget_SpaceElevator_C_SpawnSparksRight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSparksLeft
// ()

void UWidget_SpaceElevator_C::SpawnSparksLeft()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.SpawnSparksLeft");

	UWidget_SpaceElevator_C_SpawnSparksLeft_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.StartShake
// ()

void UWidget_SpaceElevator_C::StartShake()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.StartShake");

	UWidget_SpaceElevator_C_StartShake_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.StopShake
// ()

void UWidget_SpaceElevator_C::StopShake()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.StopShake");

	UWidget_SpaceElevator_C_StopShake_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.ResetLever
// ()

void UWidget_SpaceElevator_C::ResetLever()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.ResetLever");

	UWidget_SpaceElevator_C_ResetLever_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.Destruct
// ()

void UWidget_SpaceElevator_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.Destruct");

	UWidget_SpaceElevator_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.AnimNotify_Chime
// ()

void UWidget_SpaceElevator_C::AnimNotify_Chime()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.AnimNotify_Chime");

	UWidget_SpaceElevator_C_AnimNotify_Chime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SpaceElevator.Widget_SpaceElevator_C.ExecuteUbergraph_Widget_SpaceElevator
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SpaceElevator_C::ExecuteUbergraph_Widget_SpaceElevator(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SpaceElevator.Widget_SpaceElevator_C.ExecuteUbergraph_Widget_SpaceElevator");

	UWidget_SpaceElevator_C_ExecuteUbergraph_Widget_SpaceElevator_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
