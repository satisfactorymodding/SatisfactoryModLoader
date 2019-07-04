#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_SlateCore_classes.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_UMG_classes.hpp"
#include "FG_MovieScene_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum AkAudio.EAkCallbackType
enum class EAkCallbackType : uint8_t
{
	EndOfEvent                     = 0,
	Marker                         = 1,
	Duration                       = 2,
	Starvation                     = 3,
	MusicPlayStarted               = 4,
	MusicSyncBeat                  = 5,
	MusicSyncBar                   = 6,
	MusicSyncEntry                 = 7,
	MusicSyncExit                  = 8,
	MusicSyncGrid                  = 9,
	MusicSyncUserCue               = 10,
	MusicSyncPoint                 = 11,
	MIDIEvent                      = 12,
	EAkCallbackType_MAX            = 13
};


// Enum AkAudio.EAkResult
enum class EAkResult : uint8_t
{
	NotImplemented                 = 0,
	Success                        = 1,
	Fail                           = 2,
	PartialSuccess                 = 3,
	NotCompatible                  = 4,
	AlreadyConnected               = 5,
	NameNotSet                     = 6,
	InvalidFile                    = 7,
	AudioFileHeaderTooLarge        = 8,
	MaxReached                     = 9,
	InputsInUsed                   = 10,
	OutputsInUsed                  = 11,
	InvalidName                    = 12,
	NameAlreadyInUse               = 13,
	InvalidID                      = 14,
	IDNotFound                     = 15,
	InvalidInstanceID              = 16,
	NoMoreData                     = 17,
	NoSourceAvailable              = 18,
	StateGroupAlreadyExists        = 19,
	InvalidStateGroup              = 20,
	ChildAlreadyHasAParent         = 21,
	InvalidLanguage                = 22,
	CannotAddItseflAsAChild        = 23,
	Reserved1                      = 24,
	Reserved2                      = 25,
	Reserved3                      = 26,
	Reserved4                      = 27,
	Reserved5                      = 28,
	UserNotInList                  = 29,
	NoTransitionPoint              = 30,
	InvalidParameter               = 31,
	ParameterAdjusted              = 32,
	IsA3DSound                     = 33,
	NotA3DSound                    = 34,
	ElementAlreadyInList           = 35,
	PathNotFound                   = 36,
	PathNoVertices                 = 37,
	PathNotRunning                 = 38,
	PathNotPaused                  = 39,
	PathNodeAlreadyInList          = 40,
	PathNodeNotInList              = 41,
	VoiceNotFound                  = 42,
	DataNeeded                     = 43,
	NoDataNeeded                   = 44,
	DataReady                      = 45,
	NoDataReady                    = 46,
	NoMoreSlotAvailable            = 47,
	SlotNotFound                   = 48,
	ProcessingOnly                 = 49,
	MemoryLeak                     = 50,
	CorruptedBlockList             = 51,
	InsufficientMemory             = 52,
	Cancelled                      = 53,
	UnknownBankID                  = 54,
	IsProcessing                   = 55,
	BankReadError                  = 56,
	InvalidSwitchType              = 57,
	VoiceDone                      = 58,
	UnknownEnvironment             = 59,
	EnvironmentInUse               = 60,
	UnknownObject                  = 61,
	NoConversionNeeded             = 62,
	FormatNotReady                 = 63,
	WrongBankVersion               = 64,
	DataReadyNoProcess             = 65,
	FileNotFound                   = 66,
	DeviceNotReady                 = 67,
	CouldNotCreateSecBuffer        = 68,
	BankAlreadyLoaded              = 69,
	Reserved6                      = 70,
	RenderedFX                     = 71,
	ProcessNeeded                  = 72,
	ProcessDone                    = 73,
	MemManagerNotInitialized       = 74,
	StreamMgrNotInitialized        = 75,
	SSEInstructionsNotSupported    = 76,
	Busy                           = 77,
	UnsupportedChannelConfig       = 78,
	PluginMediaNotAvailable        = 79,
	MustBeVirtualized              = 80,
	CommandTooLarge                = 81,
	RejectedByFilter               = 82,
	InvalidCustomPlatformName      = 83,
	DLLCannotLoad                  = 84,
	DLLPathNotFound                = 85,
	NoJavaVM                       = 86,
	OpenSLError                    = 87,
	PluginNotRegistered            = 88,
	DataAlignmentError             = 89,
	EAkResult_MAX                  = 90
};


