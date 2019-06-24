// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TradingPost.Widget_TradingPost_C.DropInventorySlotStack
// ()
// Parameters:
// class UWidget_InventorySlot_C** InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           WasStackMoved                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::DropInventorySlotStack(class UWidget_InventorySlot_C** InventorySlot, bool* WasStackMoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.DropInventorySlotStack");

	UWidget_TradingPost_C_DropInventorySlotStack_Params params;
	params.InventorySlot = InventorySlot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WasStackMoved != nullptr)
		*WasStackMoved = params.WasStackMoved;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetLowestNonFullyResearchedTier
// ()
// Parameters:
// int                            tier                           (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// bool                           FoundTier                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::GetLowestNonFullyResearchedTier(int* tier, bool* FoundTier)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetLowestNonFullyResearchedTier");

	UWidget_TradingPost_C_GetLowestNonFullyResearchedTier_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (tier != nullptr)
		*tier = params.tier;
	if (FoundTier != nullptr)
		*FoundTier = params.FoundTier;
}


// Function Widget_TradingPost.Widget_TradingPost_C.CheckIfTierIsFullyResearched
// ()
// Parameters:
// int                            tier                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           IsResearched                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::CheckIfTierIsFullyResearched(int tier, bool* IsResearched)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.CheckIfTierIsFullyResearched");

	UWidget_TradingPost_C_CheckIfTierIsFullyResearched_Params params;
	params.tier = tier;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsResearched != nullptr)
		*IsResearched = params.IsResearched;
}


// Function Widget_TradingPost.Widget_TradingPost_C.SetTierAndDeafultSchematic
// ()
// Parameters:
// int                            tier                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::SetTierAndDeafultSchematic(int tier)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.SetTierAndDeafultSchematic");

	UWidget_TradingPost_C_SetTierAndDeafultSchematic_Params params;
	params.tier = tier;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetSchematicHintTextVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_C::GetSchematicHintTextVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetSchematicHintTextVisibility");

	UWidget_TradingPost_C_GetSchematicHintTextVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetSchematicHintVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_C::GetSchematicHintVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetSchematicHintVisibility");

	UWidget_TradingPost_C_GetSchematicHintVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetTierHintVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_C::GetTierHintVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetTierHintVisibility");

	UWidget_TradingPost_C_GetTierHintVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GenerateTierList
// ()

void UWidget_TradingPost_C::GenerateTierList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GenerateTierList");

	UWidget_TradingPost_C_GenerateTierList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.UpdateInventoryVisibility
// ()

void UWidget_TradingPost_C::UpdateInventoryVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.UpdateInventoryVisibility");

	UWidget_TradingPost_C_UpdateInventoryVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetRewardVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_C::GetRewardVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetRewardVisibility");

	UWidget_TradingPost_C_GetRewardVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetShipAwayFeedback
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_C::GetShipAwayFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetShipAwayFeedback");

	UWidget_TradingPost_C_GetShipAwayFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.SetRewardInformation
// ()
// Parameters:
// struct FText                   inTitle                        (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FText                   inDesc                         (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FSlateBrush             inIcon                         (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_TradingPost_C::SetRewardInformation(const struct FText& inTitle, const struct FText& inDesc, const struct FSlateBrush& inIcon)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.SetRewardInformation");

	UWidget_TradingPost_C_SetRewardInformation_Params params;
	params.inTitle = inTitle;
	params.inDesc = inDesc;
	params.inIcon = inIcon;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetActiveSchematicTabEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_TradingPost_C::GetActiveSchematicTabEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetActiveSchematicTabEnabled");

	UWidget_TradingPost_C_GetActiveSchematicTabEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.SetActiveTab
// ()

void UWidget_TradingPost_C::SetActiveTab()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.SetActiveTab");

	UWidget_TradingPost_C_SetActiveTab_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetShipInventoryVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_C::GetShipInventoryVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetShipInventoryVisibility");

	UWidget_TradingPost_C_GetShipInventoryVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.ActivateSelectedSchematic
// ()

void UWidget_TradingPost_C::ActivateSelectedSchematic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.ActivateSelectedSchematic");

	UWidget_TradingPost_C_ActivateSelectedSchematic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetSelectedRecipeBoxVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_C::GetSelectedRecipeBoxVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetSelectedRecipeBoxVisibility");

	UWidget_TradingPost_C_GetSelectedRecipeBoxVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.SetDefaultDescriptionText
