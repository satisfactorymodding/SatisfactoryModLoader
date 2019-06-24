#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// UserDefinedStruct FootstepSoundMapStruct.FootstepSoundMapStruct
// 0x0018
struct FFootstepSoundMapStruct
{
	class UAkAudioEvent*                               RightEvent_6_A1AC1AB14859868CFE55B0ACE1372003;            // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EPhysicalSurface>                      Surface_5_40DB0CE34F611287EBE2649496AA0D53;               // 0x0008(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0009(0x0007) MISSED OFFSET
	class UAkAudioEvent*                               LeftEvent_9_571CF04447A77B2635F4619B88C711CB;             // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