// Enum AkAudio.EReflectionFilterBits
enum class EReflectionFilterBits : uint8_t
{
	Wall                           = 0,
	Ceiling                        = 1,
	Floor                          = 2,
	EReflectionFilterBits_MAX      = 3
};


// Enum AkAudio.EAkMidiCcValues
enum class EAkMidiCcValues : uint8_t
{
	AkMidiCcBankSelectCoarse       = 0,
	AkMidiCcModWheelCoarse         = 1,
	AkMidiCcBreathCtrlCoarse       = 2,
	AkMidiCcCtrl3Coarse            = 3,
	AkMidiCcFootPedalCoarse        = 4,
	AkMidiCcPortamentoCoarse       = 5,
	AkMidiCcDataEntryCoarse        = 6,
	AkMidiCcVolumeCoarse           = 7,
	AkMidiCcBalanceCoarse          = 8,
	AkMidiCcCtrl9Coarse            = 9,
	AkMidiCcPanPositionCoarse      = 10,
	AkMidiCcExpressionCoarse       = 11,
	AkMidiCcEffectCtrl1Coarse      = 12,
	AkMidiCcEffectCtrl2Coarse      = 13,
	AkMidiCcCtrl14Coarse           = 14,
	AkMidiCcCtrl15Coarse           = 15,
	AkMidiCcGenSlider1             = 16,
	AkMidiCcGenSlider2             = 17,
	AkMidiCcGenSlider3             = 18,
	AkMidiCcGenSlider4             = 19,
	AkMidiCcCtrl20Coarse           = 20,
	AkMidiCcCtrl21Coarse           = 21,
	AkMidiCcCtrl22Coarse           = 22,
	AkMidiCcCtrl23Coarse           = 23,
	AkMidiCcCtrl24Coarse           = 24,
	AkMidiCcCtrl25Coarse           = 25,
	AkMidiCcCtrl26Coarse           = 26,
	AkMidiCcCtrl27Coarse           = 27,
	AkMidiCcCtrl28Coarse           = 28,
	AkMidiCcCtrl29Coarse           = 29,
	AkMidiCcCtrl30Coarse           = 30,
	AkMidiCcCtrl31Coarse           = 31,
	AkMidiCcBankSelectFine         = 32,
	AkMidiCcModWheelFine           = 33,
	AkMidiCcBreathCtrlFine         = 34,
	AkMidiCcCtrl3Fine              = 35,
	AkMidiCcFootPedalFine          = 36,
	AkMidiCcPortamentoFine         = 37,
	AkMidiCcDataEntryFine          = 38,
	AkMidiCcVolumeFine             = 39,
	AkMidiCcBalanceFine            = 40,
	AkMidiCcCtrl9Fine              = 41,
	AkMidiCcPanPositionFine        = 42,
	AkMidiCcExpressionFine         = 43,
	AkMidiCcEffectCtrl1Fine        = 44,
	AkMidiCcEffectCtrl2Fine        = 45,
	AkMidiCcCtrl14Fine             = 46,
	AkMidiCcCtrl15Fine             = 47,
	AkMidiCcCtrl20Fine             = 48,
	AkMidiCcCtrl21Fine             = 49,
	AkMidiCcCtrl22Fine             = 50,
	AkMidiCcCtrl23Fine             = 51,
	AkMidiCcCtrl24Fine             = 52,
	AkMidiCcCtrl25Fine             = 53,
	AkMidiCcCtrl26Fine             = 54,
	AkMidiCcCtrl27Fine             = 55,
	AkMidiCcCtrl28Fine             = 56,
	AkMidiCcCtrl29Fine             = 57,
	AkMidiCcCtrl30Fine             = 58,
	AkMidiCcCtrl31Fine             = 59,
	AkMidiCcHoldPedal              = 60,
	AkMidiCcPortamentoOnOff        = 61,
	AkMidiCcSustenutoPedal         = 62,
	AkMidiCcSoftPedal              = 63,
	AkMidiCcLegatoPedal            = 64,
	AkMidiCcHoldPedal2             = 65,
	AkMidiCcSoundVariation         = 66,
	AkMidiCcSoundTimbre            = 67,
	AkMidiCcSoundReleaseTime       = 68,
	AkMidiCcSoundAttackTime        = 69,
	AkMidiCcSoundBrightness        = 70,
	AkMidiCcSoundCtrl6             = 71,
	AkMidiCcSoundCtrl7             = 72,
	AkMidiCcSoundCtrl8             = 73,
	AkMidiCcSoundCtrl9             = 74,
	AkMidiCcSoundCtrl10            = 75,
	AkMidiCcGeneralButton1         = 76,
	AkMidiCcGeneralButton2         = 77,
	AkMidiCcGeneralButton3         = 78,
	AkMidiCcGeneralButton4         = 79,
	AkMidiCcReverbLevel            = 80,
	AkMidiCcTremoloLevel           = 81,
	AkMidiCcChorusLevel            = 82,
	AkMidiCcCelesteLevel           = 83,
	AkMidiCcPhaserLevel            = 84,
	AkMidiCcDataButtonP1           = 85,
	AkMidiCcDataButtonM1           = 86,
	AkMidiCcNonRegisterCoarse      = 87,
	AkMidiCcNonRegisterFine        = 88,
	AkMidiCcAllSoundOff            = 89,
	AkMidiCcAllControllersOff      = 90,
	AkMidiCcLocalKeyboard          = 91,
	AkMidiCcAllNotesOff            = 92,
	AkMidiCcOmniModeOff            = 93,
	AkMidiCcOmniModeOn             = 94,
	AkMidiCcOmniMonophonicOn       = 95,
	AkMidiCcOmniPolyphonicOn       = 96,
	EAkMidiCcValues_MAX            = 97
};


