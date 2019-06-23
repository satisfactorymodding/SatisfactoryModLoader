// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ProgrammableSplitter_List_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.GenerateDescriptorList
// ()
// Parameters:
// class AFGBuildableSplitterSmart* SmartSplitter                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ProgrammableSplitter_List_C::GenerateDescriptorList(class AFGBuildableSplitterSmart* SmartSplitter)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.GenerateDescriptorList");

	UWidget_ProgrammableSplitter_List_C_GenerateDescriptorList_Params params;
	params.SmartSplitter = SmartSplitter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.GetSelectedDescriptor
// ()
// Parameters:
// int                            ButtonIndex                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_ListButton_C*    Button                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ProgrammableSplitter_List_C::GetSelectedDescriptor(int ButtonIndex, class UWidget_ListButton_C* Button)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.GetSelectedDescriptor");

	UWidget_ProgrammableSplitter_List_C_GetSelectedDescriptor_Params params;
	params.ButtonIndex = ButtonIndex;
	params.Button = Button;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.ExecuteUbergraph_Widget_ProgrammableSplitter_List
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ProgrammableSplitter_List_C::ExecuteUbergraph_Widget_ProgrammableSplitter_List(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.ExecuteUbergraph_Widget_ProgrammableSplitter_List");

	UWidget_ProgrammableSplitter_List_C_ExecuteUbergraph_Widget_ProgrammableSplitter_List_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.onSelectionChanged__DelegateSignature
// ()
// Parameters:
// class UClass*                  Descriptor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ProgrammableSplitter_List_C::onSelectionChanged__DelegateSignature(class UClass* Descriptor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.onSelectionChanged__DelegateSignature");

	UWidget_ProgrammableSplitter_List_C_onSelectionChanged__DelegateSignature_Params params;
	params.Descriptor = Descriptor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
