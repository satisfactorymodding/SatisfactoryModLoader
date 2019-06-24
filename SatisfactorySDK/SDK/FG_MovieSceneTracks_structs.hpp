#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_MovieScene_classes.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum MovieSceneTracks.MovieScene3DPathSection_Axis
enum class EMovieScene3DPathSection_Axis : uint8_t
{
	X                              = 0,
	Y                              = 1,
	Z                              = 2,
	NEG_X                          = 3,
	NEG_Y                          = 4,
	NEG_Z                          = 5,
	MovieScene3DPathSection_MAX    = 6
};


// Enum MovieSceneTracks.EFireEventsAtPosition
enum class EFireEventsAtPosition : uint8_t
{
	AtStartOfEvaluation            = 0,
	AtEndOfEvaluation              = 1,
	AfterSpawn                     = 2,
	EFireEventsAtPosition_MAX      = 3
};


// Enum MovieSceneTracks.ELevelVisibility
enum class ELevelVisibility : uint8_t
{
	Visible                        = 0,
	Hidden                         = 1,
	ELevelVisibility_MAX           = 2
};


// Enum MovieSceneTracks.EParticleKey
enum class EParticleKey : uint8_t
{
	Activate                       = 0,
	Deactivate                     = 1,
	Trigger                        = 2,
	EParticleKey_MAX               = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct MovieSceneTracks.MovieSceneTransformMask
// 0x0004
struct FMovieSceneTransformMask
{
	uint32_t                                           Mask;                                                     // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieSceneTracks.MovieSceneActorReferenceKey
// 0x0018
struct FMovieSceneActorReferenceKey
{
	struct FMovieSceneObjectBindingID                  Object;                                                   // 0x0000(0x0018) (Edit)
};

// ScriptStruct MovieSceneTracks.MovieSceneActorReferenceData
// 0x0098 (0x00A0 - 0x0008)
struct FMovieSceneActorReferenceData : public FMovieSceneChannel
{
	TArray<struct FFrameNumber>                        KeyTimes;                                                 // 0x0008(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0018(0x0018) MISSED OFFSET
	TArray<struct FMovieSceneActorReferenceKey>        KeyValues;                                                // 0x0030(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x60];                                      // 0x0040(0x0060) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneCameraAnimSectionData
// 0x0020
struct FMovieSceneCameraAnimSectionData
{
	class UCameraAnim*                                 CameraAnim;                                               // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PlayRate;                                                 // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PlayScale;                                                // 0x000C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              BlendInTime;                                              // 0x0010(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              BlendOutTime;                                             // 0x0014(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bLooping;                                                 // 0x0018(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0019(0x0007) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneCameraShakeSectionData
// 0x0020
struct FMovieSceneCameraShakeSectionData
{
	class UClass*                                      ShakeClass;                                               // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PlayScale;                                                // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ECameraAnimPlaySpace>                  PlaySpace;                                                // 0x000C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x000D(0x0003) MISSED OFFSET
	struct FRotator                                    UserDefinedPlaySpace;                                     // 0x0010(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneEvent
// 0x0008
struct FMovieSceneEvent
{
	struct FName                                       FunctionName;                                             // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieSceneTracks.MovieSceneEventParameters
// 0x0028
struct FMovieSceneEventParameters
{
	unsigned char                                      UnknownData00[0x28];                                      // 0x0000(0x0028) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.EventPayload
// 0x0030
struct FEventPayload
{
	struct FName                                       EventName;                                                // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FMovieSceneEventParameters                  Parameters;                                               // 0x0008(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly)
};

// ScriptStruct MovieSceneTracks.MovieSceneEventSectionData
// 0x0080 (0x0088 - 0x0008)
struct FMovieSceneEventSectionData : public FMovieSceneChannel
{
	TArray<struct FFrameNumber>                        Times;                                                    // 0x0008(0x0010) (ZeroConstructor)
	TArray<struct FEventPayload>                       KeyValues;                                                // 0x0018(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x60];                                      // 0x0028(0x0060) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneEventChannel
// 0x0080 (0x0088 - 0x0008)
struct FMovieSceneEventChannel : public FMovieSceneChannel
{
	TArray<struct FFrameNumber>                        KeyTimes;                                                 // 0x0008(0x0010) (ZeroConstructor)
	TArray<struct FMovieSceneEvent>                    KeyValues;                                                // 0x0018(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x60];                                      // 0x0028(0x0060) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.ScalarParameterNameAndCurve
// 0x00A8
struct FScalarParameterNameAndCurve
{
	struct FName                                       ParameterName;                                            // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FMovieSceneFloatChannel                     ParameterCurve;                                           // 0x0008(0x00A0)
};

// ScriptStruct MovieSceneTracks.VectorParameterNameAndCurves
// 0x01E8
struct FVectorParameterNameAndCurves
{
	struct FName                                       ParameterName;                                            // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FMovieSceneFloatChannel                     XCurve;                                                   // 0x0008(0x00A0)
	struct FMovieSceneFloatChannel                     YCurve;                                                   // 0x00A8(0x00A0)
	struct FMovieSceneFloatChannel                     ZCurve;                                                   // 0x0148(0x00A0)
};

// ScriptStruct MovieSceneTracks.ColorParameterNameAndCurves
// 0x0288
struct FColorParameterNameAndCurves
{
	struct FName                                       ParameterName;                                            // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FMovieSceneFloatChannel                     RedCurve;                                                 // 0x0008(0x00A0)
	struct FMovieSceneFloatChannel                     GreenCurve;                                               // 0x00A8(0x00A0)
	struct FMovieSceneFloatChannel                     BlueCurve;                                                // 0x0148(0x00A0)
	struct FMovieSceneFloatChannel                     AlphaCurve;                                               // 0x01E8(0x00A0)
};

// ScriptStruct MovieSceneTracks.MovieSceneParticleChannel
// 0x0000 (0x0098 - 0x0098)
struct FMovieSceneParticleChannel : public FMovieSceneByteChannel
{

};

// ScriptStruct MovieSceneTracks.MovieSceneSkeletalAnimationParams
// 0x00C8
struct FMovieSceneSkeletalAnimationParams
{
	class UAnimSequenceBase*                           Animation;                                                // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              StartOffset;                                              // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              EndOffset;                                                // 0x000C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              PlayRate;                                                 // 0x0010(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bReverse : 1;                                             // 0x0014(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0015(0x0003) MISSED OFFSET
	struct FName                                       SlotName;                                                 // 0x0018(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FMovieSceneFloatChannel                     Weight;                                                   // 0x0020(0x00A0)
	bool                                               bSkipAnimNotifiers;                                       // 0x00C0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x00C1(0x0007) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneStringChannel
// 0x0098 (0x00A0 - 0x0008)
struct FMovieSceneStringChannel : public FMovieSceneChannel
{
	TArray<struct FFrameNumber>                        Times;                                                    // 0x0008(0x0010) (ZeroConstructor)
	TArray<class FString>                              Values;                                                   // 0x0018(0x0010) (ZeroConstructor)
	class FString                                      DefaultValue;                                             // 0x0028(0x0010) (ZeroConstructor)
	bool                                               bHasDefaultValue;                                         // 0x0038(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x67];                                      // 0x0039(0x0067) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieScene3DAttachSectionTemplate
// 0x0030 (0x0050 - 0x0020)
struct FMovieScene3DAttachSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneObjectBindingID                  AttachBindingID;                                          // 0x0020(0x0018)
	struct FName                                       AttachSocketName;                                         // 0x0038(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FName                                       AttachComponentName;                                      // 0x0040(0x0008) (ZeroConstructor, IsPlainOldData)
	EAttachmentRule                                    AttachmentLocationRule;                                   // 0x0048(0x0001) (ZeroConstructor, IsPlainOldData)
	EAttachmentRule                                    AttachmentRotationRule;                                   // 0x0049(0x0001) (ZeroConstructor, IsPlainOldData)
	EAttachmentRule                                    AttachmentScaleRule;                                      // 0x004A(0x0001) (ZeroConstructor, IsPlainOldData)
	EDetachmentRule                                    DetachmentLocationRule;                                   // 0x004B(0x0001) (ZeroConstructor, IsPlainOldData)
	EDetachmentRule                                    DetachmentRotationRule;                                   // 0x004C(0x0001) (ZeroConstructor, IsPlainOldData)
	EDetachmentRule                                    DetachmentScaleRule;                                      // 0x004D(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x004E(0x0002) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieScene3DPathSectionTemplate
// 0x00C0 (0x00E0 - 0x0020)
struct FMovieScene3DPathSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneObjectBindingID                  PathBindingID;                                            // 0x0020(0x0018)
	struct FMovieSceneFloatChannel                     TimingCurve;                                              // 0x0038(0x00A0)
	EMovieScene3DPathSection_Axis                      FrontAxisEnum;                                            // 0x00D8(0x0001) (ZeroConstructor, IsPlainOldData)
	EMovieScene3DPathSection_Axis                      UpAxisEnum;                                               // 0x00D9(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x00DA(0x0002) MISSED OFFSET
	unsigned char                                      bFollow : 1;                                              // 0x00DC(0x0001)
	unsigned char                                      bReverse : 1;                                             // 0x00DC(0x0001)
	unsigned char                                      bForceUpright : 1;                                        // 0x00DC(0x0001)
	unsigned char                                      UnknownData01[0x3];                                       // 0x00DD(0x0003) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieScene3DTransformKeyStruct
// 0x0040 (0x0048 - 0x0008)
struct FMovieScene3DTransformKeyStruct : public FMovieSceneKeyStruct
{
	struct FVector                                     Location;                                                 // 0x0008(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    Rotation;                                                 // 0x0014(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Scale;                                                    // 0x0020(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFrameNumber                                Time;                                                     // 0x002C(0x0004) (Edit)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0030(0x0018) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieScene3DScaleKeyStruct
// 0x0028 (0x0030 - 0x0008)
struct FMovieScene3DScaleKeyStruct : public FMovieSceneKeyStruct
{
	struct FVector                                     Scale;                                                    // 0x0008(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFrameNumber                                Time;                                                     // 0x0014(0x0004) (Edit)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0018(0x0018) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieScene3DRotationKeyStruct
// 0x0028 (0x0030 - 0x0008)
struct FMovieScene3DRotationKeyStruct : public FMovieSceneKeyStruct
{
	struct FRotator                                    Rotation;                                                 // 0x0008(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFrameNumber                                Time;                                                     // 0x0014(0x0004) (Edit)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0018(0x0018) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieScene3DLocationKeyStruct
// 0x0028 (0x0030 - 0x0008)
struct FMovieScene3DLocationKeyStruct : public FMovieSceneKeyStruct
{
	struct FVector                                     Location;                                                 // 0x0008(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFrameNumber                                Time;                                                     // 0x0014(0x0004) (Edit)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0018(0x0018) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieScene3DTransformTemplateData
// 0x0650
struct FMovieScene3DTransformTemplateData
{
	struct FMovieSceneFloatChannel                     TranslationCurve[0x3];                                    // 0x0000(0x00A0)
	struct FMovieSceneFloatChannel                     RotationCurve[0x3];                                       // 0x01E0(0x00A0)
	struct FMovieSceneFloatChannel                     ScaleCurve[0x3];                                          // 0x03C0(0x00A0)
	struct FMovieSceneFloatChannel                     ManualWeight;                                             // 0x05A0(0x00A0)
	EMovieSceneBlendType                               BlendType;                                                // 0x0640(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0641(0x0003) MISSED OFFSET
	struct FMovieSceneTransformMask                    Mask;                                                     // 0x0644(0x0004)
	bool                                               bUseQuaternionInterpolation;                              // 0x0648(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0649(0x0007) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneComponentTransformSectionTemplate
// 0x0650 (0x0670 - 0x0020)
struct FMovieSceneComponentTransformSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieScene3DTransformTemplateData          TemplateData;                                             // 0x0020(0x0650)
};

// ScriptStruct MovieSceneTracks.MovieSceneActorReferenceSectionTemplate
// 0x00C8 (0x00E8 - 0x0020)
struct FMovieSceneActorReferenceSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieScenePropertySectionData              PropertyData;                                             // 0x0020(0x0028)
	struct FMovieSceneActorReferenceData               ActorReferenceData;                                       // 0x0048(0x00A0)
};

// ScriptStruct MovieSceneTracks.MovieSceneAudioSectionTemplateData
// 0x0198
struct FMovieSceneAudioSectionTemplateData
{
	class USoundBase*                                  Sound;                                                    // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	float                                              AudioStartOffset;                                         // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
	double                                             SectionStartTimeSeconds;                                  // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FMovieSceneFloatChannel                     AudioPitchMultiplierCurve;                                // 0x0018(0x00A0)
	struct FMovieSceneFloatChannel                     AudioVolumeCurve;                                         // 0x00B8(0x00A0)
	int                                                RowIndex;                                                 // 0x0158(0x0004) (ZeroConstructor, IsPlainOldData)
	bool                                               bOverrideAttenuation;                                     // 0x015C(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x015D(0x0003) MISSED OFFSET
	class USoundAttenuation*                           AttenuationSettings;                                      // 0x0160(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FScriptDelegate                             OnQueueSubtitles;                                         // 0x0168(0x0014) (ZeroConstructor, InstancedReference)
	struct FScriptMulticastDelegate                    OnAudioFinished;                                          // 0x0178(0x0010) (ZeroConstructor, InstancedReference)
	struct FScriptMulticastDelegate                    OnAudioPlaybackPercent;                                   // 0x0188(0x0010) (ZeroConstructor, InstancedReference)
};

// ScriptStruct MovieSceneTracks.MovieSceneAudioSectionTemplate
// 0x0198 (0x01B8 - 0x0020)
struct FMovieSceneAudioSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneAudioSectionTemplateData         AudioData;                                                // 0x0020(0x0198)
};

// ScriptStruct MovieSceneTracks.MovieSceneAdditiveCameraAnimationTemplate
// 0x0000 (0x0020 - 0x0020)
struct FMovieSceneAdditiveCameraAnimationTemplate : public FMovieSceneEvalTemplate
{

};

// ScriptStruct MovieSceneTracks.MovieSceneCameraShakeSectionTemplate
// 0x0028 (0x0048 - 0x0020)
struct FMovieSceneCameraShakeSectionTemplate : public FMovieSceneAdditiveCameraAnimationTemplate
{
	struct FMovieSceneCameraShakeSectionData           SourceData;                                               // 0x0020(0x0020)
	struct FFrameNumber                                SectionStartTime;                                         // 0x0040(0x0004)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0044(0x0004) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneCameraAnimSectionTemplate
// 0x0028 (0x0048 - 0x0020)
struct FMovieSceneCameraAnimSectionTemplate : public FMovieSceneAdditiveCameraAnimationTemplate
{
	struct FMovieSceneCameraAnimSectionData            SourceData;                                               // 0x0020(0x0020)
	struct FFrameNumber                                SectionStartTime;                                         // 0x0040(0x0004)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0044(0x0004) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneCameraCutSectionTemplate
// 0x0060 (0x0080 - 0x0020)
struct FMovieSceneCameraCutSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneObjectBindingID                  CameraBindingID;                                          // 0x0020(0x0018)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
	struct FTransform                                  CutTransform;                                             // 0x0040(0x0030) (IsPlainOldData)
	bool                                               bHasCutTransform;                                         // 0x0070(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0xF];                                       // 0x0071(0x000F) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneColorKeyStruct
// 0x0030 (0x0038 - 0x0008)
struct FMovieSceneColorKeyStruct : public FMovieSceneKeyStruct
{
	struct FLinearColor                                Color;                                                    // 0x0008(0x0010) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFrameNumber                                Time;                                                     // 0x0018(0x0004) (Edit)
	unsigned char                                      UnknownData00[0x1C];                                      // 0x001C(0x001C) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneColorSectionTemplate
// 0x0288 (0x02D0 - 0x0048)
struct FMovieSceneColorSectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneFloatChannel                     Curves[0x4];                                              // 0x0048(0x00A0)
	EMovieSceneBlendType                               BlendType;                                                // 0x02C8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x02C9(0x0007) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneEventTemplateBase
// 0x0018 (0x0038 - 0x0020)
struct FMovieSceneEventTemplateBase : public FMovieSceneEvalTemplate
{
	TArray<struct FMovieSceneObjectBindingID>          EventReceivers;                                           // 0x0020(0x0010) (ZeroConstructor)
	unsigned char                                      bFireEventsWhenForwards : 1;                              // 0x0030(0x0001)
	unsigned char                                      bFireEventsWhenBackwards : 1;                             // 0x0030(0x0001)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0031(0x0007) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneEventRepeaterTemplate
// 0x0008 (0x0040 - 0x0038)
struct FMovieSceneEventRepeaterTemplate : public FMovieSceneEventTemplateBase
{
	struct FName                                       EventToTrigger;                                           // 0x0038(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieSceneTracks.MovieSceneEventTriggerTemplate
// 0x0020 (0x0058 - 0x0038)
struct FMovieSceneEventTriggerTemplate : public FMovieSceneEventTemplateBase
{
	TArray<struct FFrameNumber>                        EventTimes;                                               // 0x0038(0x0010) (ZeroConstructor)
	TArray<struct FName>                               EventFunctions;                                           // 0x0048(0x0010) (ZeroConstructor)
};

// ScriptStruct MovieSceneTracks.MovieSceneEventSectionTemplate
// 0x0088 (0x00C0 - 0x0038)
struct FMovieSceneEventSectionTemplate : public FMovieSceneEventTemplateBase
{
	struct FMovieSceneEventSectionData                 EventData;                                                // 0x0038(0x0088)
};

// ScriptStruct MovieSceneTracks.MovieSceneFadeSectionTemplate
// 0x00B8 (0x00D8 - 0x0020)
struct FMovieSceneFadeSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneFloatChannel                     FadeCurve;                                                // 0x0020(0x00A0)
	struct FLinearColor                                FadeColor;                                                // 0x00C0(0x0010) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      bFadeAudio : 1;                                           // 0x00D0(0x0001)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00D1(0x0007) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneLevelVisibilitySectionTemplate
// 0x0018 (0x0038 - 0x0020)
struct FMovieSceneLevelVisibilitySectionTemplate : public FMovieSceneEvalTemplate
{
	ELevelVisibility                                   Visibility;                                               // 0x0020(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0021(0x0007) MISSED OFFSET
	TArray<struct FName>                               LevelNames;                                               // 0x0028(0x0010) (ZeroConstructor)
};

// ScriptStruct MovieSceneTracks.MovieSceneParameterSectionTemplate
// 0x0030 (0x0050 - 0x0020)
struct FMovieSceneParameterSectionTemplate : public FMovieSceneEvalTemplate
{
	TArray<struct FScalarParameterNameAndCurve>        Scalars;                                                  // 0x0020(0x0010) (ZeroConstructor)
	TArray<struct FVectorParameterNameAndCurves>       Vectors;                                                  // 0x0030(0x0010) (ZeroConstructor)
	TArray<struct FColorParameterNameAndCurves>        Colors;                                                   // 0x0040(0x0010) (ZeroConstructor)
};

// ScriptStruct MovieSceneTracks.MovieSceneMaterialParameterCollectionTemplate
// 0x0008 (0x0058 - 0x0050)
struct FMovieSceneMaterialParameterCollectionTemplate : public FMovieSceneParameterSectionTemplate
{
	class UMaterialParameterCollection*                MPC;                                                      // 0x0050(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieSceneTracks.MovieSceneComponentMaterialSectionTemplate
// 0x0008 (0x0058 - 0x0050)
struct FMovieSceneComponentMaterialSectionTemplate : public FMovieSceneParameterSectionTemplate
{
	int                                                MaterialIndex;                                            // 0x0050(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0054(0x0004) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneParticleParameterSectionTemplate
// 0x0000 (0x0050 - 0x0050)
struct FMovieSceneParticleParameterSectionTemplate : public FMovieSceneParameterSectionTemplate
{

};

// ScriptStruct MovieSceneTracks.MovieSceneParticleSectionTemplate
// 0x0098 (0x00B8 - 0x0020)
struct FMovieSceneParticleSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneParticleChannel                  ParticleKeys;                                             // 0x0020(0x0098)
};

// ScriptStruct MovieSceneTracks.MovieSceneEulerTransformPropertySectionTemplate
// 0x0650 (0x0698 - 0x0048)
struct FMovieSceneEulerTransformPropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieScene3DTransformTemplateData          TemplateData;                                             // 0x0048(0x0650)
};

// ScriptStruct MovieSceneTracks.MovieSceneTransformPropertySectionTemplate
// 0x0650 (0x0698 - 0x0048)
struct FMovieSceneTransformPropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieScene3DTransformTemplateData          TemplateData;                                             // 0x0048(0x0650)
};

// ScriptStruct MovieSceneTracks.MovieSceneVectorPropertySectionTemplate
// 0x0288 (0x02D0 - 0x0048)
struct FMovieSceneVectorPropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneFloatChannel                     ComponentCurves[0x4];                                     // 0x0048(0x00A0)
	int                                                NumChannelsUsed;                                          // 0x02C8(0x0004) (ZeroConstructor, IsPlainOldData)
	EMovieSceneBlendType                               BlendType;                                                // 0x02CC(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x02CD(0x0003) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneStringPropertySectionTemplate
// 0x00A0 (0x00E8 - 0x0048)
struct FMovieSceneStringPropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneStringChannel                    StringCurve;                                              // 0x0048(0x00A0)
};

// ScriptStruct MovieSceneTracks.MovieSceneIntegerPropertySectionTemplate
// 0x0098 (0x00E0 - 0x0048)
struct FMovieSceneIntegerPropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneIntegerChannel                   IntegerCurve;                                             // 0x0048(0x0090)
	EMovieSceneBlendType                               BlendType;                                                // 0x00D8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00D9(0x0007) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneEnumPropertySectionTemplate
// 0x0098 (0x00E0 - 0x0048)
struct FMovieSceneEnumPropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneByteChannel                      EnumCurve;                                                // 0x0048(0x0098)
};

// ScriptStruct MovieSceneTracks.MovieSceneBytePropertySectionTemplate
// 0x0098 (0x00E0 - 0x0048)
struct FMovieSceneBytePropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneByteChannel                      ByteCurve;                                                // 0x0048(0x0098)
};

// ScriptStruct MovieSceneTracks.MovieSceneFloatPropertySectionTemplate
// 0x00A8 (0x00F0 - 0x0048)
struct FMovieSceneFloatPropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneFloatChannel                     FloatFunction;                                            // 0x0048(0x00A0)
	EMovieSceneBlendType                               BlendType;                                                // 0x00E8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00E9(0x0007) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneBoolPropertySectionTemplate
// 0x0090 (0x00D8 - 0x0048)
struct FMovieSceneBoolPropertySectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneBoolChannel                      BoolCurve;                                                // 0x0048(0x0090)
};

// ScriptStruct MovieSceneTracks.MovieSceneSkeletalAnimationSectionTemplateParameters
// 0x0008 (0x00D0 - 0x00C8)
struct FMovieSceneSkeletalAnimationSectionTemplateParameters : public FMovieSceneSkeletalAnimationParams
{
	struct FFrameNumber                                SectionStartTime;                                         // 0x00C8(0x0004)
	struct FFrameNumber                                SectionEndTime;                                           // 0x00CC(0x0004)
};

// ScriptStruct MovieSceneTracks.MovieSceneSkeletalAnimationSectionTemplate
// 0x00D0 (0x00F0 - 0x0020)
struct FMovieSceneSkeletalAnimationSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneSkeletalAnimationSectionTemplateParameters Params;                                                   // 0x0020(0x00D0)
};

// ScriptStruct MovieSceneTracks.MovieSceneSlomoSectionTemplate
// 0x00A0 (0x00C0 - 0x0020)
struct FMovieSceneSlomoSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneFloatChannel                     SlomoCurve;                                               // 0x0020(0x00A0)
};

// ScriptStruct MovieSceneTracks.MovieSceneSpawnSectionTemplate
// 0x0090 (0x00B0 - 0x0020)
struct FMovieSceneSpawnSectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieSceneBoolChannel                      Curve;                                                    // 0x0020(0x0090)
};

// ScriptStruct MovieSceneTracks.MovieSceneVectorKeyStructBase
// 0x0020 (0x0028 - 0x0008)
struct FMovieSceneVectorKeyStructBase : public FMovieSceneKeyStruct
{
	struct FFrameNumber                                Time;                                                     // 0x0008(0x0004) (Edit)
	unsigned char                                      UnknownData00[0x1C];                                      // 0x000C(0x001C) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneVector4KeyStruct
// 0x0018 (0x0040 - 0x0028)
struct FMovieSceneVector4KeyStruct : public FMovieSceneVectorKeyStructBase
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	struct FVector4                                    Vector;                                                   // 0x0030(0x0010) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieSceneTracks.MovieSceneVectorKeyStruct
// 0x0010 (0x0038 - 0x0028)
struct FMovieSceneVectorKeyStruct : public FMovieSceneVectorKeyStructBase
{
	struct FVector                                     Vector;                                                   // 0x0028(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0034(0x0004) MISSED OFFSET
};

// ScriptStruct MovieSceneTracks.MovieSceneVector2DKeyStruct
// 0x0008 (0x0030 - 0x0028)
struct FMovieSceneVector2DKeyStruct : public FMovieSceneVectorKeyStructBase
{
	struct FVector2D                                   Vector;                                                   // 0x0028(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieSceneTracks.MovieSceneVisibilitySectionTemplate
// 0x0000 (0x00D8 - 0x00D8)
struct FMovieSceneVisibilitySectionTemplate : public FMovieSceneBoolPropertySectionTemplate
{

};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