// Enum AkAudio.EAkMidiEventType
enum class EAkMidiEventType : uint8_t
{
	AkMidiEventTypeInvalid         = 0,
	AkMidiEventTypeNoteOff         = 1,
	AkMidiEventTypeNoteOn          = 2,
	AkMidiEventTypeNoteAftertouch  = 3,
	AkMidiEventTypeController      = 4,
	AkMidiEventTypeProgramChange   = 5,
	AkMidiEventTypeChannelAftertouch = 6,
	AkMidiEventTypePitchBend       = 7,
	AkMidiEventTypeSysex           = 8,
	AkMidiEventTypeEscape          = 9,
	AkMidiEventTypeMeta            = 10,
	EAkMidiEventType_MAX           = 11
};


// Enum AkAudio.AkMultiPositionType
enum class EAkMultiPositionType : uint8_t
{
	SingleSource                   = 0,
	MultiSources                   = 1,
	MultiDirections                = 2,
	AkMultiPositionType_MAX        = 3
};


// Enum AkAudio.AkChannelConfiguration
enum class EAkChannelConfiguration : uint8_t
{
	Ak_Parent                      = 0,
	Ak_LFE                         = 1,
	Ak_1                           = 2,
	Ak_2                           = 3,
	Ak_201                         = 4,
	Ak_3                           = 5,
	Ak_301                         = 6,
	Ak_4                           = 7,
	Ak_401                         = 8,
	Ak_5                           = 9,
	Ak_501                         = 10,
	Ak_7                           = 11,
	Ak_5_1                         = 12,
	Ak_7_1                         = 13,
	Ak_7_101                       = 14,
	Ak_Auro_9                      = 15,
	Ak_Auro_10                     = 16,
	Ak_Auro_11                     = 17,
	Ak_Auro_13                     = 18,
	Ak_Ambisonics_1st_order        = 19,
	Ak_Ambisonics_2nd_order        = 20,
	Ak_Ambisonics_3rd_order        = 21,
	Ak_MAX                         = 22
};


