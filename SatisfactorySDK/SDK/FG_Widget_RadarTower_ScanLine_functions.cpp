// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RadarTower_ScanLine_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.SetupScanline
// ()
// Parameters:
// float                          MaxSize                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          NormalizedRadius               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadarTower_ScanLine_C::SetupScanline(float MaxSize, float NormalizedRadius)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.SetupScanline");

	UWidget_RadarTower_ScanLine_C_SetupScanline_Params params;
	params.MaxSize = MaxSize;
	params.NormalizedRadius = NormalizedRadius;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadarTower_ScanLine_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.PreConstruct");

	UWidget_RadarTower_ScanLine_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.ExecuteUbergraph_Widget_RadarTower_ScanLine
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RadarTower_ScanLine_C::ExecuteUbergraph_Widget_RadarTower_ScanLine(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.ExecuteUbergraph_Widget_RadarTower_ScanLine");

	UWidget_RadarTower_ScanLine_C_ExecuteUbergraph_Widget_RadarTower_ScanLine_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
