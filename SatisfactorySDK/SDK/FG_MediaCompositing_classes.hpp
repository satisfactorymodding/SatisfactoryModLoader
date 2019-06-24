#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_MediaCompositing_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class MediaCompositing.MovieSceneMediaSection
// 0x0030 (0x0110 - 0x00E0)
class UMovieSceneMediaSection : public UMovieSceneSection
{
public:
	class UMediaSource*                                MediaSource;                                              // 0x00E0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bLooping;                                                 // 0x00E8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00E9(0x0007) MISSED OFFSET
	class UMediaTexture*                               MediaTexture;                                             // 0x00F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UMediaSoundComponent*                        MediaSoundComponent;                                      // 0x00F8(0x0008) (Edit, BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               bUseExternalMediaPlayer;                                  // 0x0100(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0101(0x0007) MISSED OFFSET
	class UMediaPlayer*                                ExternalMediaPlayer;                                      // 0x0108(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MediaCompositing.MovieSceneMediaSection");
		return ptr;
	}

};


// Class MediaCompositing.MovieSceneMediaTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneMediaTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  MediaSections;                                            // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MediaCompositing.MovieSceneMediaTrack");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
