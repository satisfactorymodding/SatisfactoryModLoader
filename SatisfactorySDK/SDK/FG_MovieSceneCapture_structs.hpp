#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_ImageWriteQueue_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum MovieSceneCapture.EHDRCaptureGamut
enum class EHDRCaptureGamut : uint8_t
{
	HCGM_Rec709                    = 0,
	HCGM_P3DCI                     = 1,
	HCGM_Rec2020                   = 2,
	HCGM_ACES                      = 3,
	HCGM_ACEScg                    = 4,
	HCGM_Linear                    = 5,
	HCGM_MAX                       = 6
};


// Enum MovieSceneCapture.EMovieSceneCaptureProtocolState
enum class EMovieSceneCaptureProtocolState : uint8_t
{
	Idle                           = 0,
	Initialized                    = 1,
	Capturing                      = 2,
	Finalizing                     = 3,
	EMovieSceneCaptureProtocolState_MAX = 4
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct MovieSceneCapture.CompositionGraphCapturePasses
// 0x0010
struct FCompositionGraphCapturePasses
{
	TArray<class FString>                              Value;                                                    // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
};

// ScriptStruct MovieSceneCapture.CaptureResolution
// 0x0008
struct FCaptureResolution
{
	int                                                ResX;                                                     // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	int                                                ResY;                                                     // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
};

// ScriptStruct MovieSceneCapture.MovieSceneCaptureSettings
// 0x0050
struct FMovieSceneCaptureSettings
{
	struct FDirectoryPath                              OutputDirectory;                                          // 0x0000(0x0010) (Edit, BlueprintVisible, Config)
	class UClass*                                      GameModeOverride;                                         // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	class FString                                      OutputFormat;                                             // 0x0018(0x0010) (Edit, BlueprintVisible, ZeroConstructor, Config)
	bool                                               bOverwriteExisting;                                       // 0x0028(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bUseRelativeFrameNumbers;                                 // 0x0029(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x002A(0x0002) MISSED OFFSET
	int                                                HandleFrames;                                             // 0x002C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      ZeroPadFrameNumbers;                                      // 0x0030(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0031(0x0003) MISSED OFFSET
	struct FFrameRate                                  FrameRate;                                                // 0x0034(0x0008) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	struct FCaptureResolution                          Resolution;                                               // 0x003C(0x0008) (Edit, BlueprintVisible, Config)
	bool                                               bEnableTextureStreaming;                                  // 0x0044(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bCinematicEngineScalability;                              // 0x0045(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bCinematicMode;                                           // 0x0046(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bAllowMovement;                                           // 0x0047(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bAllowTurning;                                            // 0x0048(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bShowPlayer;                                              // 0x0049(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bShowHUD;                                                 // 0x004A(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData02[0x5];                                       // 0x004B(0x0005) MISSED OFFSET
};

// ScriptStruct MovieSceneCapture.FrameMetrics
// 0x0010
struct FFrameMetrics
{
	float                                              TotalElapsedTime;                                         // 0x0000(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              FrameDelta;                                               // 0x0004(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                FrameNumber;                                              // 0x0008(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                NumDroppedFrames;                                         // 0x000C(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieSceneCapture.CapturedPixels
// 0x0010
struct FCapturedPixels
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x0000(0x0010) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
