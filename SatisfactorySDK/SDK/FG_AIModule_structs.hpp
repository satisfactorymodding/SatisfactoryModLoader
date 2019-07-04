#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_GameplayTasks_classes.hpp"
#include "FG_GameplayTags_classes.hpp"
#include "FG_NavigationSystem_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum AIModule.EPathFollowingResult
enum class EPathFollowingResult : uint8_t
{
	Success                        = 0,
	Blocked                        = 1,
	OffPath                        = 2,
	Aborted                        = 3,
	Skipped_DEPRECATED             = 4,
	Invalid                        = 5,
	EPathFollowingResult_MAX       = 6
};


// Enum AIModule.EEnvQueryStatus
enum class EEnvQueryStatus : uint8_t
{
	Processing                     = 0,
	Success                        = 1,
	Failed                         = 2,
	Aborted                        = 3,
	OwnerLost                      = 4,
	MissingParam                   = 5,
	EEnvQueryStatus_MAX            = 6
};


// Enum AIModule.EAISenseNotifyType
enum class EAISenseNotifyType : uint8_t
{
	OnEveryPerception              = 0,
	OnPerceptionChange             = 1,
	EAISenseNotifyType_MAX         = 2
};


// Enum AIModule.EAITaskPriority
enum class EAITaskPriority : uint8_t
{
	Lowest                         = 0,
	Low                            = 1,
	AutonomousAI                   = 2,
	High                           = 3,
	Ultimate                       = 4,
	EAITaskPriority_MAX            = 5
};


// Enum AIModule.EGenericAICheck
enum class EGenericAICheck : uint8_t
{
	Less                           = 0,
	LessOrEqual                    = 1,
	Equal                          = 2,
	NotEqual                       = 3,
	GreaterOrEqual                 = 4,
	Greater                        = 5,
	IsTrue                         = 6,
	MAX                            = 7
};


// Enum AIModule.EAILockSource
enum class EAILockSource : uint8_t
{
	Animation                      = 0,
	Logic                          = 1,
	Script                         = 2,
	Gameplay                       = 3,
	MAX                            = 4
};


// Enum AIModule.EAIRequestPriority
enum class EAIRequestPriority : uint8_t
{
	SoftScript                     = 0,
	Logic                          = 1,
	HardScript                     = 2,
	Reaction                       = 3,
	Ultimate                       = 4,
	MAX                            = 5
};


// Enum AIModule.EPawnActionEventType
enum class EPawnActionEventType : uint8_t
{
	Invalid                        = 0,
	FailedToStart                  = 1,
	InstantAbort                   = 2,
	FinishedAborting               = 3,
	FinishedExecution              = 4,
	Push                           = 5,
	EPawnActionEventType_MAX       = 6
};


// Enum AIModule.EPawnActionResult
enum class EPawnActionResult : uint8_t
{
	NotStarted                     = 0,
	InProgress                     = 1,
	Success                        = 2,
	Failed                         = 3,
	Aborted                        = 4,
	EPawnActionResult_MAX          = 5
};


// Enum AIModule.EPawnActionAbortState
enum class EPawnActionAbortState : uint8_t
{
	NeverStarted                   = 0,
	NotBeingAborted                = 1,
	MarkPendingAbort               = 2,
	LatentAbortInProgress          = 3,
	AbortDone                      = 4,
	MAX                            = 5
};


// Enum AIModule.FAIDistanceType
enum class EFAIDistanceType : uint8_t
{
	Distance3D                     = 0,
	Distance2D                     = 1,
	DistanceZ                      = 2,
	MAX                            = 3
};


// Enum AIModule.EAIOptionFlag
enum class EAIOptionFlag : uint8_t
{
	Default                        = 0,
	Enable                         = 1,
	Disable                        = 2,
	MAX                            = 3
};


// Enum AIModule.EBTFlowAbortMode
enum class EBTFlowAbortMode : uint8_t
{
	None                           = 0,
	LowerPriority                  = 1,
	Self                           = 2,
	Both                           = 3,
	EBTFlowAbortMode_MAX           = 4
};


