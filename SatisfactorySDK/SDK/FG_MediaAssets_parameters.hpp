#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_MediaAssets_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function MediaAssets.MediaSource.Validate
struct UMediaSource_Validate_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaSource.GetUrl
struct UMediaSource_GetUrl_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function MediaAssets.FileMediaSource.SetFilePath
struct UFileMediaSource_SetFilePath_Params
{
	class FString                                      Path;                                                     // (Parm, ZeroConstructor)
};

// Function MediaAssets.MediaBlueprintFunctionLibrary.EnumerateWebcamCaptureDevices
struct UMediaBlueprintFunctionLibrary_EnumerateWebcamCaptureDevices_Params
{
	TArray<struct FMediaCaptureDevice>                 OutDevices;                                               // (Parm, OutParm, ZeroConstructor)
	int                                                Filter;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function MediaAssets.MediaBlueprintFunctionLibrary.EnumerateVideoCaptureDevices
struct UMediaBlueprintFunctionLibrary_EnumerateVideoCaptureDevices_Params
{
	TArray<struct FMediaCaptureDevice>                 OutDevices;                                               // (Parm, OutParm, ZeroConstructor)
	int                                                Filter;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function MediaAssets.MediaBlueprintFunctionLibrary.EnumerateAudioCaptureDevices
struct UMediaBlueprintFunctionLibrary_EnumerateAudioCaptureDevices_Params
{
	TArray<struct FMediaCaptureDevice>                 OutDevices;                                               // (Parm, OutParm, ZeroConstructor)
	int                                                Filter;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SupportsSeeking
struct UMediaPlayer_SupportsSeeking_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SupportsScrubbing
struct UMediaPlayer_SupportsScrubbing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SupportsRate
struct UMediaPlayer_SupportsRate_Params
{
	float                                              Rate;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               Unthinned;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetViewRotation
struct UMediaPlayer_SetViewRotation_Params
{
	struct FRotator                                    Rotation;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	bool                                               Absolute;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetViewField
struct UMediaPlayer_SetViewField_Params
{
	float                                              Horizontal;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Vertical;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               Absolute;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetVideoTrackFrameRate
struct UMediaPlayer_SetVideoTrackFrameRate_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              FrameRate;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetTrackFormat
struct UMediaPlayer_SetTrackFormat_Params
{
	EMediaPlayerTrack                                  TrackType;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetTimeDelay
struct UMediaPlayer_SetTimeDelay_Params
{
	struct FTimespan                                   TimeDelay;                                                // (Parm, ZeroConstructor)
};

// Function MediaAssets.MediaPlayer.SetRate
struct UMediaPlayer_SetRate_Params
{
	float                                              Rate;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetNativeVolume
struct UMediaPlayer_SetNativeVolume_Params
{
	float                                              Volume;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetLooping
struct UMediaPlayer_SetLooping_Params
{
	bool                                               Looping;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetDesiredPlayerName
struct UMediaPlayer_SetDesiredPlayerName_Params
{
	struct FName                                       PlayerName;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.SetBlockOnTime
struct UMediaPlayer_SetBlockOnTime_Params
{
	struct FTimespan                                   Time;                                                     // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function MediaAssets.MediaPlayer.SelectTrack
struct UMediaPlayer_SelectTrack_Params
{
	EMediaPlayerTrack                                  TrackType;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.Seek
struct UMediaPlayer_Seek_Params
{
	struct FTimespan                                   Time;                                                     // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.Rewind
struct UMediaPlayer_Rewind_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.Reopen
struct UMediaPlayer_Reopen_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.Previous
struct UMediaPlayer_Previous_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.Play
struct UMediaPlayer_Play_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.Pause
struct UMediaPlayer_Pause_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.OpenUrl
struct UMediaPlayer_OpenUrl_Params
{
	class FString                                      URL;                                                      // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.OpenSourceWithOptions
struct UMediaPlayer_OpenSourceWithOptions_Params
{
	class UMediaSource*                                MediaSource;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FMediaPlayerOptions                         options;                                                  // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.OpenSource
struct UMediaPlayer_OpenSource_Params
{
	class UMediaSource*                                MediaSource;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.OpenPlaylistIndex
struct UMediaPlayer_OpenPlaylistIndex_Params
{
	class UMediaPlaylist*                              InPlaylist;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.OpenPlaylist
struct UMediaPlayer_OpenPlaylist_Params
{
	class UMediaPlaylist*                              InPlaylist;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.OpenFile
struct UMediaPlayer_OpenFile_Params
{
	class FString                                      FilePath;                                                 // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.Next
struct UMediaPlayer_Next_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.IsReady
struct UMediaPlayer_IsReady_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.IsPreparing
struct UMediaPlayer_IsPreparing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.IsPlaying
struct UMediaPlayer_IsPlaying_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.IsPaused
struct UMediaPlayer_IsPaused_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.IsLooping
struct UMediaPlayer_IsLooping_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.IsConnecting
struct UMediaPlayer_IsConnecting_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.IsBuffering
struct UMediaPlayer_IsBuffering_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.HasError
struct UMediaPlayer_HasError_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetViewRotation
struct UMediaPlayer_GetViewRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetVideoTrackType
struct UMediaPlayer_GetVideoTrackType_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetVideoTrackFrameRates
struct UMediaPlayer_GetVideoTrackFrameRates_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FFloatRange                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetVideoTrackFrameRate
struct UMediaPlayer_GetVideoTrackFrameRate_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetVideoTrackDimensions
struct UMediaPlayer_GetVideoTrackDimensions_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FIntPoint                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetVideoTrackAspectRatio
struct UMediaPlayer_GetVideoTrackAspectRatio_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetVerticalFieldOfView
struct UMediaPlayer_GetVerticalFieldOfView_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetUrl
struct UMediaPlayer_GetUrl_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetTrackLanguage
struct UMediaPlayer_GetTrackLanguage_Params
{
	EMediaPlayerTrack                                  TrackType;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetTrackFormat
struct UMediaPlayer_GetTrackFormat_Params
{
	EMediaPlayerTrack                                  TrackType;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetTrackDisplayName
struct UMediaPlayer_GetTrackDisplayName_Params
{
	EMediaPlayerTrack                                  TrackType;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetTimeDelay
struct UMediaPlayer_GetTimeDelay_Params
{
	struct FTimespan                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetTime
struct UMediaPlayer_GetTime_Params
{
	struct FTimespan                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetSupportedRates
struct UMediaPlayer_GetSupportedRates_Params
{
	TArray<struct FFloatRange>                         OutRates;                                                 // (Parm, OutParm, ZeroConstructor)
	bool                                               Unthinned;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetSelectedTrack
struct UMediaPlayer_GetSelectedTrack_Params
{
	EMediaPlayerTrack                                  TrackType;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetRate
struct UMediaPlayer_GetRate_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetPlaylistIndex
struct UMediaPlayer_GetPlaylistIndex_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetPlaylist
struct UMediaPlayer_GetPlaylist_Params
{
	class UMediaPlaylist*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetPlayerName
struct UMediaPlayer_GetPlayerName_Params
{
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetNumTracks
struct UMediaPlayer_GetNumTracks_Params
{
	EMediaPlayerTrack                                  TrackType;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetNumTrackFormats
struct UMediaPlayer_GetNumTrackFormats_Params
{
	EMediaPlayerTrack                                  TrackType;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetMediaName
struct UMediaPlayer_GetMediaName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetHorizontalFieldOfView
struct UMediaPlayer_GetHorizontalFieldOfView_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetDuration
struct UMediaPlayer_GetDuration_Params
{
	struct FTimespan                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetDesiredPlayerName
struct UMediaPlayer_GetDesiredPlayerName_Params
{
	struct FName                                       ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetAudioTrackType
struct UMediaPlayer_GetAudioTrackType_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function MediaAssets.MediaPlayer.GetAudioTrackSampleRate
struct UMediaPlayer_GetAudioTrackSampleRate_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.GetAudioTrackChannels
struct UMediaPlayer_GetAudioTrackChannels_Params
{
	int                                                TrackIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                FormatIndex;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.Close
struct UMediaPlayer_Close_Params
{
};

// Function MediaAssets.MediaPlayer.CanPlayUrl
struct UMediaPlayer_CanPlayUrl_Params
{
	class FString                                      URL;                                                      // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.CanPlaySource
struct UMediaPlayer_CanPlaySource_Params
{
	class UMediaSource*                                MediaSource;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlayer.CanPause
struct UMediaPlayer_CanPause_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.Replace
struct UMediaPlaylist_Replace_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UMediaSource*                                Replacement;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.RemoveAt
struct UMediaPlaylist_RemoveAt_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.Remove
struct UMediaPlaylist_Remove_Params
{
	class UMediaSource*                                MediaSource;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.Num
struct UMediaPlaylist_Num_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.Insert
struct UMediaPlaylist_Insert_Params
{
	class UMediaSource*                                MediaSource;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.GetRandom
struct UMediaPlaylist_GetRandom_Params
{
	int                                                OutIndex;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UMediaSource*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.GetPrevious
struct UMediaPlaylist_GetPrevious_Params
{
	int                                                InOutIndex;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UMediaSource*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.GetNext
struct UMediaPlaylist_GetNext_Params
{
	int                                                InOutIndex;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UMediaSource*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.Get
struct UMediaPlaylist_Get_Params
{
	int                                                Index;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UMediaSource*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.AddUrl
struct UMediaPlaylist_AddUrl_Params
{
	class FString                                      URL;                                                      // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.AddFile
struct UMediaPlaylist_AddFile_Params
{
	class FString                                      FilePath;                                                 // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaPlaylist.Add
struct UMediaPlaylist_Add_Params
{
	class UMediaSource*                                MediaSource;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaSoundComponent.SetMediaPlayer
struct UMediaSoundComponent_SetMediaPlayer_Params
{
	class UMediaPlayer*                                NewMediaPlayer;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function MediaAssets.MediaSoundComponent.GetMediaPlayer
struct UMediaSoundComponent_GetMediaPlayer_Params
{
	class UMediaPlayer*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaSoundComponent.BP_GetAttenuationSettingsToApply
struct UMediaSoundComponent_BP_GetAttenuationSettingsToApply_Params
{
	struct FSoundAttenuationSettings                   OutAttenuationSettings;                                   // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaTexture.SetMediaPlayer
struct UMediaTexture_SetMediaPlayer_Params
{
	class UMediaPlayer*                                NewMediaPlayer;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function MediaAssets.MediaTexture.GetWidth
struct UMediaTexture_GetWidth_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaTexture.GetMediaPlayer
struct UMediaTexture_GetMediaPlayer_Params
{
	class UMediaPlayer*                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaTexture.GetHeight
struct UMediaTexture_GetHeight_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function MediaAssets.MediaTexture.GetAspectRatio
struct UMediaTexture_GetAspectRatio_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
