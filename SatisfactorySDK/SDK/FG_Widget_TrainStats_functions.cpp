// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TrainStats_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TrainStats.Widget_TrainStats_C.SetTitle
// ()
// Parameters:
// struct FText                   mTrainName                     (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_TrainStats_C::SetTitle(const struct FText& mTrainName)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStats.Widget_TrainStats_C.SetTitle");

	UWidget_TrainStats_C_SetTitle_Params params;
	params.mTrainName = mTrainName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStats.Widget_TrainStats_C.BndEvt__mTrainNameInputBox_K2Node_ComponentBoundEvent_1_OnEditableTextCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TrainStats_C::BndEvt__mTrainNameInputBox_K2Node_ComponentBoundEvent_1_OnEditableTextCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStats.Widget_TrainStats_C.BndEvt__mTrainNameInputBox_K2Node_ComponentBoundEvent_1_OnEditableTextCommittedEvent__DelegateSignature");

	UWidget_TrainStats_C_BndEvt__mTrainNameInputBox_K2Node_ComponentBoundEvent_1_OnEditableTextCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStats.Widget_TrainStats_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TrainStats_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStats.Widget_TrainStats_C.PreConstruct");

	UWidget_TrainStats_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStats.Widget_TrainStats_C.Destruct
// ()

void UWidget_TrainStats_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStats.Widget_TrainStats_C.Destruct");

	UWidget_TrainStats_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStats.Widget_TrainStats_C.ExecuteUbergraph_Widget_TrainStats
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TrainStats_C::ExecuteUbergraph_Widget_TrainStats(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStats.Widget_TrainStats_C.ExecuteUbergraph_Widget_TrainStats");

	UWidget_TrainStats_C_ExecuteUbergraph_Widget_TrainStats_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TrainStats.Widget_TrainStats_C.OnNameChanged__DelegateSignature
// ()
// Parameters:
// struct FText                   mName                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_TrainStats_C::OnNameChanged__DelegateSignature(const struct FText& mName)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TrainStats.Widget_TrainStats_C.OnNameChanged__DelegateSignature");

	UWidget_TrainStats_C_OnNameChanged__DelegateSignature_Params params;
	params.mName = mName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