// Enum AIModule.EBTNodeResult
enum class EBTNodeResult : uint8_t
{
	Succeeded                      = 0,
	Failed                         = 1,
	Aborted                        = 2,
	InProgress                     = 3,
	EBTNodeResult_MAX              = 4
};


// Enum AIModule.ETextKeyOperation
enum class ETextKeyOperation : uint8_t
{
	Equal                          = 0,
	NotEqual                       = 1,
	Contain                        = 2,
	NotContain                     = 3,
	ETextKeyOperation_MAX          = 4
};


// Enum AIModule.EArithmeticKeyOperation
enum class EArithmeticKeyOperation : uint8_t
{
	Equal                          = 0,
	NotEqual                       = 1,
	Less                           = 2,
	LessOrEqual                    = 3,
	Greater                        = 4,
	GreaterOrEqual                 = 5,
	EArithmeticKeyOperation_MAX    = 6
};


// Enum AIModule.EBasicKeyOperation
enum class EBasicKeyOperation : uint8_t
{
	Set                            = 0,
	NotSet                         = 1,
	EBasicKeyOperation_MAX         = 2
};


// Enum AIModule.EBTParallelMode
enum class EBTParallelMode : uint8_t
{
	AbortBackground                = 0,
	WaitForBackground              = 1,
	EBTParallelMode_MAX            = 2
};


// Enum AIModule.EBTDecoratorLogic
enum class EBTDecoratorLogic : uint8_t
{
	Invalid                        = 0,
	Test                           = 1,
	And                            = 2,
	Or                             = 3,
	Not                            = 4,
	EBTDecoratorLogic_MAX          = 5
};


// Enum AIModule.EBTChildIndex
enum class EBTChildIndex : uint8_t
{
	FirstNode                      = 0,
	TaskNode                       = 1,
	EBTChildIndex_MAX              = 2
};


// Enum AIModule.EBTBlackboardRestart
enum class EBTBlackboardRestart : uint8_t
{
	ValueChange                    = 0,
	ResultChange                   = 1,
	EBTBlackboardRestart_MAX       = 2
};


// Enum AIModule.EBlackBoardEntryComparison
enum class EBlackBoardEntryComparison : uint8_t
{
	Equal                          = 0,
	NotEqual                       = 1,
	EBlackBoardEntryComparison_MAX = 2
};


// Enum AIModule.EPathExistanceQueryType
enum class EPathExistanceQueryType : uint8_t
{
	NavmeshRaycast2D               = 0,
	HierarchicalQuery              = 1,
	RegularPathFinding             = 2,
	EPathExistanceQueryType_MAX    = 3
};


// Enum AIModule.EPointOnCircleSpacingMethod
enum class EPointOnCircleSpacingMethod : uint8_t
{
	BySpaceBetween                 = 0,
	ByNumberOfPoints               = 1,
	EPointOnCircleSpacingMethod_MAX = 2
};


// Enum AIModule.EEQSNormalizationType
enum class EEQSNormalizationType : uint8_t
{
	Absolute                       = 0,
	RelativeToScores               = 1,
	EEQSNormalizationType_MAX      = 2
};


// Enum AIModule.EEnvTestDistance
enum class EEnvTestDistance : uint8_t
{
	Distance3D                     = 0,
	Distance2D                     = 1,
	DistanceZ                      = 2,
	DistanceAbsoluteZ              = 3,
	EEnvTestDistance_MAX           = 4
};


// Enum AIModule.EEnvTestDot
enum class EEnvTestDot : uint8_t
{
	Dot3D                          = 0,
	Dot2D                          = 1,
	EEnvTestDot_MAX                = 2
};


// Enum AIModule.EEnvTestPathfinding
enum class EEnvTestPathfinding : uint8_t
{
	PathExist                      = 0,
	PathCost                       = 1,
	PathLength                     = 2,
	EEnvTestPathfinding_MAX        = 3
};


