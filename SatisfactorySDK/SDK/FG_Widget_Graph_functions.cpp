// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Graph_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Graph.Widget_Graph_C.OnPaint
// ()
// Parameters:
// struct FPaintContext           Context                        (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_Graph_C::OnPaint(struct FPaintContext* Context)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Graph.Widget_Graph_C.OnPaint");

	UWidget_Graph_C_OnPaint_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Context != nullptr)
		*Context = params.Context;
}


// Function Widget_Graph.Widget_Graph_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Graph_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Graph.Widget_Graph_C.Tick");

	UWidget_Graph_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Graph.Widget_Graph_C.ExecuteUbergraph_Widget_Graph
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Graph_C::ExecuteUbergraph_Widget_Graph(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Graph.Widget_Graph_C.ExecuteUbergraph_Widget_Graph");

	UWidget_Graph_C_ExecuteUbergraph_Widget_Graph_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
