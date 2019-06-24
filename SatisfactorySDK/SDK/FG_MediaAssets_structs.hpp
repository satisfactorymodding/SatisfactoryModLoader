#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_AudioMixer_classes.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_MediaUtils_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum MediaAssets.EMediaWebcamCaptureDeviceFilter
enum class EMediaWebcamCaptureDeviceFilter : uint8_t
{
	DepthSensor                    = 0,
	Front                          = 1,
	Rear                           = 2,
	Unknown                        = 3,
	EMediaWebcamCaptureDeviceFilter_MAX = 4
};


// Enum MediaAssets.EMediaVideoCaptureDeviceFilter
enum class EMediaVideoCaptureDeviceFilter : uint8_t
{
	Card                           = 0,
	Software                       = 1,
	Unknown                        = 2,
	Webcam                         = 3,
	EMediaVideoCaptureDeviceFilter_MAX = 4
};


// Enum MediaAssets.EMediaAudioCaptureDeviceFilter
enum class EMediaAudioCaptureDeviceFilter : uint8_t
{
	Card                           = 0,
	Microphone                     = 1,
	Software                       = 2,
	Unknown                        = 3,
	EMediaAudioCaptureDeviceFilter_MAX = 4
};


// Enum MediaAssets.EMediaPlayerTrack
enum class EMediaPlayerTrack : uint8_t
{
	Audio                          = 0,
	Caption                        = 1,
	Metadata                       = 2,
	Script                         = 3,
	Subtitle                       = 4,
	Text                           = 5,
	Video                          = 6,
	EMediaPlayerTrack_MAX          = 7
};


// Enum MediaAssets.EMediaSoundChannels
enum class EMediaSoundChannels : uint8_t
{
	Mono                           = 0,
	Stereo                         = 1,
	Surround                       = 2,
	EMediaSoundChannels_MAX        = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct MediaAssets.MediaCaptureDevice
// 0x0028
struct FMediaCaptureDevice
{
	struct FText                                       DisplayName;                                              // 0x0000(0x0028) (BlueprintVisible, BlueprintReadOnly, Transient)
	class FString                                      URL;                                                      // 0x0018(0x0010) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
