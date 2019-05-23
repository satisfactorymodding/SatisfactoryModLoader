#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_MovieSceneCapture_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class MovieSceneCapture.MovieSceneCaptureProtocolSettings
// 0x0000 (0x0028 - 0x0028)
class UMovieSceneCaptureProtocolSettings : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.MovieSceneCaptureProtocolSettings");
		return ptr;
	}

};


// Class MovieSceneCapture.CompositionGraphCaptureSettings
// 0x0040 (0x0068 - 0x0028)
class UCompositionGraphCaptureSettings : public UMovieSceneCaptureProtocolSettings
{
public:
	struct FCompositionGraphCapturePasses              IncludeRenderPasses;                                      // 0x0028(0x0010) (Edit, BlueprintVisible, Config)
	bool                                               bCaptureFramesInHDR;                                      // 0x0038(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0039(0x0003) MISSED OFFSET
	int                                                HDRCompressionQuality;                                    // 0x003C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	TEnumAsByte<EHDRCaptureGamut>                      CaptureGamut;                                             // 0x0040(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0041(0x0007) MISSED OFFSET
	struct FSoftObjectPath                             PostProcessingMaterial;                                   // 0x0048(0x0018) (Edit, BlueprintVisible, Config)
	bool                                               bDisableScreenPercentage;                                 // 0x0060(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0061(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.CompositionGraphCaptureSettings");
		return ptr;
	}

};


// Class MovieSceneCapture.FrameGrabberProtocolSettings
// 0x0008 (0x0030 - 0x0028)
class UFrameGrabberProtocolSettings : public UMovieSceneCaptureProtocolSettings
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.FrameGrabberProtocolSettings");
		return ptr;
	}

};


// Class MovieSceneCapture.BmpImageCaptureSettings
// 0x0000 (0x0028 - 0x0028)
class UBmpImageCaptureSettings : public UMovieSceneCaptureProtocolSettings
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.BmpImageCaptureSettings");
		return ptr;
	}

};


// Class MovieSceneCapture.ImageCaptureSettings
// 0x0008 (0x0038 - 0x0030)
class UImageCaptureSettings : public UFrameGrabberProtocolSettings
{
public:
	int                                                CompressionQuality;                                       // 0x0030(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0034(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.ImageCaptureSettings");
		return ptr;
	}

};


// Class MovieSceneCapture.MovieSceneCaptureInterface
// 0x0000 (0x0028 - 0x0028)
class UMovieSceneCaptureInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.MovieSceneCaptureInterface");
		return ptr;
	}

};


// Class MovieSceneCapture.MovieSceneCapture
// 0x01B0 (0x01D8 - 0x0028)
class UMovieSceneCapture : public UObject
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0028(0x0010) MISSED OFFSET
	struct FCaptureProtocolID                          CaptureType;                                              // 0x0038(0x0008) (Edit, BlueprintVisible, Config)
	class UMovieSceneCaptureProtocolSettings*          ProtocolSettings;                                         // 0x0040(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FMovieSceneCaptureSettings                  Settings;                                                 // 0x0048(0x0050) (Edit, BlueprintVisible, Config)
	bool                                               bUseSeparateProcess;                                      // 0x0098(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bCloseEditorWhenCaptureStarts;                            // 0x0099(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x009A(0x0006) MISSED OFFSET
	class FString                                      AdditionalCommandLineArguments;                           // 0x00A0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, Config)
	class FString                                      InheritedCommandLineArguments;                            // 0x00B0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, Transient)
	unsigned char                                      UnknownData02[0x118];                                     // 0x00C0(0x0118) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.MovieSceneCapture");
		return ptr;
	}

};


// Class MovieSceneCapture.LevelCapture
// 0x0020 (0x01F8 - 0x01D8)
class ULevelCapture : public UMovieSceneCapture
{
public:
	bool                                               bAutoStartCapture;                                        // 0x01D8(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0xB];                                       // 0x01D9(0x000B) MISSED OFFSET
	struct FGuid                                       PrerequisiteActorId;                                      // 0x01E4(0x0010) (IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x01F4(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.LevelCapture");
		return ptr;
	}

};


// Class MovieSceneCapture.MovieSceneCaptureEnvironment
// 0x0000 (0x0028 - 0x0028)
class UMovieSceneCaptureEnvironment : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.MovieSceneCaptureEnvironment");
		return ptr;
	}


	int GetCaptureFrameNumber();
	float GetCaptureElapsedTime();
};


// Class MovieSceneCapture.VideoCaptureSettings
// 0x0018 (0x0048 - 0x0030)
class UVideoCaptureSettings : public UFrameGrabberProtocolSettings
{
public:
	bool                                               bUseCompression;                                          // 0x0030(0x0001) (Edit, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0031(0x0003) MISSED OFFSET
	float                                              CompressionQuality;                                       // 0x0034(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData)
	class FString                                      VideoCodec;                                               // 0x0038(0x0010) (Edit, ZeroConstructor, Config)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneCapture.VideoCaptureSettings");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