// Enum AIModule.EEnvQueryTestClamping
enum class EEnvQueryTestClamping : uint8_t
{
	None                           = 0,
	SpecifiedValue                 = 1,
	FilterThreshold                = 2,
	EEnvQueryTestClamping_MAX      = 3
};


// Enum AIModule.EEnvDirection
enum class EEnvDirection : uint8_t
{
	TwoPoints                      = 0,
	Rotation                       = 1,
	EEnvDirection_MAX              = 2
};


// Enum AIModule.EEnvOverlapShape
enum class EEnvOverlapShape : uint8_t
{
	Box                            = 0,
	Sphere                         = 1,
	Capsule                        = 2,
	EEnvOverlapShape_MAX           = 3
};


// Enum AIModule.EEnvTraceShape
enum class EEnvTraceShape : uint8_t
{
	Line                           = 0,
	Box                            = 1,
	Sphere                         = 2,
	Capsule                        = 3,
	EEnvTraceShape_MAX             = 4
};


// Enum AIModule.EEnvQueryTrace
enum class EEnvQueryTrace : uint8_t
{
	None                           = 0,
	Navigation                     = 1,
	Geometry                       = 2,
	NavigationOverLedges           = 3,
	EEnvQueryTrace_MAX             = 4
};


// Enum AIModule.EAIParamType
enum class EAIParamType : uint8_t
{
	Float                          = 0,
	Int                            = 1,
	Bool                           = 2,
	MAX                            = 3
};


// Enum AIModule.EEnvQueryParam
enum class EEnvQueryParam : uint8_t
{
	Float                          = 0,
	Int                            = 1,
	Bool                           = 2,
	EEnvQueryParam_MAX             = 3
};


// Enum AIModule.EEnvQueryRunMode
enum class EEnvQueryRunMode : uint8_t
{
	SingleResult                   = 0,
	RandomBest5Pct                 = 1,
	RandomBest25Pct                = 2,
	AllMatching                    = 3,
	EEnvQueryRunMode_MAX           = 4
};


// Enum AIModule.EEnvTestScoreOperator
enum class EEnvTestScoreOperator : uint8_t
{
	AverageScore                   = 0,
	MinScore                       = 1,
	MaxScore                       = 2,
	EEnvTestScoreOperator_MAX      = 3
};


// Enum AIModule.EEnvTestFilterOperator
enum class EEnvTestFilterOperator : uint8_t
{
	AllPass                        = 0,
	AnyPass                        = 1,
	EEnvTestFilterOperator_MAX     = 2
};


// Enum AIModule.EEnvTestCost
enum class EEnvTestCost : uint8_t
{
	Low                            = 0,
	Medium                         = 1,
	High                           = 2,
	EEnvTestCost_MAX               = 3
};


// Enum AIModule.EEnvTestWeight
enum class EEnvTestWeight : uint8_t
{
	None                           = 0,
	Square                         = 1,
	Inverse                        = 2,
	Unused                         = 3,
	Constant                       = 4,
	Skip                           = 5,
	EEnvTestWeight_MAX             = 6
};


// Enum AIModule.EEnvTestScoreEquation
enum class EEnvTestScoreEquation : uint8_t
{
	Linear                         = 0,
	Square                         = 1,
	InverseLinear                  = 2,
	SquareRoot                     = 3,
	Constant                       = 4,
	EEnvTestScoreEquation_MAX      = 5
};


// Enum AIModule.EEnvTestFilterType
enum class EEnvTestFilterType : uint8_t
{
	Minimum                        = 0,
	Maximum                        = 1,
	Range                          = 2,
	Match                          = 3,
	EEnvTestFilterType_MAX         = 4
};


// Enum AIModule.EEnvTestPurpose
enum class EEnvTestPurpose : uint8_t
{
	Filter                         = 0,
	Score                          = 1,
	FilterAndScore                 = 2,
	EEnvTestPurpose_MAX            = 3
};


// Enum AIModule.EEnvQueryHightlightMode
enum class EEnvQueryHightlightMode : uint8_t
{
	All                            = 0,
	Best5Pct                       = 1,
	Best25Pct                      = 2,
	EEnvQueryHightlightMode_MAX    = 3
};


