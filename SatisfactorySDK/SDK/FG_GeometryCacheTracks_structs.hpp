#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_MovieScene_classes.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct GeometryCacheTracks.MovieSceneGeometryCacheParams
// 0x0028
struct FMovieSceneGeometryCacheParams
{
	struct FSoftObjectPath                             GeometryCache;                                            // 0x0000(0x0018) (Edit, ZeroConstructor)
	float                                              StartOffset;                                              // 0x0018(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              EndOffset;                                                // 0x001C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PlayRate;                                                 // 0x0020(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bReverse : 1;                                             // 0x0024(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0025(0x0003) MISSED OFFSET
};

// ScriptStruct GeometryCacheTracks.MovieSceneGeometryCacheSectionTemplateParameters
// 0x0010 (0x0038 - 0x0028)
struct FMovieSceneGeometryCacheSectionTemplateParameters : public FMovieSceneGeometryCacheParams
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	struct FFrameNumber                                SectionStartTime;                                         // 0x0030(0x0004)
	struct FFrameNumber                                SectionEndTime;                                           // 0x0034(0x0004)
};

// ScriptStruct GeometryCacheTracks.MovieSceneGeometryCacheSectionTemplate
// 0x0038 (0x0058 - 0x0020)
struct FMovieSceneGeometryCacheSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneGeometryCacheSectionTemplateParameters Params;                                                   // 0x0020(0x0038)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