// Enum AkAudio.AkAcousticPortalState
enum class EAkAcousticPortalState : uint8_t
{
	Closed                         = 0,
	Open                           = 1,
	AkAcousticPortalState_MAX      = 2
};


// Enum AkAudio.PanningRule
enum class EPanningRule : uint8_t
{
	PanningRule_Speakers           = 0,
	PanningRule_Headphones         = 1,
	PanningRule_MAX                = 2
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct AkAudio.AkBoolPropertyToControl
// 0x0010
struct FAkBoolPropertyToControl
{
	class FString                                      ItemProperty;                                             // 0x0000(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst)
};

// ScriptStruct AkAudio.AkWwiseObjectDetails
// 0x0030
struct FAkWwiseObjectDetails
{
	class FString                                      ItemName;                                                 // 0x0000(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst)
	class FString                                      ItemPath;                                                 // 0x0010(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst)
	class FString                                      ItemId;                                                   // 0x0020(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst)
};

// ScriptStruct AkAudio.AkWwiseItemToControl
// 0x0040
struct FAkWwiseItemToControl
{
	struct FAkWwiseObjectDetails                       ItemPicked;                                               // 0x0000(0x0030) (Edit, EditConst)
	class FString                                      ItemPath;                                                 // 0x0030(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst)
};

// ScriptStruct AkAudio.AkMidiEventBase
// 0x0002
struct FAkMidiEventBase
{
	EAkMidiEventType                                   Type;                                                     // 0x0000(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      Chan;                                                     // 0x0001(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkMidiProgramChange
// 0x0001 (0x0003 - 0x0002)
struct FAkMidiProgramChange : public FAkMidiEventBase
{
	unsigned char                                      ProgramNum;                                               // 0x0002(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkMidiPitchBend
// 0x0006 (0x0008 - 0x0002)
struct FAkMidiPitchBend : public FAkMidiEventBase
{
	unsigned char                                      ValueLsb;                                                 // 0x0002(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      ValueMsb;                                                 // 0x0003(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                FullValue;                                                // 0x0004(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkMidiNoteOnOff
// 0x0002 (0x0004 - 0x0002)
struct FAkMidiNoteOnOff : public FAkMidiEventBase
{
	unsigned char                                      Note;                                                     // 0x0002(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      Velocity;                                                 // 0x0003(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkMidiNoteAftertouch
// 0x0002 (0x0004 - 0x0002)
struct FAkMidiNoteAftertouch : public FAkMidiEventBase
{
	unsigned char                                      Note;                                                     // 0x0002(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      Value;                                                    // 0x0003(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkMidiGeneric
// 0x0002 (0x0004 - 0x0002)
struct FAkMidiGeneric : public FAkMidiEventBase
{
	unsigned char                                      Param1;                                                   // 0x0002(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      Param2;                                                   // 0x0003(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkMidiChannelAftertouch
// 0x0001 (0x0003 - 0x0002)
struct FAkMidiChannelAftertouch : public FAkMidiEventBase
{
	unsigned char                                      Value;                                                    // 0x0002(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkMidiCc
// 0x0002 (0x0004 - 0x0002)
struct FAkMidiCc : public FAkMidiEventBase
{
	EAkMidiCcValues                                    Cc;                                                       // 0x0002(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      Value;                                                    // 0x0003(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkSegmentInfo
// 0x0024
struct FAkSegmentInfo
{
	int                                                CurrentPosition;                                          // 0x0000(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                PreEntryDuration;                                         // 0x0004(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                ActiveDuration;                                           // 0x0008(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                PostExitDuration;                                         // 0x000C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                RemainingLookAheadTime;                                   // 0x0010(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              BeatDuration;                                             // 0x0014(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              BarDuration;                                              // 0x0018(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              GridDuration;                                             // 0x001C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              GridOffset;                                               // 0x0020(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.AkPropertyToControl
// 0x0010
struct FAkPropertyToControl
{
	class FString                                      ItemProperty;                                             // 0x0000(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst)
};

// ScriptStruct AkAudio.AkPoly
// 0x0010
struct FAkPoly
{
	class UAkAcousticTexture*                          Texture;                                                  // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               EnableSurface;                                            // 0x0008(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0009(0x0007) MISSED OFFSET
};

// ScriptStruct AkAudio.AkWaapiSubscriptionId
// 0x0008
struct FAkWaapiSubscriptionId
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
};

// ScriptStruct AkAudio.AKWaapiJsonObject
// 0x0010
struct FAKWaapiJsonObject
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x0000(0x0010) MISSED OFFSET
};

// ScriptStruct AkAudio.AkWaapiUri
// 0x0010
struct FAkWaapiUri
{
	class FString                                      Uri;                                                      // 0x0000(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst)
};

// ScriptStruct AkAudio.AkWaapiFieldNames
// 0x0010
struct FAkWaapiFieldNames
{
	class FString                                      FieldName;                                                // 0x0000(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst)
};

// ScriptStruct AkAudio.AkAudioEventTrackKey
// 0x0020
struct FAkAudioEventTrackKey
{
	float                                              Time;                                                     // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0004(0x0004) MISSED OFFSET
	class UAkAudioEvent*                               AkAudioEvent;                                             // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, EditConst, IsPlainOldData)
	class FString                                      EventName;                                                // 0x0010(0x0010) (Edit, BlueprintVisible, ZeroConstructor, EditConst)
};

// ScriptStruct AkAudio.MovieSceneTangentDataSerializationHelper
// 0x0014
struct FMovieSceneTangentDataSerializationHelper
{
	float                                              ArriveTangent;                                            // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              LeaveTangent;                                             // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERichCurveTangentWeightMode>           TangentWeightMode;                                        // 0x0008(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
	float                                              ArriveTangentWeight;                                      // 0x000C(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              LeaveTangentWeight;                                       // 0x0010(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.MovieSceneFloatValueSerializationHelper
// 0x001C
struct FMovieSceneFloatValueSerializationHelper
{
	float                                              Value;                                                    // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERichCurveInterpMode>                  InterpMode;                                               // 0x0004(0x0001) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERichCurveTangentMode>                 TangentMode;                                              // 0x0005(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0006(0x0002) MISSED OFFSET
	struct FMovieSceneTangentDataSerializationHelper   Tangent;                                                  // 0x0008(0x0014)
};

// ScriptStruct AkAudio.MovieSceneFloatChannelSerializationHelper
// 0x0030
struct FMovieSceneFloatChannelSerializationHelper
{
	TEnumAsByte<ERichCurveExtrapolation>               PreInfinityExtrap;                                        // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERichCurveExtrapolation>               PostInfinityExtrap;                                       // 0x0001(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x0002(0x0006) MISSED OFFSET
	TArray<int>                                        Times;                                                    // 0x0008(0x0010) (ZeroConstructor)
	TArray<struct FMovieSceneFloatValueSerializationHelper> Values;                                                   // 0x0018(0x0010) (ZeroConstructor)
	float                                              DefaultValue;                                             // 0x0028(0x0004) (ZeroConstructor, IsPlainOldData)
	bool                                               bHasDefaultValue;                                         // 0x002C(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x002D(0x0003) MISSED OFFSET
};

// ScriptStruct AkAudio.AkAmbSoundCheckpointRecord
// 0x0001
struct FAkAmbSoundCheckpointRecord
{
	bool                                               bCurrentlyPlaying;                                        // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AkAudio.MovieSceneAkAudioEventTemplate
// 0x0008 (0x0028 - 0x0020)
struct FMovieSceneAkAudioEventTemplate : public FMovieSceneEvalTemplate
{
	class UMovieSceneAkAudioEventSection*              Section;                                                  // 0x0020(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// ScriptStruct AkAudio.MovieSceneAkAudioRTPCTemplate
// 0x0008 (0x0028 - 0x0020)
struct FMovieSceneAkAudioRTPCTemplate : public FMovieSceneEvalTemplate
{
	class UMovieSceneAkAudioRTPCSection*               Section;                                                  // 0x0020(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
