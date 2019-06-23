#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ProgrammableSplitter_List_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.GenerateDescriptorList
struct UWidget_ProgrammableSplitter_List_C_GenerateDescriptorList_Params
{
	class AFGBuildableSplitterSmart*                   SmartSplitter;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.GetSelectedDescriptor
struct UWidget_ProgrammableSplitter_List_C_GetSelectedDescriptor_Params
{
	int                                                ButtonIndex;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        Button;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.ExecuteUbergraph_Widget_ProgrammableSplitter_List
struct UWidget_ProgrammableSplitter_List_C_ExecuteUbergraph_Widget_ProgrammableSplitter_List_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ProgrammableSplitter_List.Widget_ProgrammableSplitter_List_C.onSelectionChanged__DelegateSignature
struct UWidget_ProgrammableSplitter_List_C_onSelectionChanged__DelegateSignature_Params
{
	class UClass*                                      Descriptor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
