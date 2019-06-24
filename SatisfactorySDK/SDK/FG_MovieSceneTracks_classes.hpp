#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_MovieSceneTracks_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class MovieSceneTracks.MovieScenePropertyTrack
// 0x0028 (0x0080 - 0x0058)
class UMovieScenePropertyTrack : public UMovieSceneNameableTrack
{
public:
	struct FName                                       PropertyName;                                             // 0x0058(0x0008) (ZeroConstructor, IsPlainOldData)
	class FString                                      PropertyPath;                                             // 0x0060(0x0010) (ZeroConstructor)
	TArray<class UMovieSceneSection*>                  Sections;                                                 // 0x0070(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScenePropertyTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneTransformOrigin
// 0x0000 (0x0028 - 0x0028)
class UMovieSceneTransformOrigin : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneTransformOrigin");
		return ptr;
	}


	struct FTransform BP_GetTransformOrigin();
};


// Class MovieSceneTracks.MovieScene3DConstraintSection
// 0x0028 (0x0108 - 0x00E0)
class UMovieScene3DConstraintSection : public UMovieSceneSection
{
public:
	struct FGuid                                       ConstraintId;                                             // 0x00E0(0x0010) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FMovieSceneObjectBindingID                  ConstraintBindingID;                                      // 0x00F0(0x0018) (Edit)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScene3DConstraintSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieScene3DAttachSection
// 0x0018 (0x0120 - 0x0108)
class UMovieScene3DAttachSection : public UMovieScene3DConstraintSection
{
public:
	struct FName                                       AttachSocketName;                                         // 0x0108(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FName                                       AttachComponentName;                                      // 0x0110(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	EAttachmentRule                                    AttachmentLocationRule;                                   // 0x0118(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EAttachmentRule                                    AttachmentRotationRule;                                   // 0x0119(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EAttachmentRule                                    AttachmentScaleRule;                                      // 0x011A(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EDetachmentRule                                    DetachmentLocationRule;                                   // 0x011B(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EDetachmentRule                                    DetachmentRotationRule;                                   // 0x011C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EDetachmentRule                                    DetachmentScaleRule;                                      // 0x011D(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x011E(0x0002) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScene3DAttachSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieScene3DConstraintTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieScene3DConstraintTrack : public UMovieSceneTrack
{
public:
	TArray<class UMovieSceneSection*>                  ConstraintSections;                                       // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScene3DConstraintTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieScene3DAttachTrack
// 0x0000 (0x0068 - 0x0068)
class UMovieScene3DAttachTrack : public UMovieScene3DConstraintTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScene3DAttachTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieScene3DPathSection
// 0x00A8 (0x01B0 - 0x0108)
class UMovieScene3DPathSection : public UMovieScene3DConstraintSection
{
public:
	struct FMovieSceneFloatChannel                     TimingCurve;                                              // 0x0108(0x00A0)
	EMovieScene3DPathSection_Axis                      FrontAxisEnum;                                            // 0x01A8(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EMovieScene3DPathSection_Axis                      UpAxisEnum;                                               // 0x01A9(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x01AA(0x0002) MISSED OFFSET
	unsigned char                                      bFollow : 1;                                              // 0x01AC(0x0001) (Edit)
	unsigned char                                      bReverse : 1;                                             // 0x01AC(0x0001) (Edit)
	unsigned char                                      bForceUpright : 1;                                        // 0x01AC(0x0001) (Edit)
	unsigned char                                      UnknownData01[0x3];                                       // 0x01AD(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScene3DPathSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieScene3DPathTrack
// 0x0000 (0x0068 - 0x0068)
class UMovieScene3DPathTrack : public UMovieScene3DConstraintTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScene3DPathTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieScene3DTransformSection
// 0x0650 (0x0730 - 0x00E0)
class UMovieScene3DTransformSection : public UMovieSceneSection
{
public:
	struct FMovieSceneTransformMask                    TransformMask;                                            // 0x00E0(0x0004)
	unsigned char                                      UnknownData00[0x4];                                       // 0x00E4(0x0004) MISSED OFFSET
	struct FMovieSceneFloatChannel                     Translation[0x3];                                         // 0x00E8(0x00A0)
	struct FMovieSceneFloatChannel                     Rotation[0x3];                                            // 0x02C8(0x00A0)
	struct FMovieSceneFloatChannel                     Scale[0x3];                                               // 0x04A8(0x00A0)
	struct FMovieSceneFloatChannel                     ManualWeight;                                             // 0x0688(0x00A0)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0728(0x0004) MISSED OFFSET
	bool                                               bUseQuaternionInterpolation;                              // 0x072C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x072D(0x0003) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScene3DTransformSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieScene3DTransformTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieScene3DTransformTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieScene3DTransformTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneActorReferenceSection
// 0x0120 (0x0200 - 0x00E0)
class UMovieSceneActorReferenceSection : public UMovieSceneSection
{
public:
	struct FMovieSceneActorReferenceData               ActorReferenceData;                                       // 0x00E0(0x00A0)
	struct FIntegralCurve                              ActorGuidIndexCurve;                                      // 0x0180(0x0070) (Deprecated)
	TArray<class FString>                              ActorGuidStrings;                                         // 0x01F0(0x0010) (ZeroConstructor, Deprecated)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneActorReferenceSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneActorReferenceTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneActorReferenceTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneActorReferenceTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneAudioSection
// 0x0198 (0x0278 - 0x00E0)
class UMovieSceneAudioSection : public UMovieSceneSection
{
public:
	class USoundBase*                                  Sound;                                                    // 0x00E0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              StartOffset;                                              // 0x00E8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              AudioStartTime;                                           // 0x00EC(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              AudioDilationFactor;                                      // 0x00F0(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              AudioVolume;                                              // 0x00F4(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FMovieSceneFloatChannel                     SoundVolume;                                              // 0x00F8(0x00A0)
	struct FMovieSceneFloatChannel                     PitchMultiplier;                                          // 0x0198(0x00A0)
	bool                                               bSuppressSubtitles;                                       // 0x0238(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bOverrideAttenuation;                                     // 0x0239(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x023A(0x0006) MISSED OFFSET
	class USoundAttenuation*                           AttenuationSettings;                                      // 0x0240(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FScriptDelegate                             OnQueueSubtitles;                                         // 0x0248(0x0014) (ZeroConstructor, InstancedReference)
	struct FScriptMulticastDelegate                    OnAudioFinished;                                          // 0x0258(0x0010) (ZeroConstructor, InstancedReference)
	struct FScriptMulticastDelegate                    OnAudioPlaybackPercent;                                   // 0x0268(0x0010) (ZeroConstructor, InstancedReference)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneAudioSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneAudioTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneAudioTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  AudioSections;                                            // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneAudioTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneBoolSection
// 0x0098 (0x0178 - 0x00E0)
class UMovieSceneBoolSection : public UMovieSceneSection
{
public:
	bool                                               DefaultValue;                                             // 0x00E0(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00E1(0x0007) MISSED OFFSET
	struct FMovieSceneBoolChannel                      BoolCurve;                                                // 0x00E8(0x0090)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneBoolSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneBoolTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneBoolTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneBoolTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneByteSection
// 0x0098 (0x0178 - 0x00E0)
class UMovieSceneByteSection : public UMovieSceneSection
{
public:
	struct FMovieSceneByteChannel                      ByteCurve;                                                // 0x00E0(0x0098)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneByteSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneByteTrack
// 0x0008 (0x0088 - 0x0080)
class UMovieSceneByteTrack : public UMovieScenePropertyTrack
{
public:
	class UEnum*                                       Enum;                                                     // 0x0080(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneByteTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneCameraAnimSection
// 0x0040 (0x0120 - 0x00E0)
class UMovieSceneCameraAnimSection : public UMovieSceneSection
{
public:
	struct FMovieSceneCameraAnimSectionData            AnimData;                                                 // 0x00E0(0x0020) (Edit)
	class UCameraAnim*                                 CameraAnim;                                               // 0x0100(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              PlayRate;                                                 // 0x0108(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              PlayScale;                                                // 0x010C(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              BlendInTime;                                              // 0x0110(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              BlendOutTime;                                             // 0x0114(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	bool                                               bLooping;                                                 // 0x0118(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0119(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneCameraAnimSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneCameraAnimTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneCameraAnimTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  CameraAnimSections;                                       // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneCameraAnimTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneCameraCutSection
// 0x0028 (0x0108 - 0x00E0)
class UMovieSceneCameraCutSection : public UMovieSceneSection
{
public:
	struct FGuid                                       CameraGuid;                                               // 0x00E0(0x0010) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FMovieSceneObjectBindingID                  CameraBindingID;                                          // 0x00F0(0x0018) (Edit)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneCameraCutSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneCameraCutTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneCameraCutTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  Sections;                                                 // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneCameraCutTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneCameraShakeSection
// 0x0040 (0x0120 - 0x00E0)
class UMovieSceneCameraShakeSection : public UMovieSceneSection
{
public:
	struct FMovieSceneCameraShakeSectionData           ShakeData;                                                // 0x00E0(0x0020) (Edit)
	class UClass*                                      ShakeClass;                                               // 0x0100(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              PlayScale;                                                // 0x0108(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	TEnumAsByte<ECameraAnimPlaySpace>                  PlaySpace;                                                // 0x010C(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x010D(0x0003) MISSED OFFSET
	struct FRotator                                    UserDefinedPlaySpace;                                     // 0x0110(0x000C) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x011C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneCameraShakeSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneCameraShakeTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneCameraShakeTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  CameraShakeSections;                                      // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneCameraShakeTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneCinematicShotSection
// 0x0028 (0x0178 - 0x0150)
class UMovieSceneCinematicShotSection : public UMovieSceneSubSection
{
public:
	class FString                                      ShotDisplayName;                                          // 0x0150(0x0010) (ZeroConstructor)
	struct FText                                       DisplayName;                                              // 0x0160(0x0028) (Deprecated)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneCinematicShotSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneCinematicShotTrack
// 0x0000 (0x0068 - 0x0068)
class UMovieSceneCinematicShotTrack : public UMovieSceneSubTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneCinematicShotTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneColorSection
// 0x0280 (0x0360 - 0x00E0)
class UMovieSceneColorSection : public UMovieSceneSection
{
public:
	struct FMovieSceneFloatChannel                     RedCurve;                                                 // 0x00E0(0x00A0)
	struct FMovieSceneFloatChannel                     GreenCurve;                                               // 0x0180(0x00A0)
	struct FMovieSceneFloatChannel                     BlueCurve;                                                // 0x0220(0x00A0)
	struct FMovieSceneFloatChannel                     AlphaCurve;                                               // 0x02C0(0x00A0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneColorSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneColorTrack
// 0x0008 (0x0088 - 0x0080)
class UMovieSceneColorTrack : public UMovieScenePropertyTrack
{
public:
	bool                                               bIsSlateColor;                                            // 0x0080(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0081(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneColorTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneEnumSection
// 0x0098 (0x0178 - 0x00E0)
class UMovieSceneEnumSection : public UMovieSceneSection
{
public:
	struct FMovieSceneByteChannel                      EnumCurve;                                                // 0x00E0(0x0098)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneEnumSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneEnumTrack
// 0x0008 (0x0088 - 0x0080)
class UMovieSceneEnumTrack : public UMovieScenePropertyTrack
{
public:
	class UEnum*                                       Enum;                                                     // 0x0080(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneEnumTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneEulerTransformTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneEulerTransformTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneEulerTransformTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneEventSectionBase
// 0x0000 (0x00E0 - 0x00E0)
class UMovieSceneEventSectionBase : public UMovieSceneSection
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneEventSectionBase");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneEventRepeaterSection
// 0x0008 (0x00E8 - 0x00E0)
class UMovieSceneEventRepeaterSection : public UMovieSceneEventSectionBase
{
public:
	struct FMovieSceneEvent                            Event;                                                    // 0x00E0(0x0008) (Edit)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneEventRepeaterSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneEventSection
// 0x00F0 (0x01D0 - 0x00E0)
class UMovieSceneEventSection : public UMovieSceneSection
{
public:
	struct FNameCurve                                  Events;                                                   // 0x00E0(0x0068) (Deprecated)
	struct FMovieSceneEventSectionData                 EventData;                                                // 0x0148(0x0088)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneEventSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneEventTrack
// 0x0028 (0x0080 - 0x0058)
class UMovieSceneEventTrack : public UMovieSceneNameableTrack
{
public:
	unsigned char                                      bFireEventsWhenForwards : 1;                              // 0x0058(0x0001) (Edit)
	unsigned char                                      bFireEventsWhenBackwards : 1;                             // 0x0058(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0059(0x0003) MISSED OFFSET
	EFireEventsAtPosition                              EventPosition;                                            // 0x005C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x005D(0x0003) MISSED OFFSET
	TArray<struct FMovieSceneObjectBindingID>          EventReceivers;                                           // 0x0060(0x0010) (Edit, ZeroConstructor)
	TArray<class UMovieSceneSection*>                  Sections;                                                 // 0x0070(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneEventTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneEventTriggerSection
// 0x0088 (0x0168 - 0x00E0)
class UMovieSceneEventTriggerSection : public UMovieSceneEventSectionBase
{
public:
	struct FMovieSceneEventChannel                     EventChannel;                                             // 0x00E0(0x0088)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneEventTriggerSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneFloatSection
// 0x00A0 (0x0180 - 0x00E0)
class UMovieSceneFloatSection : public UMovieSceneSection
{
public:
	struct FMovieSceneFloatChannel                     FloatCurve;                                               // 0x00E0(0x00A0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneFloatSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneFadeSection
// 0x0018 (0x0198 - 0x0180)
class UMovieSceneFadeSection : public UMovieSceneFloatSection
{
public:
	struct FLinearColor                                FadeColor;                                                // 0x0180(0x0010) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bFadeAudio : 1;                                           // 0x0190(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0191(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneFadeSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneFloatTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneFloatTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneFloatTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneFadeTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneFadeTrack : public UMovieSceneFloatTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneFadeTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneIntegerSection
// 0x0090 (0x0170 - 0x00E0)
class UMovieSceneIntegerSection : public UMovieSceneSection
{
public:
	struct FMovieSceneIntegerChannel                   IntegerCurve;                                             // 0x00E0(0x0090)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneIntegerSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneIntegerTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneIntegerTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneIntegerTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneLevelVisibilitySection
// 0x0018 (0x00F8 - 0x00E0)
class UMovieSceneLevelVisibilitySection : public UMovieSceneSection
{
public:
	ELevelVisibility                                   Visibility;                                               // 0x00E0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00E1(0x0007) MISSED OFFSET
	TArray<struct FName>                               LevelNames;                                               // 0x00E8(0x0010) (Edit, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneLevelVisibilitySection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneLevelVisibilityTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneLevelVisibilityTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  Sections;                                                 // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneLevelVisibilityTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneMaterialTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneMaterialTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  Sections;                                                 // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneMaterialTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneMaterialParameterCollectionTrack
// 0x0008 (0x0070 - 0x0068)
class UMovieSceneMaterialParameterCollectionTrack : public UMovieSceneMaterialTrack
{
public:
	class UMaterialParameterCollection*                MPC;                                                      // 0x0068(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneMaterialParameterCollectionTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneComponentMaterialTrack
// 0x0008 (0x0070 - 0x0068)
class UMovieSceneComponentMaterialTrack : public UMovieSceneMaterialTrack
{
public:
	int                                                MaterialIndex;                                            // 0x0068(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x006C(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneComponentMaterialTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneParameterSection
// 0x0030 (0x0110 - 0x00E0)
class UMovieSceneParameterSection : public UMovieSceneSection
{
public:
	TArray<struct FScalarParameterNameAndCurve>        ScalarParameterNamesAndCurves;                            // 0x00E0(0x0010) (ZeroConstructor)
	TArray<struct FVectorParameterNameAndCurves>       VectorParameterNamesAndCurves;                            // 0x00F0(0x0010) (ZeroConstructor)
	TArray<struct FColorParameterNameAndCurves>        ColorParameterNamesAndCurves;                             // 0x0100(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneParameterSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneParticleParameterTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneParticleParameterTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  Sections;                                                 // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneParticleParameterTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneParticleSection
// 0x0098 (0x0178 - 0x00E0)
class UMovieSceneParticleSection : public UMovieSceneSection
{
public:
	struct FMovieSceneParticleChannel                  ParticleKeys;                                             // 0x00E0(0x0098)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneParticleSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneParticleTrack
// 0x0010 (0x0068 - 0x0058)
class UMovieSceneParticleTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  ParticleSections;                                         // 0x0058(0x0010) (ExportObject, ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneParticleTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneSkeletalAnimationSection
// 0x00F0 (0x01D0 - 0x00E0)
class UMovieSceneSkeletalAnimationSection : public UMovieSceneSection
{
public:
	struct FMovieSceneSkeletalAnimationParams          Params;                                                   // 0x00E0(0x00C8) (Edit)
	class UAnimSequence*                               AnimSequence;                                             // 0x01A8(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	class UAnimSequenceBase*                           Animation;                                                // 0x01B0(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              StartOffset;                                              // 0x01B8(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              EndOffset;                                                // 0x01BC(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              PlayRate;                                                 // 0x01C0(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      bReverse : 1;                                             // 0x01C4(0x0001) (Deprecated)
	unsigned char                                      UnknownData00[0x3];                                       // 0x01C5(0x0003) MISSED OFFSET
	struct FName                                       SlotName;                                                 // 0x01C8(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneSkeletalAnimationSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneSkeletalAnimationTrack
// 0x0018 (0x0070 - 0x0058)
class UMovieSceneSkeletalAnimationTrack : public UMovieSceneNameableTrack
{
public:
	TArray<class UMovieSceneSection*>                  AnimationSections;                                        // 0x0058(0x0010) (ExportObject, ZeroConstructor)
	bool                                               bUseLegacySectionIndexBlend;                              // 0x0068(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0069(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneSkeletalAnimationTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneSlomoSection
// 0x0000 (0x0180 - 0x0180)
class UMovieSceneSlomoSection : public UMovieSceneFloatSection
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneSlomoSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneSlomoTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneSlomoTrack : public UMovieSceneFloatTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneSlomoTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneSpawnSection
// 0x0000 (0x0178 - 0x0178)
class UMovieSceneSpawnSection : public UMovieSceneBoolSection
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneSpawnSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneSpawnTrack
// 0x0020 (0x0078 - 0x0058)
class UMovieSceneSpawnTrack : public UMovieSceneTrack
{
public:
	TArray<class UMovieSceneSection*>                  Sections;                                                 // 0x0058(0x0010) (ExportObject, ZeroConstructor)
	struct FGuid                                       ObjectGuid;                                               // 0x0068(0x0010) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneSpawnTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneStringSection
// 0x00A0 (0x0180 - 0x00E0)
class UMovieSceneStringSection : public UMovieSceneSection
{
public:
	struct FMovieSceneStringChannel                    StringCurve;                                              // 0x00E0(0x00A0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneStringSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneStringTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneStringTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneStringTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneTransformTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneTransformTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneTransformTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneVectorSection
// 0x0288 (0x0368 - 0x00E0)
class UMovieSceneVectorSection : public UMovieSceneSection
{
public:
	struct FMovieSceneFloatChannel                     Curves[0x4];                                              // 0x00E0(0x00A0)
	int                                                ChannelsUsed;                                             // 0x0360(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0364(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneVectorSection");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneVectorTrack
// 0x0008 (0x0088 - 0x0080)
class UMovieSceneVectorTrack : public UMovieScenePropertyTrack
{
public:
	int                                                NumChannelsUsed;                                          // 0x0080(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0084(0x0004) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneVectorTrack");
		return ptr;
	}

};


// Class MovieSceneTracks.MovieSceneVisibilityTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneVisibilityTrack : public UMovieSceneBoolTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class MovieSceneTracks.MovieSceneVisibilityTrack");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
