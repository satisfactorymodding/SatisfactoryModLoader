#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// UserDefinedStruct BerryAlternatives.BerryAlternatives
// 0x0018
struct FBerryAlternatives
{
	int                                                NumBerries_3_04E44FA44B4EA4BA85E390AD49D0182C;            // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0004(0x0004) MISSED OFFSET
	class UStaticMesh*                                 BushMesh_5_7036F8324BB7951F7ADED7B09E41EE3B;              // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 BerryMesh_7_592ECE8B4AB42BAD1230AEB74FF3C661;             // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
