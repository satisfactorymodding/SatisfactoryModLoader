#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RadarTower_ScanLine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.SetupScanline
struct UWidget_RadarTower_ScanLine_C_SetupScanline_Params
{
	float                                              MaxSize;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              NormalizedRadius;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.PreConstruct
struct UWidget_RadarTower_ScanLine_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadarTower_ScanLine.Widget_RadarTower_ScanLine_C.ExecuteUbergraph_Widget_RadarTower_ScanLine
struct UWidget_RadarTower_ScanLine_C_ExecuteUbergraph_Widget_RadarTower_ScanLine_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
