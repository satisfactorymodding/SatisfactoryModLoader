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

// ScriptStruct MediaUtils.MediaPlayerTrackOptions
// 0x001C
struct FMediaPlayerTrackOptions
{
	int                                                Audio;                                                    // 0x0000(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Caption;                                                  // 0x0004(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                MetaData;                                                 // 0x0008(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Script;                                                   // 0x000C(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Subtitle;                                                 // 0x0010(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Text;                                                     // 0x0014(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                Video;                                                    // 0x0018(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MediaUtils.MediaPlayerOptions
// 0x001C
struct FMediaPlayerOptions
{
	struct FMediaPlayerTrackOptions                    TRACKS;                                                   // 0x0000(0x001C) (BlueprintVisible)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
