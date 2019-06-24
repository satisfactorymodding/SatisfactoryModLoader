#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum MovieScene.EMovieSceneKeyInterpolation
enum class EMovieSceneKeyInterpolation : uint8_t
{
	Auto                           = 0,
	User                           = 1,
	Break                          = 2,
	Linear                         = 3,
	Constant                       = 4,
	EMovieSceneKeyInterpolation_MAX = 5
};


// Enum MovieScene.EMovieSceneBlendType
enum class EMovieSceneBlendType : uint8_t
{
	Absolute                       = 0,
	Additive                       = 1,
	Relative                       = 2,
	EMovieSceneBlendType_MAX       = 3
};


// Enum MovieScene.EMovieSceneBuiltInEasing
enum class EMovieSceneBuiltInEasing : uint8_t
{
	Linear                         = 0,
	SinIn                          = 1,
	SinOut                         = 2,
	SinInOut                       = 3,
	QuadIn                         = 4,
	QuadOut                        = 5,
	QuadInOut                      = 6,
	CubicIn                        = 7,
	CubicOut                       = 8,
	CubicInOut                     = 9,
	QuartIn                        = 10,
	QuartOut                       = 11,
	QuartInOut                     = 12,
	QuintIn                        = 13,
	QuintOut                       = 14,
	QuintInOut                     = 15,
	ExpoIn                         = 16,
	ExpoOut                        = 17,
	ExpoInOut                      = 18,
	CircIn                         = 19,
	CircOut                        = 20,
	CircInOut                      = 21,
	EMovieSceneBuiltInEasing_MAX   = 22
};


// Enum MovieScene.EEvaluationMethod
enum class EEvaluationMethod : uint8_t
{
	Static                         = 0,
	Swept                          = 1,
	EEvaluationMethod_MAX          = 2
};


// Enum MovieScene.EUpdateClockSource
enum class EUpdateClockSource : uint8_t
{
	Tick                           = 0,
	Platform                       = 1,
	Audio                          = 2,
	EUpdateClockSource_MAX         = 3
};


// Enum MovieScene.EMovieSceneEvaluationType
enum class EMovieSceneEvaluationType : uint8_t
{
	FrameLocked                    = 0,
	WithSubFrames                  = 1,
	EMovieSceneEvaluationType_MAX  = 2
};


// Enum MovieScene.EMovieScenePlayerStatus
enum class EMovieScenePlayerStatus : uint8_t
{
	Stopped                        = 0,
	Playing                        = 1,
	Recording                      = 2,
	Scrubbing                      = 3,
	Jumping                        = 4,
	Stepping                       = 5,
	Paused                         = 6,
	MAX                            = 7
};


// Enum MovieScene.EMovieSceneObjectBindingSpace
enum class EMovieSceneObjectBindingSpace : uint8_t
{
	Local                          = 0,
	Root                           = 1,
	EMovieSceneObjectBindingSpace_MAX = 2
};


// Enum MovieScene.EMovieSceneCompletionMode
enum class EMovieSceneCompletionMode : uint8_t
{
	KeepState                      = 0,
	RestoreState                   = 1,
	ProjectDefault                 = 2,
	EMovieSceneCompletionMode_MAX  = 3
};


// Enum MovieScene.ESectionEvaluationFlags
enum class ESectionEvaluationFlags : uint8_t
{
	None                           = 0,
	PreRoll                        = 1,
	PostRoll                       = 2,
	ESectionEvaluationFlags_MAX    = 3
};