// Enum AIModule.ETeamAttitude
enum class ETeamAttitude : uint8_t
{
	Friendly                       = 0,
	Neutral                        = 1,
	Hostile                        = 2,
	ETeamAttitude_MAX              = 3
};


// Enum AIModule.EPathFollowingRequestResult
enum class EPathFollowingRequestResult : uint8_t
{
	Failed                         = 0,
	AlreadyAtGoal                  = 1,
	RequestSuccessful              = 2,
	EPathFollowingRequestResult_MAX = 3
};


// Enum AIModule.EPathFollowingAction
enum class EPathFollowingAction : uint8_t
{
	Error                          = 0,
	NoMove                         = 1,
	DirectMove                     = 2,
	PartialPath                    = 3,
	PathToGoal                     = 4,
	EPathFollowingAction_MAX       = 5
};


// Enum AIModule.EPathFollowingStatus
enum class EPathFollowingStatus : uint8_t
{
	Idle                           = 0,
	Waiting                        = 1,
	Paused                         = 2,
	Moving                         = 3,
	EPathFollowingStatus_MAX       = 4
};


// Enum AIModule.EPawnActionFailHandling
enum class EPawnActionFailHandling : uint8_t
{
	RequireSuccess                 = 0,
	IgnoreFailure                  = 1,
	EPawnActionFailHandling_MAX    = 2
};


// Enum AIModule.EPawnSubActionTriggeringPolicy
enum class EPawnSubActionTriggeringPolicy : uint8_t
{
	CopyBeforeTriggering           = 0,
	ReuseInstances                 = 1,
	EPawnSubActionTriggeringPolicy_MAX = 2
};


