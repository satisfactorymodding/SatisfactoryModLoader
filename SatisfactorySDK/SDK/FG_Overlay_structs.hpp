#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct Overlay.OverlayItem
// 0x0028
struct FOverlayItem
{
	struct FTimespan                                   StartTime;                                                // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor)
	struct FTimespan                                   EndTime;                                                  // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor)
	class FString                                      Text;                                                     // 0x0010(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FVector2D                                   Position;                                                 // 0x0020(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