// ()
// Parameters:
// class UClass*                  mSchematicClass                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::SetDefaultDescriptionText(class UClass* mSchematicClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.SetDefaultDescriptionText");

	UWidget_TradingPost_C_SetDefaultDescriptionText_Params params;
	params.mSchematicClass = mSchematicClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.UpdateRewardInfoFromProduct
// ()
// Parameters:
// class UWidget_SchematicRewardItem_C* Reward_Widget                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_TradingPost_C::UpdateRewardInfoFromProduct(class UWidget_SchematicRewardItem_C* Reward_Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.UpdateRewardInfoFromProduct");

	UWidget_TradingPost_C_UpdateRewardInfoFromProduct_Params params;
	params.Reward_Widget = Reward_Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetTabFeedback
// ()

void UWidget_TradingPost_C::GetTabFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetTabFeedback");

	UWidget_TradingPost_C_GetTabFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.OnSchematicClicked
// ()
// Parameters:
// class UClass*                  Schematic                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::OnSchematicClicked(class UClass* Schematic)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.OnSchematicClicked");

	UWidget_TradingPost_C_OnSchematicClicked_Params params;
	params.Schematic = Schematic;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.GetActiveSchematicInfoVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_C::GetActiveSchematicInfoVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.GetActiveSchematicInfoVisibility");

	UWidget_TradingPost_C_GetActiveSchematicInfoVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.SetActiveSchematicInfo
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_TradingPost_C::SetActiveSchematicInfo()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.SetActiveSchematicInfo");

	UWidget_TradingPost_C_SetActiveSchematicInfo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost.Widget_TradingPost_C.Cleanup
// ()

void UWidget_TradingPost_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.Cleanup");

	UWidget_TradingPost_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.Destruct
// ()

void UWidget_TradingPost_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.Destruct");

	UWidget_TradingPost_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.Init
// ()

void UWidget_TradingPost_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.Init");

	UWidget_TradingPost_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.Tick");

	UWidget_TradingPost_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.CloseTradepost
// ()

void UWidget_TradingPost_C::CloseTradepost()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.CloseTradepost");

	UWidget_TradingPost_C_CloseTradepost_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.OnActiveSchematicChanged
// ()
// Parameters:
// class UClass*                  Schematic                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::OnActiveSchematicChanged(class UClass* Schematic)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.OnActiveSchematicChanged");

	UWidget_TradingPost_C_OnActiveSchematicChanged_Params params;
	params.Schematic = Schematic;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.Construct
// ()

void UWidget_TradingPost_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.Construct");

	UWidget_TradingPost_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.purchasedSchematic
// ()
// Parameters:
// class UClass*                  purchasedSchematic             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::purchasedSchematic(class UClass* purchasedSchematic)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.purchasedSchematic");

	UWidget_TradingPost_C_purchasedSchematic_Params params;
	params.purchasedSchematic = purchasedSchematic;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.mShakeWindow
// ()

void UWidget_TradingPost_C::mShakeWindow()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.mShakeWindow");

	UWidget_TradingPost_C_mShakeWindow_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.BndEvt__mWindow_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature
// ()

void UWidget_TradingPost_C::BndEvt__mWindow_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.BndEvt__mWindow_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature");

	UWidget_TradingPost_C_BndEvt__mWindow_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.CreateSmoke
// ()

void UWidget_TradingPost_C::CreateSmoke()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.CreateSmoke");

	UWidget_TradingPost_C_CreateSmoke_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.BndEvt__mWindow_K2Node_ComponentBoundEvent_3_OnTabButtonClicked__DelegateSignature
// ()
// Parameters:
// int                            ButtonIndex                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::BndEvt__mWindow_K2Node_ComponentBoundEvent_3_OnTabButtonClicked__DelegateSignature(int ButtonIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.BndEvt__mWindow_K2Node_ComponentBoundEvent_3_OnTabButtonClicked__DelegateSignature");

	UWidget_TradingPost_C_BndEvt__mWindow_K2Node_ComponentBoundEvent_3_OnTabButtonClicked__DelegateSignature_Params params;
	params.ButtonIndex = ButtonIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TradingPost.Widget_TradingPost_C.ExecuteUbergraph_Widget_TradingPost
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TradingPost_C::ExecuteUbergraph_Widget_TradingPost(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost.Widget_TradingPost_C.ExecuteUbergraph_Widget_TradingPost");

	UWidget_TradingPost_C_ExecuteUbergraph_Widget_TradingPost_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