// Enum AIModule.EPawnActionMoveMode
enum class EPawnActionMoveMode : uint8_t
{
	UsePathfinding                 = 0,
	StraightLine                   = 1,
	EPawnActionMoveMode_MAX        = 2
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct AIModule.EnvTraceData
// 0x0030
struct FEnvTraceData
{
	int                                                VersionNum;                                               // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0004(0x0004) MISSED OFFSET
	class UClass*                                      NavigationFilter;                                         // 0x0008(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ProjectDown;                                              // 0x0010(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ProjectUp;                                                // 0x0014(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ExtentX;                                                  // 0x0018(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ExtentY;                                                  // 0x001C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ExtentZ;                                                  // 0x0020(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              PostProjectionVerticalOffset;                             // 0x0024(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<ETraceTypeQuery>                       TraceChannel;                                             // 0x0028(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<ECollisionChannel>                     SerializedChannel;                                        // 0x0029(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EEnvTraceShape>                        TraceShape;                                               // 0x002A(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EEnvQueryTrace>                        TraceMode;                                                // 0x002B(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      bTraceComplex : 1;                                        // 0x002C(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      bOnlyBlockingHits : 1;                                    // 0x002C(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      bCanTraceOnNavMesh : 1;                                   // 0x002C(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      bCanTraceOnGeometry : 1;                                  // 0x002C(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      bCanDisableTrace : 1;                                     // 0x002C(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      bCanProjectDown : 1;                                      // 0x002C(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData01[0x3];                                       // 0x002D(0x0003) MISSED OFFSET
};

// ScriptStruct AIModule.AIDataProviderValue
// 0x0020
struct FAIDataProviderValue
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
	class UProperty*                                   CachedProperty;                                           // 0x0008(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UAIDataProvider*                             DataBinding;                                              // 0x0010(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       DataField;                                                // 0x0018(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.AIDataProviderTypedValue
// 0x0008 (0x0028 - 0x0020)
struct FAIDataProviderTypedValue : public FAIDataProviderValue
{
	class UClass*                                      PropertyType;                                             // 0x0020(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.AIDataProviderBoolValue
// 0x0008 (0x0030 - 0x0028)
struct FAIDataProviderBoolValue : public FAIDataProviderTypedValue
{
	bool                                               DefaultValue;                                             // 0x0028(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0029(0x0007) MISSED OFFSET
};

// ScriptStruct AIModule.AIDataProviderFloatValue
// 0x0008 (0x0030 - 0x0028)
struct FAIDataProviderFloatValue : public FAIDataProviderTypedValue
{
	float                                              DefaultValue;                                             // 0x0028(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x002C(0x0004) MISSED OFFSET
};

// ScriptStruct AIModule.AIRequestID
// 0x0004
struct FAIRequestID
{
	uint32_t                                           RequestID;                                                // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.AIStimulus
// 0x0048
struct FAIStimulus
{
	float                                              Age;                                                      // 0x0000(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ExpirationAge;                                            // 0x0004(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Strength;                                                 // 0x0008(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     StimulusLocation;                                         // 0x000C(0x000C) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReceiverLocation;                                         // 0x0018(0x000C) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0024(0x0004) MISSED OFFSET
	struct FName                                       Tag;                                                      // 0x0028(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0030(0x0010) MISSED OFFSET
	unsigned char                                      UnknownData02 : 1;                                        // 0x0040(0x0001)
	unsigned char                                      bSuccessfullySensed : 1;                                  // 0x0040(0x0001) (BlueprintVisible)
	unsigned char                                      UnknownData03[0x7];                                       // 0x0041(0x0007) MISSED OFFSET
};

// ScriptStruct AIModule.ActorPerceptionBlueprintInfo
// 0x0020
struct FActorPerceptionBlueprintInfo
{
	class AActor*                                      Target;                                                   // 0x0000(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TArray<struct FAIStimulus>                         LastSensedStimuli;                                        // 0x0008(0x0010) (BlueprintVisible, ZeroConstructor)
	unsigned char                                      bIsHostile : 1;                                           // 0x0018(0x0001) (BlueprintVisible)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0019(0x0007) MISSED OFFSET
};

// ScriptStruct AIModule.AIDamageEvent
// 0x0030
struct FAIDamageEvent
{
	float                                              amount;                                                   // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // 0x0004(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitLocation;                                              // 0x0010(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
	class AActor*                                      damagedActor;                                             // 0x0020(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Instigator;                                               // 0x0028(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.AINoiseEvent
// 0x0030
struct FAINoiseEvent
{
	unsigned char                                      UnknownData00[0x4];                                       // 0x0000(0x0004) MISSED OFFSET
	struct FVector                                     NoiseLocation;                                            // 0x0004(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Loudness;                                                 // 0x0010(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              MaxRange;                                                 // 0x0014(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Instigator;                                               // 0x0018(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FName                                       Tag;                                                      // 0x0020(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
};

// ScriptStruct AIModule.AIPredictionEvent
// 0x0018
struct FAIPredictionEvent
{
	class AActor*                                      Requestor;                                                // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	class AActor*                                      PredictedActor;                                           // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0010(0x0008) MISSED OFFSET
};

// ScriptStruct AIModule.AITeamStimulusEvent
// 0x0038
struct FAITeamStimulusEvent
{
	unsigned char                                      UnknownData00[0x28];                                      // 0x0000(0x0028) MISSED OFFSET
	class AActor*                                      Broadcaster;                                              // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData)
	class AActor*                                      Enemy;                                                    // 0x0030(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.AITouchEvent
// 0x0020
struct FAITouchEvent
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x0000(0x0010) MISSED OFFSET
	class AActor*                                      TouchReceiver;                                            // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // 0x0018(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.AISenseAffiliationFilter
// 0x0004
struct FAISenseAffiliationFilter
{
	unsigned char                                      bDetectEnemies : 1;                                       // 0x0000(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bDetectNeutrals : 1;                                      // 0x0000(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bDetectFriendlies : 1;                                    // 0x0000(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
};

// ScriptStruct AIModule.AIMoveRequest
// 0x0040
struct FAIMoveRequest
{
	class AActor*                                      GoalActor;                                                // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x38];                                      // 0x0008(0x0038) MISSED OFFSET
};

// ScriptStruct AIModule.BTDecoratorLogic
// 0x0004
struct FBTDecoratorLogic
{
	TEnumAsByte<EBTDecoratorLogic>                     Operation;                                                // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1];                                       // 0x0001(0x0001) MISSED OFFSET
	uint16_t                                           Number;                                                   // 0x0002(0x0002) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.BehaviorTreeTemplateInfo
// 0x0018
struct FBehaviorTreeTemplateInfo
{
	class UBehaviorTree*                               Asset;                                                    // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	class UBTCompositeNode*                            Template;                                                 // 0x0008(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0010(0x0008) MISSED OFFSET
};

// ScriptStruct AIModule.BlackboardEntry
// 0x0018
struct FBlackboardEntry
{
	struct FName                                       EntryName;                                                // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UBlackboardKeyType*                          KeyType;                                                  // 0x0008(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      bInstanceSynced : 1;                                      // 0x0010(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0011(0x0007) MISSED OFFSET
};

// ScriptStruct AIModule.BTCompositeChild
// 0x0030
struct FBTCompositeChild
{
	class UBTCompositeNode*                            ChildComposite;                                           // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	class UBTTaskNode*                                 ChildTask;                                                // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData)
	TArray<class UBTDecorator*>                        Decorators;                                               // 0x0010(0x0010) (ZeroConstructor)
	TArray<struct FBTDecoratorLogic>                   DecoratorOps;                                             // 0x0020(0x0010) (ZeroConstructor)
};

// ScriptStruct AIModule.BlackboardKeySelector
// 0x0028
struct FBlackboardKeySelector
{
	TArray<class UBlackboardKeyType*>                  AllowedTypes;                                             // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor, Transient)
	struct FName                                       SelectedKeyName;                                          // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, IsPlainOldData)
	class UClass*                                      SelectedKeyType;                                          // 0x0018(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, Transient, IsPlainOldData)
	unsigned char                                      SelectedKeyID;                                            // 0x0020(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, Transient, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0021(0x0003) MISSED OFFSET
	unsigned char                                      bNoneIsAllowedValue : 1;                                  // 0x0024(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0025(0x0003) MISSED OFFSET
};

// ScriptStruct AIModule.AIDynamicParam
// 0x0038
struct FAIDynamicParam
{
	struct FName                                       ParamName;                                                // 0x0000(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData)
	EAIParamType                                       ParamType;                                                // 0x0008(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
	float                                              Value;                                                    // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FBlackboardKeySelector                      BBKey;                                                    // 0x0010(0x0028) (Edit, BlueprintVisible)
};

// ScriptStruct AIModule.EQSParametrizedQueryExecutionRequest
// 0x0048
struct FEQSParametrizedQueryExecutionRequest
{
	class UEnvQuery*                                   QueryTemplate;                                            // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<struct FAIDynamicParam>                     QueryConfig;                                              // 0x0008(0x0010) (Edit, ZeroConstructor)
	struct FBlackboardKeySelector                      EQSQueryBlackboardKey;                                    // 0x0018(0x0028) (Edit)
	TEnumAsByte<EEnvQueryRunMode>                      RunMode;                                                  // 0x0040(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0041(0x0003) MISSED OFFSET
	unsigned char                                      bUseBBKeyForQueryTemplate : 1;                            // 0x0044(0x0001) (Edit)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0045(0x0003) MISSED OFFSET
};

// ScriptStruct AIModule.EnvNamedValue
// 0x0010
struct FEnvNamedValue
{
	struct FName                                       ParamName;                                                // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	EAIParamType                                       ParamType;                                                // 0x0008(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
	float                                              Value;                                                    // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.CrowdAvoidanceConfig
// 0x001C
struct FCrowdAvoidanceConfig
{
	float                                              VelocityBias;                                             // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              DesiredVelocityWeight;                                    // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              CurrentVelocityWeight;                                    // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SideBiasWeight;                                           // 0x000C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ImpactTimeWeight;                                         // 0x0010(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ImpactTimeRange;                                          // 0x0014(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      CustomPatternIdx;                                         // 0x0018(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      AdaptiveDivisions;                                        // 0x0019(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      AdaptiveRings;                                            // 0x001A(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      AdaptiveDepth;                                            // 0x001B(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.CrowdAvoidanceSamplingPattern
// 0x0020
struct FCrowdAvoidanceSamplingPattern
{
	TArray<float>                                      Angles;                                                   // 0x0000(0x0010) (Edit, ZeroConstructor)
	TArray<float>                                      Radii;                                                    // 0x0010(0x0010) (Edit, ZeroConstructor)
};

// ScriptStruct AIModule.AIDataProviderIntValue
// 0x0008 (0x0030 - 0x0028)
struct FAIDataProviderIntValue : public FAIDataProviderTypedValue
{
	int                                                DefaultValue;                                             // 0x0028(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x002C(0x0004) MISSED OFFSET
};

// ScriptStruct AIModule.EnvDirection
// 0x0020
struct FEnvDirection
{
	class UClass*                                      LineFrom;                                                 // 0x0000(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      LineTo;                                                   // 0x0008(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      Rotation;                                                 // 0x0010(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EEnvDirection>                         DirMode;                                                  // 0x0018(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0019(0x0007) MISSED OFFSET
};

// ScriptStruct AIModule.EnvQueryInstanceCache
// 0x0178
struct FEnvQueryInstanceCache
{
	class UEnvQuery*                                   Template;                                                 // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x170];                                     // 0x0008(0x0170) MISSED OFFSET
};

// ScriptStruct AIModule.EnvOverlapData
// 0x0020
struct FEnvOverlapData
{
	float                                              ExtentX;                                                  // 0x0000(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ExtentY;                                                  // 0x0004(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ExtentZ;                                                  // 0x0008(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FVector                                     ShapeOffset;                                              // 0x000C(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<ECollisionChannel>                     OverlapChannel;                                           // 0x0018(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TEnumAsByte<EEnvOverlapShape>                      OverlapShape;                                             // 0x0019(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x001A(0x0002) MISSED OFFSET
	unsigned char                                      bOnlyBlockingHits : 1;                                    // 0x001C(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      bOverlapComplex : 1;                                      // 0x001C(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData01[0x3];                                       // 0x001D(0x0003) MISSED OFFSET
};

// ScriptStruct AIModule.PawnActionStack
// 0x0008
struct FPawnActionStack
{
	class UPawnAction*                                 TopAction;                                                // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.PawnActionEvent
// 0x0018
struct FPawnActionEvent
{
	class UPawnAction*                                 Action;                                                   // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0008(0x0010) MISSED OFFSET
};

// ScriptStruct AIModule.AIDataProviderStructValue
// 0x0010 (0x0030 - 0x0020)
struct FAIDataProviderStructValue : public FAIDataProviderValue
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x0020(0x0010) MISSED OFFSET
};

// ScriptStruct AIModule.AISightEvent
// 0x0018
struct FAISightEvent
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
	class AActor*                                      SeenActor;                                                // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData)
	class AActor*                                      Observer;                                                 // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AIModule.EnvQueryRequest
// 0x0068
struct FEnvQueryRequest
{
	class UEnvQuery*                                   QueryTemplate;                                            // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	class UObject*                                     Owner;                                                    // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData)
	class UWorld*                                      World;                                                    // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x50];                                      // 0x0018(0x0050) MISSED OFFSET
};

// ScriptStruct AIModule.EnvQueryResult
// 0x0040
struct FEnvQueryResult
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x0000(0x0010) MISSED OFFSET
	class UClass*                                      ItemType;                                                 // 0x0010(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x14];                                      // 0x0018(0x0014) MISSED OFFSET
	int                                                OptionIndex;                                              // 0x002C(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                QueryID;                                                  // 0x0030(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0xC];                                       // 0x0034(0x000C) MISSED OFFSET
};

// ScriptStruct AIModule.GenericTeamId
// 0x0001
struct FGenericTeamId
{
	unsigned char                                      TeamID;                                                   // 0x0000(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
