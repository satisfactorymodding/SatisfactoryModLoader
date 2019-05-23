#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

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

// ScriptStruct MediaCompositing.MovieSceneMediaSectionParams
// 0x0030
struct FMovieSceneMediaSectionParams
{
	class UMediaSoundComponent*                        MediaSoundComponent;                                      // 0x0000(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UMediaSource*                                MediaSource;                                              // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData)
	class UMediaTexture*                               MediaTexture;                                             // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
	class FString                                      Proxy;                                                    // 0x0018(0x0010) (ZeroConstructor)
	struct FFrameNumber                                SectionStartFrame;                                        // 0x0028(0x0004)
	struct FFrameNumber                                SectionEndFrame;                                          // 0x002C(0x0004)
};

// ScriptStruct MediaCompositing.MovieSceneMediaSectionTemplate
// 0x0030 (0x0050 - 0x0020)
struct FMovieSceneMediaSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneMediaSectionParams               Params;                                                   // 0x0020(0x0030)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
