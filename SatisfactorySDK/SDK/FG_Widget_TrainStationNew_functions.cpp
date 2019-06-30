// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TrainStationNew_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.UpdatePowerStatus
// ()

void UWidget_TrainStationNew_C::UpdatePowerStatus()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.UpdatePowerStatus");

	UWidget_TrainStationNew_C_UpdatePowerStatus_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.ShowLocomotiveMenu
// ()
// Parameters:
// class AFGTrain*                mTrain                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TrainStationNew_C::ShowLocomotiveMenu(class AFGTrain* mTrain)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.ShowLocomotiveMenu");

	UWidget_TrainStationNew_C_ShowLocomotiveMenu_Params params;
	params.mTrain = mTrain;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.GenerateTrainList
// ()

void UWidget_TrainStationNew_C::GenerateTrainList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.GenerateTrainList");

	UWidget_TrainStationNew_C_GenerateTrainList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.GetStationName
// ()
// Parameters:
// struct FText                   Name                           (Parm, OutParm)

void UWidget_TrainStationNew_C::GetStationName(struct FText* Name)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.GetStationName");

	UWidget_TrainStationNew_C_GetStationName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Name != nullptr)
		*Name = params.Name;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.SetStationName
// ()
// Parameters:
// struct FText                   Name                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_TrainStationNew_C::SetStationName(const struct FText& Name)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.SetStationName");

	UWidget_TrainStationNew_C_SetStationName_Params params;
	params.Name = Name;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnGetPowerCircuit
// ()
// Parameters:
// class UFGPowerCircuit*         ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UFGPowerCircuit* UWidget_TrainStationNew_C::OnGetPowerCircuit()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnGetPowerCircuit");

	UWidget_TrainStationNew_C_OnGetPowerCircuit_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.Construct
// ()

void UWidget_TrainStationNew_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.Construct");

	UWidget_TrainStationNew_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnEscapePressed
// ()

void UWidget_TrainStationNew_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnEscapePressed");

	UWidget_TrainStationNew_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.BndEvt__mStationNameInput_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TrainStationNew_C::BndEvt__mStationNameInput_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.BndEvt__mStationNameInput_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature");

	UWidget_TrainStationNew_C_BndEvt__mStationNameInput_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnTrainButtonClicked
// ()
// Parameters:
// class UWidget_TrainButton_C*   Button                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_TrainStationNew_C::OnTrainButtonClicked(class UWidget_TrainButton_C* Button)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnTrainButtonClicked");

	UWidget_TrainStationNew_C_OnTrainButtonClicked_Params params;
	params.Button = Button;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnLocomotiveMenuClosed
// ()

void UWidget_TrainStationNew_C::OnLocomotiveMenuClosed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnLocomotiveMenuClosed");

	UWidget_TrainStationNew_C_OnLocomotiveMenuClosed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnTrainNameChanged
// ()

void UWidget_TrainStationNew_C::OnTrainNameChanged()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnTrainNameChanged");

	UWidget_TrainStationNew_C_OnTrainNameChanged_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnPowerChanged
// ()
// Parameters:
// bool                           State                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TrainStationNew_C::OnPowerChanged(bool State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnPowerChanged");

	UWidget_TrainStationNew_C_OnPowerChanged_Params params;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStationNew.Widget_TrainStationNew_C.ExecuteUbergraph_Widget_TrainStationNew
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TrainStationNew_C::ExecuteUbergraph_Widget_TrainStationNew(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStationNew.Widget_TrainStationNew_C.ExecuteUbergraph_Widget_TrainStationNew");

	UWidget_TrainStationNew_C_ExecuteUbergraph_Widget_TrainStationNew_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