// Enum MovieScene.ESpawnOwnership
enum class ESpawnOwnership : uint8_t
{
	InnerSequence                  = 0,
	MasterSequence                 = 1,
	External                       = 2,
	ESpawnOwnership_MAX            = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct MovieScene.MovieSceneSectionEvalOptions
// 0x0002
struct FMovieSceneSectionEvalOptions
{
	bool                                               bCanEditCompletionMode;                                   // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
	EMovieSceneCompletionMode                          CompletionMode;                                           // 0x0001(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneEasingSettings
// 0x0038
struct FMovieSceneEasingSettings
{
	int                                                AutoEaseInDuration;                                       // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                AutoEaseOutDuration;                                      // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
	TScriptInterface<class UMovieSceneEasingFunction>  EaseIn;                                                   // 0x0008(0x0010) (ZeroConstructor, IsPlainOldData)
	bool                                               bManualEaseIn;                                            // 0x0018(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0019(0x0003) MISSED OFFSET
	int                                                ManualEaseInDuration;                                     // 0x001C(0x0004) (ZeroConstructor, IsPlainOldData)
	TScriptInterface<class UMovieSceneEasingFunction>  EaseOut;                                                  // 0x0020(0x0010) (ZeroConstructor, IsPlainOldData)
	bool                                               bManualEaseOut;                                           // 0x0030(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0031(0x0003) MISSED OFFSET
	int                                                ManualEaseOutDuration;                                    // 0x0034(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneFrameRange
// 0x0010
struct FMovieSceneFrameRange
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x0000(0x0010) MISSED OFFSET
};

// ScriptStruct MovieScene.OptionalMovieSceneBlendType
// 0x0002
struct FOptionalMovieSceneBlendType
{
	EMovieSceneBlendType                               BlendType;                                                // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bIsValid;                                                 // 0x0001(0x0001) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneTrackEvalOptions
// 0x0004
struct FMovieSceneTrackEvalOptions
{
	unsigned char                                      bCanEvaluateNearestSection : 1;                           // 0x0000(0x0001)
	unsigned char                                      bEvalNearestSection : 1;                                  // 0x0000(0x0001) (Edit)
	unsigned char                                      bEvaluateInPreroll : 1;                                   // 0x0000(0x0001) (Edit)
	unsigned char                                      bEvaluateInPostroll : 1;                                  // 0x0000(0x0001) (Edit)
	unsigned char                                      bEvaluateNearestSection : 1;                              // 0x0000(0x0001) (Deprecated)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneTrackIdentifier
// 0x0004
struct FMovieSceneTrackIdentifier
{
	uint32_t                                           Value;                                                    // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneSegment
// 0x0058
struct FMovieSceneSegment
{
	unsigned char                                      UnknownData00[0x58];                                      // 0x0000(0x0058) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneEvaluationTrackSegments
// 0x0020
struct FMovieSceneEvaluationTrackSegments
{
	TArray<int>                                        SegmentIdentifierToIndex;                                 // 0x0000(0x0010) (ZeroConstructor)
	TArray<struct FMovieSceneSegment>                  SortedSegments;                                           // 0x0010(0x0010) (ZeroConstructor)
};

// ScriptStruct MovieScene.SectionEvaluationDataTree
// 0x0060
struct FSectionEvaluationDataTree
{
	unsigned char                                      UnknownData00[0x60];                                      // 0x0000(0x0060) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneEvalTemplatePtr
// 0x0038
struct FMovieSceneEvalTemplatePtr
{
	unsigned char                                      UnknownData00[0x38];                                      // 0x0000(0x0038) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneTrackImplementationPtr
// 0x0038
struct FMovieSceneTrackImplementationPtr
{
	unsigned char                                      UnknownData00[0x38];                                      // 0x0000(0x0038) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneEvaluationTrack
// 0x00F8
struct FMovieSceneEvaluationTrack
{
	struct FGuid                                       ObjectBindingId;                                          // 0x0000(0x0010) (ZeroConstructor, IsPlainOldData)
	uint16_t                                           EvaluationPriority;                                       // 0x0010(0x0002) (ZeroConstructor, IsPlainOldData)
	EEvaluationMethod                                  EvaluationMethod;                                         // 0x0012(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x5];                                       // 0x0013(0x0005) MISSED OFFSET
	struct FMovieSceneEvaluationTrackSegments          Segments;                                                 // 0x0018(0x0020)
	class UMovieSceneTrack*                            SourceTrack;                                              // 0x0038(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FSectionEvaluationDataTree                  EvaluationTree;                                           // 0x0040(0x0060)
	TArray<struct FMovieSceneEvalTemplatePtr>          ChildTemplates;                                           // 0x00A0(0x0010) (ZeroConstructor)
	struct FMovieSceneTrackImplementationPtr           TrackTemplate;                                            // 0x00B0(0x0038)
	struct FName                                       EvaluationGroup;                                          // 0x00E8(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      bEvaluateInPreroll : 1;                                   // 0x00F0(0x0001)
	unsigned char                                      bEvaluateInPostroll : 1;                                  // 0x00F0(0x0001)
	unsigned char                                      UnknownData01[0x7];                                       // 0x00F1(0x0007) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneEvaluationGroupLUTIndex
// 0x000C
struct FMovieSceneEvaluationGroupLUTIndex
{
	int                                                LUTOffset;                                                // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                NumInitPtrs;                                              // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                NumEvalPtrs;                                              // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneSequenceID
// 0x0004
struct FMovieSceneSequenceID
{
	uint32_t                                           Value;                                                    // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneEvaluationFieldTrackPtr
// 0x0008
struct FMovieSceneEvaluationFieldTrackPtr
{
	struct FMovieSceneSequenceID                       SequenceID;                                               // 0x0000(0x0004)
	struct FMovieSceneTrackIdentifier                  TrackIdentifier;                                          // 0x0004(0x0004)
};

// ScriptStruct MovieScene.MovieSceneSegmentIdentifier
// 0x0004
struct FMovieSceneSegmentIdentifier
{
	int                                                IdentifierIndex;                                          // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneEvaluationFieldSegmentPtr
// 0x0004 (0x000C - 0x0008)
struct FMovieSceneEvaluationFieldSegmentPtr : public FMovieSceneEvaluationFieldTrackPtr
{
	struct FMovieSceneSegmentIdentifier                SegmentID;                                                // 0x0008(0x0004)
};

// ScriptStruct MovieScene.MovieSceneEvaluationGroup
// 0x0020
struct FMovieSceneEvaluationGroup
{
	TArray<struct FMovieSceneEvaluationGroupLUTIndex>  LUTIndices;                                               // 0x0000(0x0010) (ZeroConstructor)
	TArray<struct FMovieSceneEvaluationFieldSegmentPtr> SegmentPtrLUT;                                            // 0x0010(0x0010) (ZeroConstructor)
};

// ScriptStruct MovieScene.MovieSceneEvaluationKey
// 0x000C
struct FMovieSceneEvaluationKey
{
	struct FMovieSceneSequenceID                       SequenceID;                                               // 0x0000(0x0004)
	struct FMovieSceneTrackIdentifier                  TrackIdentifier;                                          // 0x0004(0x0004)
	uint32_t                                           SectionIndex;                                             // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneOrderedEvaluationKey
// 0x0010
struct FMovieSceneOrderedEvaluationKey
{
	struct FMovieSceneEvaluationKey                    Key;                                                      // 0x0000(0x000C)
	uint32_t                                           EvaluationIndex;                                          // 0x000C(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneEvaluationMetaData
// 0x0070
struct FMovieSceneEvaluationMetaData
{
	TArray<struct FMovieSceneSequenceID>               ActiveSequences;                                          // 0x0000(0x0010) (ZeroConstructor)
	TArray<struct FMovieSceneOrderedEvaluationKey>     ActiveEntities;                                           // 0x0010(0x0010) (ZeroConstructor)
	TMap<struct FMovieSceneSequenceID, uint32_t>       SubTemplateSerialNumbers;                                 // 0x0020(0x0050) (ZeroConstructor)
};

// ScriptStruct MovieScene.MovieSceneEvaluationField
// 0x0030
struct FMovieSceneEvaluationField
{
	TArray<struct FMovieSceneFrameRange>               Ranges;                                                   // 0x0000(0x0010) (ZeroConstructor)
	TArray<struct FMovieSceneEvaluationGroup>          Groups;                                                   // 0x0010(0x0010) (ZeroConstructor)
	TArray<struct FMovieSceneEvaluationMetaData>       MetaData;                                                 // 0x0020(0x0010) (ZeroConstructor)
};

// ScriptStruct MovieScene.MovieSceneSequenceTransform
// 0x000C
struct FMovieSceneSequenceTransform
{
	float                                              TimeScale;                                                // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FFrameTime                                  Offset;                                                   // 0x0004(0x0008)
};

// ScriptStruct MovieScene.MovieSceneSequenceInstanceDataPtr
// 0x0018
struct FMovieSceneSequenceInstanceDataPtr
{
	unsigned char                                      UnknownData00[0x18];                                      // 0x0000(0x0018) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneSubSequenceData
// 0x00A8
struct FMovieSceneSubSequenceData
{
	struct FSoftObjectPath                             Sequence;                                                 // 0x0000(0x0018) (ZeroConstructor)
	struct FMovieSceneSequenceTransform                RootToSequenceTransform;                                  // 0x0018(0x000C)
	struct FFrameRate                                  TickResolution;                                           // 0x0024(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FMovieSceneSequenceID                       DeterministicSequenceID;                                  // 0x002C(0x0004)
	struct FMovieSceneFrameRange                       PlayRange;                                                // 0x0030(0x0010)
	struct FMovieSceneFrameRange                       PreRollRange;                                             // 0x0040(0x0010)
	struct FMovieSceneFrameRange                       PostRollRange;                                            // 0x0050(0x0010)
	int                                                HierarchicalBias;                                         // 0x0060(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0064(0x0004) MISSED OFFSET
	struct FMovieSceneSequenceInstanceDataPtr          InstanceData;                                             // 0x0068(0x0018)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0080(0x0008) MISSED OFFSET
	struct FGuid                                       SubSectionSignature;                                      // 0x0088(0x0010) (ZeroConstructor, IsPlainOldData)
	struct FMovieSceneSequenceTransform                OuterToInnerTransform;                                    // 0x0098(0x000C)
	unsigned char                                      UnknownData02[0x4];                                       // 0x00A4(0x0004) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneSequenceHierarchyNode
// 0x0018
struct FMovieSceneSequenceHierarchyNode
{
	struct FMovieSceneSequenceID                       ParentID;                                                 // 0x0000(0x0004)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0004(0x0004) MISSED OFFSET
	TArray<struct FMovieSceneSequenceID>               Children;                                                 // 0x0008(0x0010) (ZeroConstructor)
};

// ScriptStruct MovieScene.MovieSceneSequenceHierarchy
// 0x00A0
struct FMovieSceneSequenceHierarchy
{
	TMap<struct FMovieSceneSequenceID, struct FMovieSceneSubSequenceData> SubSequences;                                             // 0x0000(0x0050) (ZeroConstructor)
	TMap<struct FMovieSceneSequenceID, struct FMovieSceneSequenceHierarchyNode> Hierarchy;                                                // 0x0050(0x0050) (ZeroConstructor)
};

// ScriptStruct MovieScene.MovieSceneEvaluationTemplateSerialNumber
// 0x0004
struct FMovieSceneEvaluationTemplateSerialNumber
{
	uint32_t                                           Value;                                                    // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneTemplateGenerationLedger
// 0x00A8
struct FMovieSceneTemplateGenerationLedger
{
	struct FMovieSceneTrackIdentifier                  LastTrackIdentifier;                                      // 0x0000(0x0004)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0004(0x0004) MISSED OFFSET
	TMap<struct FGuid, struct FMovieSceneTrackIdentifier> TrackSignatureToTrackIdentifier;                          // 0x0008(0x0050) (ZeroConstructor)
	TMap<struct FGuid, struct FMovieSceneFrameRange>   SubSectionRanges;                                         // 0x0058(0x0050) (ZeroConstructor)
};

// ScriptStruct MovieScene.MovieSceneTrackFieldData
// 0x0060
struct FMovieSceneTrackFieldData
{
	unsigned char                                      UnknownData00[0x60];                                      // 0x0000(0x0060) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneSubSectionFieldData
// 0x0060
struct FMovieSceneSubSectionFieldData
{
	unsigned char                                      UnknownData00[0x60];                                      // 0x0000(0x0060) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneEvaluationTemplate
// 0x02F0
struct FMovieSceneEvaluationTemplate
{
	TMap<struct FMovieSceneTrackIdentifier, struct FMovieSceneEvaluationTrack> TRACKS;                                                   // 0x0000(0x0050) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x50];                                      // 0x0050(0x0050) MISSED OFFSET
	struct FMovieSceneEvaluationField                  EvaluationField;                                          // 0x00A0(0x0030)
	struct FMovieSceneSequenceHierarchy                Hierarchy;                                                // 0x00D0(0x00A0)
	struct FGuid                                       SequenceSignature;                                        // 0x0170(0x0010) (ZeroConstructor, IsPlainOldData)
	struct FMovieSceneEvaluationTemplateSerialNumber   TemplateSerialNumber;                                     // 0x0180(0x0004)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0184(0x0004) MISSED OFFSET
	struct FMovieSceneTemplateGenerationLedger         TemplateLedger;                                           // 0x0188(0x00A8)
	struct FMovieSceneTrackFieldData                   TrackFieldData;                                           // 0x0230(0x0060)
	struct FMovieSceneSubSectionFieldData              SubSectionFieldData;                                      // 0x0290(0x0060)
};

// ScriptStruct MovieScene.MovieSceneSequencePlaybackSettings
// 0x0040
struct FMovieSceneSequencePlaybackSettings
{
	int                                                LoopCount;                                                // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              PlayRate;                                                 // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bRandomStartTime;                                         // 0x0008(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
	float                                              StartTime;                                                // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bRestoreState;                                            // 0x0010(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bDisableMovementInput;                                    // 0x0011(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bDisableLookAtInput;                                      // 0x0012(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bHidePlayer;                                              // 0x0013(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bHideHud;                                                 // 0x0014(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bDisableCameraCuts;                                       // 0x0015(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bPauseAtEnd;                                              // 0x0016(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x1];                                       // 0x0017(0x0001) MISSED OFFSET
	class UObject*                                     InstanceData;                                             // 0x0018(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TScriptInterface<class UMovieSceneBindingOverridesInterface> BindingOverrides;                                         // 0x0020(0x0010) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x10];                                      // 0x0030(0x0010) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneRootEvaluationTemplateInstance
// 0x0300
struct FMovieSceneRootEvaluationTemplateInstance
{
	unsigned char                                      UnknownData00[0x18];                                      // 0x0000(0x0018) MISSED OFFSET
	TMap<struct FMovieSceneSequenceID, class UObject*> DirectorInstances;                                        // 0x0018(0x0050) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x298];                                     // 0x0068(0x0298) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneObjectBindingID
// 0x0018
struct FMovieSceneObjectBindingID
{
	int                                                SequenceID;                                               // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	EMovieSceneObjectBindingSpace                      Space;                                                    // 0x0004(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0005(0x0003) MISSED OFFSET
	struct FGuid                                       Guid;                                                     // 0x0008(0x0010) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneSpawnable
// 0x0090
struct FMovieSceneSpawnable
{
	struct FTransform                                  SpawnTransform;                                           // 0x0000(0x0030) (Edit, IsPlainOldData)
	TArray<struct FName>                               Tags;                                                     // 0x0030(0x0010) (Edit, ZeroConstructor)
	struct FGuid                                       Guid;                                                     // 0x0040(0x0010) (ZeroConstructor, IsPlainOldData)
	class FString                                      Name;                                                     // 0x0050(0x0010) (ZeroConstructor)
	class UObject*                                     ObjectTemplate;                                           // 0x0060(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<struct FGuid>                               ChildPossessables;                                        // 0x0068(0x0010) (ZeroConstructor)
	ESpawnOwnership                                    Ownership;                                                // 0x0078(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0079(0x0007) MISSED OFFSET
	struct FName                                       LevelName;                                                // 0x0080(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0088(0x0008) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieScenePossessable
// 0x0048
struct FMovieScenePossessable
{
	TArray<struct FName>                               Tags;                                                     // 0x0000(0x0010) (Edit, ZeroConstructor)
	struct FGuid                                       Guid;                                                     // 0x0010(0x0010) (ZeroConstructor, IsPlainOldData)
	class FString                                      Name;                                                     // 0x0020(0x0010) (ZeroConstructor)
	class UClass*                                      PossessedObjectClass;                                     // 0x0030(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FGuid                                       ParentGuid;                                               // 0x0038(0x0010) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneBinding
// 0x0030
struct FMovieSceneBinding
{
	struct FGuid                                       ObjectGuid;                                               // 0x0000(0x0010) (ZeroConstructor, IsPlainOldData)
	class FString                                      BindingName;                                              // 0x0010(0x0010) (ZeroConstructor)
	TArray<class UMovieSceneTrack*>                    TRACKS;                                                   // 0x0020(0x0010) (ExportObject, ZeroConstructor)
};

// ScriptStruct MovieScene.MovieSceneBindingOverrideData
// 0x0024
struct FMovieSceneBindingOverrideData
{
	struct FMovieSceneObjectBindingID                  ObjectBindingId;                                          // 0x0000(0x0018) (Edit)
	TWeakObjectPtr<class UObject>                      Object;                                                   // 0x0018(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bOverridesDefault;                                        // 0x0020(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0021(0x0003) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneSectionParameters
// 0x0018
struct FMovieSceneSectionParameters
{
	struct FFrameNumber                                StartFrameOffset;                                         // 0x0000(0x0004) (Edit)
	float                                              TimeScale;                                                // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                HierarchicalBias;                                         // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              StartOffset;                                              // 0x000C(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              PrerollTime;                                              // 0x0010(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              PostrollTime;                                             // 0x0014(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneEvalTemplateBase
// 0x0010
struct FMovieSceneEvalTemplateBase
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x0000(0x0010) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneEvalTemplate
// 0x0010 (0x0020 - 0x0010)
struct FMovieSceneEvalTemplate : public FMovieSceneEvalTemplateBase
{
	EMovieSceneCompletionMode                          CompletionMode;                                           // 0x0010(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0011(0x0007) MISSED OFFSET
	class UMovieSceneSection*                          SourceSection;                                            // 0x0018(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieScenePropertySectionData
// 0x0028
struct FMovieScenePropertySectionData
{
	struct FName                                       PropertyName;                                             // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	class FString                                      PropertyPath;                                             // 0x0008(0x0010) (ZeroConstructor)
	struct FName                                       FunctionName;                                             // 0x0018(0x0008) (ZeroConstructor, IsPlainOldData)
	struct FName                                       NotifyFunctionName;                                       // 0x0020(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieScenePropertySectionTemplate
// 0x0028 (0x0048 - 0x0020)
struct FMovieScenePropertySectionTemplate : public FMovieSceneEvalTemplate
{
	struct FMovieScenePropertySectionData              PropertyData;                                             // 0x0020(0x0028)
};

// ScriptStruct MovieScene.MovieSceneChannel
// 0x0008
struct FMovieSceneChannel
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneTangentData
// 0x0014
struct FMovieSceneTangentData
{
	float                                              ArriveTangent;                                            // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              LeaveTangent;                                             // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERichCurveTangentWeightMode>           TangentWeightMode;                                        // 0x0008(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
	float                                              ArriveTangentWeight;                                      // 0x000C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              LeaveTangentWeight;                                       // 0x0010(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneFloatValue
// 0x001C
struct FMovieSceneFloatValue
{
	float                                              Value;                                                    // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERichCurveInterpMode>                  InterpMode;                                               // 0x0004(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERichCurveTangentMode>                 TangentMode;                                              // 0x0005(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0006(0x0002) MISSED OFFSET
	struct FMovieSceneTangentData                      Tangent;                                                  // 0x0008(0x0014) (Edit)
};

// ScriptStruct MovieScene.MovieSceneKeyHandleMap
// 0x0000 (0x0060 - 0x0060)
struct FMovieSceneKeyHandleMap : public FKeyHandleLookupTable
{

};

// ScriptStruct MovieScene.MovieSceneFloatChannel
// 0x0098 (0x00A0 - 0x0008)
struct FMovieSceneFloatChannel : public FMovieSceneChannel
{
	TEnumAsByte<ERichCurveExtrapolation>               PreInfinityExtrap;                                        // 0x0008(0x0001) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERichCurveExtrapolation>               PostInfinityExtrap;                                       // 0x0009(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x000A(0x0006) MISSED OFFSET
	TArray<struct FFrameNumber>                        Times;                                                    // 0x0010(0x0010) (ZeroConstructor)
	TArray<struct FMovieSceneFloatValue>               Values;                                                   // 0x0020(0x0010) (ZeroConstructor)
	float                                              DefaultValue;                                             // 0x0030(0x0004) (ZeroConstructor, IsPlainOldData)
	bool                                               bHasDefaultValue;                                         // 0x0034(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0035(0x0003) MISSED OFFSET
	struct FMovieSceneKeyHandleMap                     KeyHandles;                                               // 0x0038(0x0060) (Transient)
	struct FFrameRate                                  TickResolution;                                           // 0x0098(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneTrackLabels
// 0x0010
struct FMovieSceneTrackLabels
{
	TArray<class FString>                              Strings;                                                  // 0x0000(0x0010) (ZeroConstructor)
};

// ScriptStruct MovieScene.MovieSceneExpansionState
// 0x0001
struct FMovieSceneExpansionState
{
	bool                                               bExpanded;                                                // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneEditorData
// 0x00E0
struct FMovieSceneEditorData
{
	TMap<class FString, struct FMovieSceneExpansionState> ExpansionStates;                                          // 0x0000(0x0050) (ZeroConstructor)
	double                                             ViewStart;                                                // 0x0050(0x0008) (ZeroConstructor, IsPlainOldData)
	double                                             ViewEnd;                                                  // 0x0058(0x0008) (ZeroConstructor, IsPlainOldData)
	double                                             WorkStart;                                                // 0x0060(0x0008) (ZeroConstructor, IsPlainOldData)
	double                                             WorkEnd;                                                  // 0x0068(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x50];                                      // 0x0070(0x0050) UNKNOWN PROPERTY: SetProperty MovieScene.MovieSceneEditorData.MarkedFrames
	struct FFloatRange                                 WorkingRange;                                             // 0x00C0(0x0010) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FFloatRange                                 ViewRange;                                                // 0x00D0(0x0010) (ZeroConstructor, Deprecated, IsPlainOldData)
};

// ScriptStruct MovieScene.MovieSceneTimecodeSource
// 0x0018
struct FMovieSceneTimecodeSource
{
	struct FTimecode                                   Timecode;                                                 // 0x0000(0x0014) (ZeroConstructor, IsPlainOldData)
	struct FFrameNumber                                DeltaFrame;                                               // 0x0014(0x0004)
};

// ScriptStruct MovieScene.MovieSceneBoolChannel
// 0x0088 (0x0090 - 0x0008)
struct FMovieSceneBoolChannel : public FMovieSceneChannel
{
	TArray<struct FFrameNumber>                        Times;                                                    // 0x0008(0x0010) (ZeroConstructor)
	bool                                               DefaultValue;                                             // 0x0018(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bHasDefaultValue;                                         // 0x0019(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x001A(0x0006) MISSED OFFSET
	TArray<bool>                                       Values;                                                   // 0x0020(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x60];                                      // 0x0030(0x0060) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneByteChannel
// 0x0090 (0x0098 - 0x0008)
struct FMovieSceneByteChannel : public FMovieSceneChannel
{
	TArray<struct FFrameNumber>                        Times;                                                    // 0x0008(0x0010) (ZeroConstructor)
	unsigned char                                      DefaultValue;                                             // 0x0018(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bHasDefaultValue;                                         // 0x0019(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x001A(0x0006) MISSED OFFSET
	TArray<unsigned char>                              Values;                                                   // 0x0020(0x0010) (ZeroConstructor)
	class UEnum*                                       Enum;                                                     // 0x0030(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x60];                                      // 0x0038(0x0060) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneEmptyStruct
// 0x0001
struct FMovieSceneEmptyStruct
{
	unsigned char                                      UnknownData00[0x1];                                       // 0x0000(0x0001) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneEvaluationOperand
// 0x0014
struct FMovieSceneEvaluationOperand
{
	struct FGuid                                       ObjectBindingId;                                          // 0x0000(0x0010) (ZeroConstructor, IsPlainOldData)
	struct FMovieSceneSequenceID                       SequenceID;                                               // 0x0010(0x0004)
};

// ScriptStruct MovieScene.MovieSceneSubSectionData
// 0x001C
struct FMovieSceneSubSectionData
{
	TWeakObjectPtr<class UMovieSceneSubSection>        Section;                                                  // 0x0000(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FGuid                                       ObjectBindingId;                                          // 0x0008(0x0010) (ZeroConstructor, IsPlainOldData)
	ESectionEvaluationFlags                            Flags;                                                    // 0x0018(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0019(0x0003) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneIntegerChannel
// 0x0088 (0x0090 - 0x0008)
struct FMovieSceneIntegerChannel : public FMovieSceneChannel
{
	TArray<struct FFrameNumber>                        Times;                                                    // 0x0008(0x0010) (ZeroConstructor)
	int                                                DefaultValue;                                             // 0x0018(0x0004) (ZeroConstructor, IsPlainOldData)
	bool                                               bHasDefaultValue;                                         // 0x001C(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x001D(0x0003) MISSED OFFSET
	TArray<int>                                        Values;                                                   // 0x0020(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData01[0x60];                                      // 0x0030(0x0060) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneKeyStruct
// 0x0008
struct FMovieSceneKeyStruct
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneKeyTimeStruct
// 0x0020 (0x0028 - 0x0008)
struct FMovieSceneKeyTimeStruct : public FMovieSceneKeyStruct
{
	struct FFrameNumber                                Time;                                                     // 0x0008(0x0004) (Edit)
	unsigned char                                      UnknownData00[0x1C];                                      // 0x000C(0x001C) MISSED OFFSET
};

// ScriptStruct MovieScene.SectionEvaluationData
// 0x000C
struct FSectionEvaluationData
{
	int                                                ImplIndex;                                                // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FFrameNumber                                ForcedTime;                                               // 0x0004(0x0004)
	ESectionEvaluationFlags                            Flags;                                                    // 0x0008(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
};

// ScriptStruct MovieScene.MovieSceneSequenceInstanceData
// 0x0008
struct FMovieSceneSequenceInstanceData
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
};

// ScriptStruct MovieScene.TestMovieSceneEvalTemplate
// 0x0000 (0x0020 - 0x0020)
struct FTestMovieSceneEvalTemplate : public FMovieSceneEvalTemplate
{

};

// ScriptStruct MovieScene.MovieSceneTrackImplementation
// 0x0000 (0x0010 - 0x0010)
struct FMovieSceneTrackImplementation : public FMovieSceneEvalTemplateBase
{

};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
