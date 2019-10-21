#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_AnimationCore_classes.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum AnimGraphRuntime.ESphericalLimitType
enum class ESphericalLimitType : uint8_t
{
	Inner                          = 0,
	Outer                          = 1,
	ESphericalLimitType_MAX        = 2
};


// Enum AnimGraphRuntime.AnimPhysSimSpaceType
enum class EAnimPhysSimSpaceType : uint8_t
{
	Component                      = 0,
	Actor                          = 1,
	World                          = 2,
	RootRelative                   = 3,
	BoneRelative                   = 4,
	AnimPhysSimSpaceType_MAX       = 5
};


// Enum AnimGraphRuntime.AnimPhysLinearConstraintType
enum class EAnimPhysLinearConstraintType : uint8_t
{
	Free                           = 0,
	Limited                        = 1,
	AnimPhysLinearConstraintType_MAX = 2
};


// Enum AnimGraphRuntime.AnimPhysAngularConstraintType
enum class EAnimPhysAngularConstraintType : uint8_t
{
	Angular                        = 0,
	Cone                           = 1,
	AnimPhysAngularConstraintType_MAX = 2
};


// Enum AnimGraphRuntime.EDrivenDestinationMode
enum class EDrivenDestinationMode : uint8_t
{
	Bone                           = 0,
	MorphTarget                    = 1,
	MaterialParameter              = 2,
	EDrivenDestinationMode_MAX     = 3
};


// Enum AnimGraphRuntime.EDrivenBoneModificationMode
enum class EDrivenBoneModificationMode : uint8_t
{
	AddToInput                     = 0,
	ReplaceComponent               = 1,
	AddToRefPose                   = 2,
	EDrivenBoneModificationMode_MAX = 3
};


// Enum AnimGraphRuntime.EConstraintOffsetOption
enum class EConstraintOffsetOption : uint8_t
{
	None                           = 0,
	Offset_RefPose                 = 1,
	EConstraintOffsetOption_MAX    = 2
};


// Enum AnimGraphRuntime.CopyBoneDeltaMode
enum class ECopyBoneDeltaMode : uint8_t
{
	Accumulate                     = 0,
	Copy                           = 1,
	CopyBoneDeltaMode_MAX          = 2
};


// Enum AnimGraphRuntime.EInterpolationBlend
enum class EInterpolationBlend : uint8_t
{
	Linear                         = 0,
	Cubic                          = 1,
	Sinusoidal                     = 2,
	EaseInOutExponent2             = 3,
	EaseInOutExponent3             = 4,
	EaseInOutExponent4             = 5,
	EaseInOutExponent5             = 6,
	MAX                            = 7
};


// Enum AnimGraphRuntime.EBoneModificationMode
enum class EBoneModificationMode : uint8_t
{
	BMM_Ignore                     = 0,
	BMM_Replace                    = 1,
	BMM_Additive                   = 2,
	BMM_MAX                        = 3
};


// Enum AnimGraphRuntime.EModifyCurveApplyMode
enum class EModifyCurveApplyMode : uint8_t
{
	Add                            = 0,
	Scale                          = 1,
	Blend                          = 2,
	WeightedMovingAverage          = 3,
	RemapCurve                     = 4,
	EModifyCurveApplyMode_MAX      = 5
};


// Enum AnimGraphRuntime.EPoseDriverOutput
enum class EPoseDriverOutput : uint8_t
{
	DrivePoses                     = 0,
	DriveCurves                    = 1,
	EPoseDriverOutput_MAX          = 2
};


// Enum AnimGraphRuntime.EPoseDriverSource
enum class EPoseDriverSource : uint8_t
{
	Rotation                       = 0,
	Translation                    = 1,
	EPoseDriverSource_MAX          = 2
};


// Enum AnimGraphRuntime.EPoseDriverType
enum class EPoseDriverType : uint8_t
{
	SwingAndTwist                  = 0,
	SwingOnly                      = 1,
	Translation                    = 2,
	EPoseDriverType_MAX            = 3
};


// Enum AnimGraphRuntime.ESnapshotSourceMode
enum class ESnapshotSourceMode : uint8_t
{
	NamedSnapshot                  = 0,
	SnapshotPin                    = 1,
	ESnapshotSourceMode_MAX        = 2
};


// Enum AnimGraphRuntime.ERefPoseType
enum class ERefPoseType : uint8_t
{
	EIT_LocalSpace                 = 0,
	EIT_Additive                   = 1,
	EIT_MAX                        = 2
};


// Enum AnimGraphRuntime.ESimulationSpace
enum class ESimulationSpace : uint8_t
{
	ComponentSpace                 = 0,
	WorldSpace                     = 1,
	BaseBoneSpace                  = 2,
	ESimulationSpace_MAX           = 3
};


// Enum AnimGraphRuntime.EScaleChainInitialLength
enum class EScaleChainInitialLength : uint8_t
{
	FixedDefaultLengthValue        = 0,
	Distance                       = 1,
	ChainLength                    = 2,
	EScaleChainInitialLength_MAX   = 3
};


// Enum AnimGraphRuntime.ESequenceEvalReinit
enum class ESequenceEvalReinit : uint8_t
{
	NoReset                        = 0,
	StartPosition                  = 1,
	ExplicitTime                   = 2,
	ESequenceEvalReinit_MAX        = 3
};


// Enum AnimGraphRuntime.ESplineBoneAxis
enum class ESplineBoneAxis : uint8_t
{
	X                              = 0,
	Y                              = 1,
	Z                              = 2,
	ESplineBoneAxis_MAX            = 3
};


// Enum AnimGraphRuntime.ERBFDistanceMethod
enum class ERBFDistanceMethod : uint8_t
{
	Euclidean                      = 0,
	Quaternion                     = 1,
	SwingAngle                     = 2,
	ERBFDistanceMethod_MAX         = 3
};


// Enum AnimGraphRuntime.ERBFFunctionType
enum class ERBFFunctionType : uint8_t
{
	Gaussian                       = 0,
	Exponential                    = 1,
	Linear                         = 2,
	Cubic                          = 3,
	Quintic                        = 4,
	ERBFFunctionType_MAX           = 5
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct AnimGraphRuntime.AnimNode_SkeletalControlBase
// 0x00C0 (0x00F0 - 0x0030)
struct FAnimNode_SkeletalControlBase : public FAnimNode_Base
{
	struct FComponentSpacePoseLink                     ComponentPose;                                            // 0x0030(0x0010) (Edit, BlueprintVisible)
	int                                                LODThreshold;                                             // 0x0040(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ActualAlpha;                                              // 0x0044(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	EAnimAlphaInputType                                AlphaInputType;                                           // 0x0048(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bAlphaBoolEnabled;                                        // 0x0049(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x004A(0x0002) MISSED OFFSET
	float                                              Alpha;                                                    // 0x004C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBias                             AlphaScaleBias;                                           // 0x0050(0x0008) (Edit, BlueprintVisible)
	struct FInputAlphaBoolBlend                        AlphaBoolBlend;                                           // 0x0058(0x0050) (Edit, BlueprintVisible)
	struct FName                                       AlphaCurveName;                                           // 0x00A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBiasClamp                        AlphaScaleBiasClamp;                                      // 0x00B0(0x0030) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData01[0x10];                                      // 0x00E0(0x0010) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_BlendSpacePlayer
// 0x00D0 (0x0128 - 0x0058)
struct FAnimNode_BlendSpacePlayer : public FAnimNode_AssetPlayerBase
{
	float                                              X;                                                        // 0x0058(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Y;                                                        // 0x005C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Z;                                                        // 0x0060(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              PlayRate;                                                 // 0x0064(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bLoop;                                                    // 0x0068(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0069(0x0003) MISSED OFFSET
	float                                              StartPosition;                                            // 0x006C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UBlendSpaceBase*                             BlendSpace;                                               // 0x0070(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bResetPlayTimeWhenBlendSpaceChanges;                      // 0x0078(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0079(0x0007) MISSED OFFSET
	struct FBlendFilter                                BlendFilter;                                              // 0x0080(0x0090)
	TArray<struct FBlendSampleData>                    BlendSampleDataCache;                                     // 0x0110(0x0010) (ZeroConstructor)
	class UBlendSpaceBase*                             PreviousBlendSpace;                                       // 0x0120(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.AnimNode_AimOffsetLookAt
// 0x00E8 (0x0210 - 0x0128)
struct FAnimNode_AimOffsetLookAt : public FAnimNode_BlendSpacePlayer
{
	struct FPoseLink                                   BasePose;                                                 // 0x0128(0x0010) (Edit, BlueprintVisible)
	int                                                LODThreshold;                                             // 0x0138(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bIsLODEnabled;                                            // 0x013C(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x013D(0x0003) MISSED OFFSET
	struct FVector                                     LookAtLocation;                                           // 0x0140(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x014C(0x0004) MISSED OFFSET
	struct FName                                       SourceSocketName;                                         // 0x0150(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FName                                       PivotSocketName;                                          // 0x0158(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     SocketAxis;                                               // 0x0160(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Alpha;                                                    // 0x016C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FBoneReference                              SocketBoneReference;                                      // 0x0170(0x0018)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0188(0x0008) MISSED OFFSET
	struct FTransform                                  SocketLocalTransform;                                     // 0x0190(0x0030) (IsPlainOldData)
	struct FBoneReference                              PivotSocketBoneReference;                                 // 0x01C0(0x0018)
	unsigned char                                      UnknownData03[0x8];                                       // 0x01D8(0x0008) MISSED OFFSET
	struct FTransform                                  PivotSocketLocalTransform;                                // 0x01E0(0x0030) (IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.AnimPhysConstraintSetup
// 0x005C
struct FAnimPhysConstraintSetup
{
	EAnimPhysLinearConstraintType                      LinearXLimitType;                                         // 0x0000(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EAnimPhysLinearConstraintType                      LinearYLimitType;                                         // 0x0001(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EAnimPhysLinearConstraintType                      LinearZLimitType;                                         // 0x0002(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1];                                       // 0x0003(0x0001) MISSED OFFSET
	struct FVector                                     LinearAxesMin;                                            // 0x0004(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     LinearAxesMax;                                            // 0x0010(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	EAnimPhysAngularConstraintType                     AngularConstraintType;                                    // 0x001C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EAnimPhysTwistAxis                                 TwistAxis;                                                // 0x001D(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x001E(0x0002) MISSED OFFSET
	float                                              ConeAngle;                                                // 0x0020(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              AngularXAngle;                                            // 0x0024(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              AngularYAngle;                                            // 0x0028(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	float                                              AngularZAngle;                                            // 0x002C(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FVector                                     AngularLimitsMin;                                         // 0x0030(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     AngularLimitsMax;                                         // 0x003C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	EAnimPhysTwistAxis                                 AngularTargetAxis;                                        // 0x0048(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0049(0x0003) MISSED OFFSET
	struct FVector                                     AngularTarget;                                            // 0x004C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bLinearFullyLocked;                                       // 0x0058(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x0059(0x0003) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimPhysPlanarLimit
// 0x0050
struct FAnimPhysPlanarLimit
{
	struct FBoneReference                              DrivingBone;                                              // 0x0000(0x0018) (Edit)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0018(0x0008) MISSED OFFSET
	struct FTransform                                  PlaneTransform;                                           // 0x0020(0x0030) (Edit, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.AnimPhysSphericalLimit
// 0x0030
struct FAnimPhysSphericalLimit
{
	struct FBoneReference                              DrivingBone;                                              // 0x0000(0x0018) (Edit)
	struct FVector                                     SphereLocalOffset;                                        // 0x0018(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              LimitRadius;                                              // 0x0024(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	ESphericalLimitType                                LimitType;                                                // 0x0028(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0029(0x0007) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_AnimDynamics
// 0x02B0 (0x03A0 - 0x00F0)
struct FAnimNode_AnimDynamics : public FAnimNode_SkeletalControlBase
{
	EAnimPhysSimSpaceType                              SimulationSpace;                                          // 0x00F0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00F1(0x0007) MISSED OFFSET
	struct FBoneReference                              RelativeSpaceBone;                                        // 0x00F8(0x0018) (Edit)
	bool                                               bChain;                                                   // 0x0110(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0111(0x0007) MISSED OFFSET
	struct FBoneReference                              BoundBone;                                                // 0x0118(0x0018) (Edit)
	struct FBoneReference                              ChainEnd;                                                 // 0x0130(0x0018) (Edit)
	struct FVector                                     BoxExtents;                                               // 0x0148(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     LocalJointOffset;                                         // 0x0154(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              GravityScale;                                             // 0x0160(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     GravityOverride;                                          // 0x0164(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bUseGravityOverride;                                      // 0x0170(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bLinearSpring;                                            // 0x0171(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bAngularSpring;                                           // 0x0172(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x1];                                       // 0x0173(0x0001) MISSED OFFSET
	float                                              LinearSpringConstant;                                     // 0x0174(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              AngularSpringConstant;                                    // 0x0178(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableWind;                                              // 0x017C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bWindWasEnabled;                                          // 0x017D(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData03[0x2];                                       // 0x017E(0x0002) MISSED OFFSET
	float                                              WindScale;                                                // 0x0180(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ComponentLinearAccScale;                                  // 0x0184(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ComponentLinearVelScale;                                  // 0x0190(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ComponentAppliedLinearAccClamp;                           // 0x019C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bOverrideLinearDamping;                                   // 0x01A8(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x3];                                       // 0x01A9(0x0003) MISSED OFFSET
	float                                              LinearDampingOverride;                                    // 0x01AC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bOverrideAngularDamping;                                  // 0x01B0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData05[0x3];                                       // 0x01B1(0x0003) MISSED OFFSET
	float                                              AngularDampingOverride;                                   // 0x01B4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bOverrideAngularBias;                                     // 0x01B8(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData06[0x3];                                       // 0x01B9(0x0003) MISSED OFFSET
	float                                              AngularBiasOverride;                                      // 0x01BC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bDoUpdate;                                                // 0x01C0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bDoEval;                                                  // 0x01C1(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData07[0x2];                                       // 0x01C2(0x0002) MISSED OFFSET
	int                                                NumSolverIterationsPreUpdate;                             // 0x01C4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                NumSolverIterationsPostUpdate;                            // 0x01C8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FAnimPhysConstraintSetup                    ConstraintSetup;                                          // 0x01CC(0x005C) (Edit)
	bool                                               bUsePlanarLimit;                                          // 0x0228(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData08[0x7];                                       // 0x0229(0x0007) MISSED OFFSET
	TArray<struct FAnimPhysPlanarLimit>                PlanarLimits;                                             // 0x0230(0x0010) (Edit, ZeroConstructor)
	bool                                               bUseSphericalLimits;                                      // 0x0240(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData09[0x7];                                       // 0x0241(0x0007) MISSED OFFSET
	TArray<struct FAnimPhysSphericalLimit>             SphericalLimits;                                          // 0x0248(0x0010) (Edit, ZeroConstructor)
	EAnimPhysCollisionType                             CollisionType;                                            // 0x0258(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData10[0x3];                                       // 0x0259(0x0003) MISSED OFFSET
	float                                              SphereCollisionRadius;                                    // 0x025C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ExternalForce;                                            // 0x0260(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData11[0x134];                                     // 0x026C(0x0134) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_ApplyAdditive
// 0x00C0 (0x00F0 - 0x0030)
struct FAnimNode_ApplyAdditive : public FAnimNode_Base
{
	struct FPoseLink                                   Base;                                                     // 0x0030(0x0010) (Edit, BlueprintVisible)
	struct FPoseLink                                   Additive;                                                 // 0x0040(0x0010) (Edit, BlueprintVisible)
	float                                              Alpha;                                                    // 0x0050(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBias                             AlphaScaleBias;                                           // 0x0054(0x0008) (Edit, BlueprintVisible)
	int                                                LODThreshold;                                             // 0x005C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ActualAlpha;                                              // 0x0060(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	EAnimAlphaInputType                                AlphaInputType;                                           // 0x0064(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bAlphaBoolEnabled;                                        // 0x0065(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0066(0x0002) MISSED OFFSET
	struct FInputAlphaBoolBlend                        AlphaBoolBlend;                                           // 0x0068(0x0050) (Edit, BlueprintVisible)
	struct FName                                       AlphaCurveName;                                           // 0x00B8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBiasClamp                        AlphaScaleBiasClamp;                                      // 0x00C0(0x0030) (Edit, BlueprintVisible)
};

// ScriptStruct AnimGraphRuntime.AngularRangeLimit
// 0x0030
struct FAngularRangeLimit
{
	struct FVector                                     LimitMin;                                                 // 0x0000(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     LimitMax;                                                 // 0x000C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FBoneReference                              Bone;                                                     // 0x0018(0x0018) (Edit)
};

// ScriptStruct AnimGraphRuntime.AnimNode_ApplyLimits
// 0x0020 (0x0110 - 0x00F0)
struct FAnimNode_ApplyLimits : public FAnimNode_SkeletalControlBase
{
	TArray<struct FAngularRangeLimit>                  AngularRangeLimits;                                       // 0x00F0(0x0010) (Edit, ZeroConstructor)
	TArray<struct FVector>                             AngularOffsets;                                           // 0x0100(0x0010) (Edit, BlueprintVisible, EditFixedSize, ZeroConstructor)
};

// ScriptStruct AnimGraphRuntime.BlendBoneByChannelEntry
// 0x0038
struct FBlendBoneByChannelEntry
{
	struct FBoneReference                              SourceBone;                                               // 0x0000(0x0018) (Edit)
	struct FBoneReference                              TargetBone;                                               // 0x0018(0x0018) (Edit)
	bool                                               bBlendTranslation;                                        // 0x0030(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bBlendRotation;                                           // 0x0031(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bBlendScale;                                              // 0x0032(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x5];                                       // 0x0033(0x0005) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_BlendBoneByChannel
// 0x0060 (0x0090 - 0x0030)
struct FAnimNode_BlendBoneByChannel : public FAnimNode_Base
{
	struct FPoseLink                                   A;                                                        // 0x0030(0x0010) (Edit, BlueprintVisible)
	struct FPoseLink                                   B;                                                        // 0x0040(0x0010) (Edit, BlueprintVisible)
	float                                              Alpha;                                                    // 0x0050(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBias                             AlphaScaleBias;                                           // 0x0054(0x0008) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData00[0x4];                                       // 0x005C(0x0004) MISSED OFFSET
	TArray<struct FBlendBoneByChannelEntry>            BoneDefinitions;                                          // 0x0060(0x0010) (Edit, ZeroConstructor)
	TEnumAsByte<EBoneControlSpace>                     TransformsSpace;                                          // 0x0070(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0071(0x0003) MISSED OFFSET
	float                                              InternalBlendAlpha;                                       // 0x0074(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	bool                                               bBIsRelevant;                                             // 0x0078(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0079(0x0007) MISSED OFFSET
	TArray<struct FBlendBoneByChannelEntry>            ValidBoneEntries;                                         // 0x0080(0x0010) (ZeroConstructor, Transient)
};

// ScriptStruct AnimGraphRuntime.AnimNode_BlendListBase
// 0x0098 (0x00C8 - 0x0030)
struct FAnimNode_BlendListBase : public FAnimNode_Base
{
	TArray<struct FPoseLink>                           BlendPose;                                                // 0x0030(0x0010) (Edit, BlueprintVisible, EditFixedSize, ZeroConstructor)
	TArray<float>                                      BlendTime;                                                // 0x0040(0x0010) (Edit, BlueprintVisible, EditFixedSize, ZeroConstructor)
	EAlphaBlendOption                                  BlendType;                                                // 0x0050(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0051(0x0007) MISSED OFFSET
	class UCurveFloat*                                 CustomBlendCurve;                                         // 0x0058(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UBlendProfile*                               BlendProfile;                                             // 0x0060(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<struct FAlphaBlend>                         Blends;                                                   // 0x0068(0x0010) (ZeroConstructor)
	TArray<float>                                      BlendWeights;                                             // 0x0078(0x0010) (ZeroConstructor)
	TArray<float>                                      RemainingBlendTimes;                                      // 0x0088(0x0010) (ZeroConstructor)
	int                                                LastActiveChildIndex;                                     // 0x0098(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x009C(0x0004) MISSED OFFSET
	TArray<struct FBlendSampleData>                    PerBoneSampleData;                                        // 0x00A0(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData02[0x10];                                      // 0x00B0(0x0010) MISSED OFFSET
	bool                                               bResetChildOnActivation;                                  // 0x00C0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x7];                                       // 0x00C1(0x0007) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_BlendListByBool
// 0x0008 (0x00D0 - 0x00C8)
struct FAnimNode_BlendListByBool : public FAnimNode_BlendListBase
{
	bool                                               bActiveValue;                                             // 0x00C8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00C9(0x0007) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_BlendListByEnum
// 0x0018 (0x00E0 - 0x00C8)
struct FAnimNode_BlendListByEnum : public FAnimNode_BlendListBase
{
	TArray<int>                                        EnumToPoseIndex;                                          // 0x00C8(0x0010) (ZeroConstructor)
	unsigned char                                      ActiveEnumValue;                                          // 0x00D8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00D9(0x0007) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_BlendListByInt
// 0x0008 (0x00D0 - 0x00C8)
struct FAnimNode_BlendListByInt : public FAnimNode_BlendListBase
{
	int                                                ActiveChildIndex;                                         // 0x00C8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x00CC(0x0004) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_BlendSpaceEvaluator
// 0x0008 (0x0130 - 0x0128)
struct FAnimNode_BlendSpaceEvaluator : public FAnimNode_BlendSpacePlayer
{
	float                                              NormalizedTime;                                           // 0x0128(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x012C(0x0004) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_BoneDrivenController
// 0x0078 (0x0168 - 0x00F0)
struct FAnimNode_BoneDrivenController : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              SourceBone;                                               // 0x00F0(0x0018) (Edit)
	TEnumAsByte<EComponentType>                        SourceComponent;                                          // 0x0108(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0109(0x0007) MISSED OFFSET
	class UCurveFloat*                                 DrivingCurve;                                             // 0x0110(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              Multiplier;                                               // 0x0118(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bUseRange;                                                // 0x011C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x011D(0x0003) MISSED OFFSET
	float                                              RangeMin;                                                 // 0x0120(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              RangeMax;                                                 // 0x0124(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              RemappedMin;                                              // 0x0128(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              RemappedMax;                                              // 0x012C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	EDrivenDestinationMode                             DestinationMode;                                          // 0x0130(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0131(0x0007) MISSED OFFSET
	struct FName                                       ParameterName;                                            // 0x0138(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FBoneReference                              TargetBone;                                               // 0x0140(0x0018) (Edit)
	TEnumAsByte<EComponentType>                        TargetComponent;                                          // 0x0158(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x0159(0x0003) MISSED OFFSET
	unsigned char                                      bAffectTargetTranslationX : 1;                            // 0x015C(0x0001) (Edit)
	unsigned char                                      bAffectTargetTranslationY : 1;                            // 0x015C(0x0001) (Edit)
	unsigned char                                      bAffectTargetTranslationZ : 1;                            // 0x015C(0x0001) (Edit)
	unsigned char                                      bAffectTargetRotationX : 1;                               // 0x015C(0x0001) (Edit)
	unsigned char                                      bAffectTargetRotationY : 1;                               // 0x015C(0x0001) (Edit)
	unsigned char                                      bAffectTargetRotationZ : 1;                               // 0x015C(0x0001) (Edit)
	unsigned char                                      bAffectTargetScaleX : 1;                                  // 0x015C(0x0001) (Edit)
	unsigned char                                      bAffectTargetScaleY : 1;                                  // 0x015C(0x0001) (Edit)
	unsigned char                                      bAffectTargetScaleZ : 1;                                  // 0x015D(0x0001) (Edit)
	unsigned char                                      UnknownData04[0x2];                                       // 0x015E(0x0002) MISSED OFFSET
	EDrivenBoneModificationMode                        ModificationMode;                                         // 0x0160(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData05[0x7];                                       // 0x0161(0x0007) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.SocketReference
// 0x0040
struct FSocketReference
{
	struct FName                                       SocketName;                                               // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x38];                                      // 0x0008(0x0038) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.BoneSocketTarget
// 0x0060
struct FBoneSocketTarget
{
	bool                                               bUseSocket;                                               // 0x0000(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
	struct FBoneReference                              BoneReference;                                            // 0x0008(0x0018) (Edit)
	struct FSocketReference                            SocketReference;                                          // 0x0020(0x0040) (Edit)
};

// ScriptStruct AnimGraphRuntime.AnimNode_CCDIK
// 0x00C0 (0x01B0 - 0x00F0)
struct FAnimNode_CCDIK : public FAnimNode_SkeletalControlBase
{
	struct FVector                                     EffectorLocation;                                         // 0x00F0(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneControlSpace>                     EffectorLocationSpace;                                    // 0x00FC(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x00FD(0x0003) MISSED OFFSET
	struct FBoneSocketTarget                           EffectorTarget;                                           // 0x0100(0x0060) (Edit)
	struct FBoneReference                              TipBone;                                                  // 0x0160(0x0018) (Edit)
	struct FBoneReference                              RootBone;                                                 // 0x0178(0x0018) (Edit)
	float                                              Precision;                                                // 0x0190(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                MaxIterations;                                            // 0x0194(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bStartFromTail;                                           // 0x0198(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableRotationLimit;                                     // 0x0199(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x019A(0x0006) MISSED OFFSET
	TArray<float>                                      RotationLimitPerJoints;                                   // 0x01A0(0x0010) (Edit, EditFixedSize, ZeroConstructor)
};

// ScriptStruct AnimGraphRuntime.Constraint
// 0x0028
struct FConstraint
{
	struct FBoneReference                              TargetBone;                                               // 0x0000(0x0018) (Edit)
	EConstraintOffsetOption                            OffsetOption;                                             // 0x0018(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	ETransformConstraintType                           TransformType;                                            // 0x0019(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	struct FFilterOptionPerAxis                        PerAxis;                                                  // 0x001A(0x0003) (Edit)
	unsigned char                                      UnknownData00[0xB];                                       // 0x001D(0x000B) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_Constraint
// 0x0048 (0x0138 - 0x00F0)
struct FAnimNode_Constraint : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              BoneToModify;                                             // 0x00F0(0x0018) (Edit)
	TArray<struct FConstraint>                         ConstraintSetup;                                          // 0x0108(0x0010) (Edit, ZeroConstructor)
	TArray<float>                                      ConstraintWeights;                                        // 0x0118(0x0010) (Edit, EditFixedSize, ZeroConstructor)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0128(0x0010) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_CopyBone
// 0x0038 (0x0128 - 0x00F0)
struct FAnimNode_CopyBone : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              SourceBone;                                               // 0x00F0(0x0018) (Edit)
	struct FBoneReference                              TargetBone;                                               // 0x0108(0x0018) (Edit)
	bool                                               bCopyTranslation;                                         // 0x0120(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bCopyRotation;                                            // 0x0121(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bCopyScale;                                               // 0x0122(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneControlSpace>                     ControlSpace;                                             // 0x0123(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0124(0x0004) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_CopyBoneDelta
// 0x0040 (0x0130 - 0x00F0)
struct FAnimNode_CopyBoneDelta : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              SourceBone;                                               // 0x00F0(0x0018) (Edit)
	struct FBoneReference                              TargetBone;                                               // 0x0108(0x0018) (Edit)
	bool                                               bCopyTranslation;                                         // 0x0120(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bCopyRotation;                                            // 0x0121(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bCopyScale;                                               // 0x0122(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	ECopyBoneDeltaMode                                 CopyMode;                                                 // 0x0123(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              TranslationMultiplier;                                    // 0x0124(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              RotationMultiplier;                                       // 0x0128(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ScaleMultiplier;                                          // 0x012C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.AnimNode_CopyPoseFromMesh
// 0x00B8 (0x00E8 - 0x0030)
struct FAnimNode_CopyPoseFromMesh : public FAnimNode_Base
{
	TWeakObjectPtr<class USkeletalMeshComponent>       SourceMeshComponent;                                      // 0x0030(0x0008) (Edit, BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               bUseAttachedParent;                                       // 0x0038(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bCopyCurves;                                              // 0x0039(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0xAE];                                      // 0x003A(0x00AE) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_CurveSource
// 0x0030 (0x0060 - 0x0030)
struct FAnimNode_CurveSource : public FAnimNode_Base
{
	struct FPoseLink                                   SourcePose;                                               // 0x0030(0x0010) (Edit, BlueprintVisible)
	struct FName                                       SourceBinding;                                            // 0x0040(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Alpha;                                                    // 0x0048(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x004C(0x0004) MISSED OFFSET
	TScriptInterface<class UCurveSourceInterface>      CurveSource;                                              // 0x0050(0x0010) (ZeroConstructor, Transient, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.AnimNode_Fabrik
// 0x0100 (0x01F0 - 0x00F0)
struct FAnimNode_Fabrik : public FAnimNode_SkeletalControlBase
{
	struct FTransform                                  EffectorTransform;                                        // 0x00F0(0x0030) (Edit, BlueprintVisible, IsPlainOldData)
	TEnumAsByte<EBoneControlSpace>                     EffectorTransformSpace;                                   // 0x0120(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0121(0x0007) MISSED OFFSET
	struct FBoneReference                              EffectorTransformBone;                                    // 0x0128(0x0018) (Deprecated)
	struct FBoneSocketTarget                           EffectorTarget;                                           // 0x0140(0x0060) (Edit)
	TEnumAsByte<EBoneRotationSource>                   EffectorRotationSource;                                   // 0x01A0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x01A1(0x0007) MISSED OFFSET
	struct FBoneReference                              TipBone;                                                  // 0x01A8(0x0018) (Edit)
	struct FBoneReference                              RootBone;                                                 // 0x01C0(0x0018) (Edit)
	float                                              Precision;                                                // 0x01D8(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                MaxIterations;                                            // 0x01DC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableDebugDraw;                                         // 0x01E0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0xF];                                       // 0x01E1(0x000F) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_HandIKRetargeting
// 0x0078 (0x0168 - 0x00F0)
struct FAnimNode_HandIKRetargeting : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              RightHandFK;                                              // 0x00F0(0x0018) (Edit)
	struct FBoneReference                              LeftHandFK;                                               // 0x0108(0x0018) (Edit)
	struct FBoneReference                              RightHandIK;                                              // 0x0120(0x0018) (Edit)
	struct FBoneReference                              LeftHandIK;                                               // 0x0138(0x0018) (Edit)
	TArray<struct FBoneReference>                      IKBonesToMove;                                            // 0x0150(0x0010) (Edit, ZeroConstructor)
	float                                              HandFKWeight;                                             // 0x0160(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0164(0x0004) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_LayeredBoneBlend
// 0x00A8 (0x00D8 - 0x0030)
struct FAnimNode_LayeredBoneBlend : public FAnimNode_Base
{
	struct FPoseLink                                   BasePose;                                                 // 0x0030(0x0010) (Edit, BlueprintVisible)
	TArray<struct FPoseLink>                           BlendPoses;                                               // 0x0040(0x0010) (Edit, BlueprintVisible, EditFixedSize, ZeroConstructor)
	TArray<struct FInputBlendPose>                     LayerSetup;                                               // 0x0050(0x0010) (Edit, EditFixedSize, ZeroConstructor)
	TArray<float>                                      BlendWeights;                                             // 0x0060(0x0010) (Edit, BlueprintVisible, EditFixedSize, ZeroConstructor)
	bool                                               bMeshSpaceRotationBlend;                                  // 0x0070(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ECurveBlendOption>                     CurveBlendOption;                                         // 0x0071(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bBlendRootMotionBasedOnRootBone;                          // 0x0072(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bHasRelevantPoses;                                        // 0x0073(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	int                                                LODThreshold;                                             // 0x0074(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TArray<struct FPerBoneBlendWeight>                 PerBoneBlendWeights;                                      // 0x0078(0x0010) (ZeroConstructor)
	struct FGuid                                       SkeletonGuid;                                             // 0x0088(0x0010) (ZeroConstructor, IsPlainOldData)
	struct FGuid                                       VirtualBoneGuid;                                          // 0x0098(0x0010) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x30];                                      // 0x00A8(0x0030) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimLegIKDefinition
// 0x0040
struct FAnimLegIKDefinition
{
	struct FBoneReference                              IKFootBone;                                               // 0x0000(0x0018) (Edit)
	struct FBoneReference                              FKFootBone;                                               // 0x0018(0x0018) (Edit)
	int                                                NumBonesInLimb;                                           // 0x0030(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAxis>                                 FootBoneForwardAxis;                                      // 0x0034(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAxis>                                 HingeRotationAxis;                                        // 0x0035(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableRotationLimit;                                     // 0x0036(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1];                                       // 0x0037(0x0001) MISSED OFFSET
	float                                              MinRotationAngle;                                         // 0x0038(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableKneeTwistCorrection;                               // 0x003C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x003D(0x0003) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimLegIKData
// 0x00B0
struct FAnimLegIKData
{
	unsigned char                                      UnknownData00[0xB0];                                      // 0x0000(0x00B0) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_LegIK
// 0x0030 (0x0120 - 0x00F0)
struct FAnimNode_LegIK : public FAnimNode_SkeletalControlBase
{
	float                                              ReachPrecision;                                           // 0x00F0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                MaxIterations;                                            // 0x00F4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<struct FAnimLegIKDefinition>                LegsDefinition;                                           // 0x00F8(0x0010) (Edit, ZeroConstructor)
	TArray<struct FAnimLegIKData>                      LegsData;                                                 // 0x0108(0x0010) (ZeroConstructor, Transient)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0118(0x0008) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.IKChain
// 0x0040
struct FIKChain
{
	unsigned char                                      UnknownData00[0x40];                                      // 0x0000(0x0040) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.IKChainLink
// 0x0040
struct FIKChainLink
{
	unsigned char                                      UnknownData00[0x40];                                      // 0x0000(0x0040) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_LookAt
// 0x0130 (0x0220 - 0x00F0)
struct FAnimNode_LookAt : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              BoneToModify;                                             // 0x00F0(0x0018) (Edit)
	struct FBoneReference                              LookAtBone;                                               // 0x0108(0x0018) (Deprecated)
	struct FName                                       LookAtSocket;                                             // 0x0120(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0128(0x0008) MISSED OFFSET
	struct FBoneSocketTarget                           LookAtTarget;                                             // 0x0130(0x0060) (Edit)
	struct FVector                                     LookAtLocation;                                           // 0x0190(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAxisOption>                           LookAtAxis;                                               // 0x019C(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x019D(0x0003) MISSED OFFSET
	struct FVector                                     CustomLookAtAxis;                                         // 0x01A0(0x000C) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FAxis                                       LookAt_Axis;                                              // 0x01AC(0x0010) (Edit)
	bool                                               bUseLookUpAxis;                                           // 0x01BC(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAxisOption>                           LookUpAxis;                                               // 0x01BD(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData02[0x2];                                       // 0x01BE(0x0002) MISSED OFFSET
	struct FVector                                     CustomLookUpAxis;                                         // 0x01C0(0x000C) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FAxis                                       LookUp_Axis;                                              // 0x01CC(0x0010) (Edit)
	float                                              LookAtClamp;                                              // 0x01DC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EInterpolationBlend>                   InterpolationType;                                        // 0x01E0(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x01E1(0x0003) MISSED OFFSET
	float                                              InterpolationTime;                                        // 0x01E4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              InterpolationTriggerThreashold;                           // 0x01E8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x34];                                      // 0x01EC(0x0034) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_MakeDynamicAdditive
// 0x0028 (0x0058 - 0x0030)
struct FAnimNode_MakeDynamicAdditive : public FAnimNode_Base
{
	struct FPoseLink                                   Base;                                                     // 0x0030(0x0010) (Edit, BlueprintVisible)
	struct FPoseLink                                   Additive;                                                 // 0x0040(0x0010) (Edit, BlueprintVisible)
	bool                                               bMeshSpaceAdditive;                                       // 0x0050(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0051(0x0007) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_ModifyBone
// 0x0048 (0x0138 - 0x00F0)
struct FAnimNode_ModifyBone : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              BoneToModify;                                             // 0x00F0(0x0018) (Edit)
	struct FVector                                     Translation;                                              // 0x0108(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    Rotation;                                                 // 0x0114(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Scale;                                                    // 0x0120(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneModificationMode>                 TranslationMode;                                          // 0x012C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneModificationMode>                 RotationMode;                                             // 0x012D(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneModificationMode>                 ScaleMode;                                                // 0x012E(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneControlSpace>                     TranslationSpace;                                         // 0x012F(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneControlSpace>                     RotationSpace;                                            // 0x0130(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneControlSpace>                     ScaleSpace;                                               // 0x0131(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x6];                                       // 0x0132(0x0006) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_ModifyCurve
// 0x0050 (0x0080 - 0x0030)
struct FAnimNode_ModifyCurve : public FAnimNode_Base
{
	struct FPoseLink                                   SourcePose;                                               // 0x0030(0x0010) (Edit, BlueprintVisible, EditFixedSize)
	EModifyCurveApplyMode                              ApplyMode;                                                // 0x0040(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0041(0x0007) MISSED OFFSET
	TArray<float>                                      CurveValues;                                              // 0x0048(0x0010) (Edit, BlueprintVisible, EditFixedSize, ZeroConstructor)
	TArray<float>                                      LastCurveValues;                                          // 0x0058(0x0010) (ZeroConstructor, Transient)
	TArray<struct FName>                               CurveNames;                                               // 0x0068(0x0010) (ZeroConstructor)
	float                                              Alpha;                                                    // 0x0078(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x007C(0x0004) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_MultiWayBlend
// 0x0040 (0x0070 - 0x0030)
struct FAnimNode_MultiWayBlend : public FAnimNode_Base
{
	TArray<struct FPoseLink>                           Poses;                                                    // 0x0030(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	TArray<float>                                      DesiredAlphas;                                            // 0x0040(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	bool                                               bAdditiveNode;                                            // 0x0050(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bNormalizeAlpha;                                          // 0x0051(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0052(0x0002) MISSED OFFSET
	struct FInputScaleBias                             AlphaScaleBias;                                           // 0x0054(0x0008) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData01[0x14];                                      // 0x005C(0x0014) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_ObserveBone
// 0x0040 (0x0130 - 0x00F0)
struct FAnimNode_ObserveBone : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              BoneToObserve;                                            // 0x00F0(0x0018) (Edit)
	TEnumAsByte<EBoneControlSpace>                     DisplaySpace;                                             // 0x0108(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bRelativeToRefPose;                                       // 0x0109(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x010A(0x0002) MISSED OFFSET
	struct FVector                                     Translation;                                              // 0x010C(0x000C) (ZeroConstructor, IsPlainOldData)
	struct FRotator                                    Rotation;                                                 // 0x0118(0x000C) (ZeroConstructor, IsPlainOldData)
	struct FVector                                     Scale;                                                    // 0x0124(0x000C) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.AnimNode_PoseHandler
// 0x0038 (0x0090 - 0x0058)
struct FAnimNode_PoseHandler : public FAnimNode_AssetPlayerBase
{
	class UPoseAsset*                                  PoseAsset;                                                // 0x0058(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x30];                                      // 0x0060(0x0030) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_PoseBlendNode
// 0x0020 (0x00B0 - 0x0090)
struct FAnimNode_PoseBlendNode : public FAnimNode_PoseHandler
{
	struct FPoseLink                                   SourcePose;                                               // 0x0090(0x0010) (Edit, BlueprintVisible, EditFixedSize)
	EAlphaBlendOption                                  BlendOption;                                              // 0x00A0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00A1(0x0007) MISSED OFFSET
	class UCurveFloat*                                 CustomCurve;                                              // 0x00A8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.AnimNode_PoseByName
// 0x0010 (0x00A0 - 0x0090)
struct FAnimNode_PoseByName : public FAnimNode_PoseHandler
{
	struct FName                                       PoseName;                                                 // 0x0090(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              PoseWeight;                                               // 0x0098(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x009C(0x0004) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.RBFParams
// 0x0010
struct FRBFParams
{
	int                                                TargetDimensions;                                         // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              Radius;                                                   // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	ERBFFunctionType                                   Function;                                                 // 0x0008(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	ERBFDistanceMethod                                 DistanceMethod;                                           // 0x0009(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneAxis>                             TwistAxis;                                                // 0x000A(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1];                                       // 0x000B(0x0001) MISSED OFFSET
	float                                              WeightThreshold;                                          // 0x000C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.PoseDriverTransform
// 0x0018
struct FPoseDriverTransform
{
	struct FVector                                     TargetTranslation;                                        // 0x0000(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    TargetRotation;                                           // 0x000C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.PoseDriverTarget
// 0x00A8
struct FPoseDriverTarget
{
	TArray<struct FPoseDriverTransform>                BoneTransforms;                                           // 0x0000(0x0010) (Edit, ZeroConstructor)
	struct FRotator                                    TargetRotation;                                           // 0x0010(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              TargetScale;                                              // 0x001C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bApplyCustomCurve;                                        // 0x0020(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0021(0x0007) MISSED OFFSET
	struct FRichCurve                                  CustomCurve;                                              // 0x0028(0x0070) (Edit)
	struct FName                                       DrivenName;                                               // 0x0098(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x00A0(0x0008) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_PoseDriver
// 0x00D0 (0x0160 - 0x0090)
struct FAnimNode_PoseDriver : public FAnimNode_PoseHandler
{
	struct FPoseLink                                   SourcePose;                                               // 0x0090(0x0010) (Edit, BlueprintVisible, EditFixedSize)
	TArray<struct FBoneReference>                      SourceBones;                                              // 0x00A0(0x0010) (Edit, ZeroConstructor)
	bool                                               bOnlyDriveSelectedBones;                                  // 0x00B0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00B1(0x0007) MISSED OFFSET
	TArray<struct FBoneReference>                      OnlyDriveBones;                                           // 0x00B8(0x0010) (Edit, ZeroConstructor)
	struct FBoneReference                              EvalSpaceBone;                                            // 0x00C8(0x0018) (Edit)
	struct FRBFParams                                  RBFParams;                                                // 0x00E0(0x0010) (Edit)
	EPoseDriverSource                                  DriveSource;                                              // 0x00F0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	EPoseDriverOutput                                  DriveOutput;                                              // 0x00F1(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x00F2(0x0006) MISSED OFFSET
	TArray<struct FPoseDriverTarget>                   PoseTargets;                                              // 0x00F8(0x0010) (Edit, ZeroConstructor)
	struct FBoneReference                              SourceBone;                                               // 0x0108(0x0018) (Deprecated)
	TEnumAsByte<EBoneAxis>                             TwistAxis;                                                // 0x0120(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	EPoseDriverType                                    Type;                                                     // 0x0121(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData02[0x2];                                       // 0x0122(0x0002) MISSED OFFSET
	float                                              RadialScaling;                                            // 0x0124(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData03[0x38];                                      // 0x0128(0x0038) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_PoseSnapshot
// 0x0080 (0x00B0 - 0x0030)
struct FAnimNode_PoseSnapshot : public FAnimNode_Base
{
	ESnapshotSourceMode                                Mode;                                                     // 0x0030(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0031(0x0007) MISSED OFFSET
	struct FName                                       SnapshotName;                                             // 0x0038(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FPoseSnapshot                               Snapshot;                                                 // 0x0040(0x0038) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData01[0x38];                                      // 0x0078(0x0038) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.RandomPlayerSequenceEntry
// 0x0058
struct FRandomPlayerSequenceEntry
{
	class UAnimSequence*                               Sequence;                                                 // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ChanceToPlay;                                             // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                MinLoopCount;                                             // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                MaxLoopCount;                                             // 0x0010(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              MinPlayRate;                                              // 0x0014(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              MaxPlayRate;                                              // 0x0018(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
	struct FAlphaBlend                                 BlendIn;                                                  // 0x0020(0x0038) (Edit)
};

// ScriptStruct AnimGraphRuntime.AnimNode_RandomPlayer
// 0x0060 (0x0090 - 0x0030)
struct FAnimNode_RandomPlayer : public FAnimNode_Base
{
	bool                                               bShuffleMode;                                             // 0x0030(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0031(0x0007) MISSED OFFSET
	TArray<struct FRandomPlayerSequenceEntry>          Entries;                                                  // 0x0038(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	unsigned char                                      UnknownData01[0x48];                                      // 0x0048(0x0048) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_MeshSpaceRefPose
// 0x0000 (0x0030 - 0x0030)
struct FAnimNode_MeshSpaceRefPose : public FAnimNode_Base
{

};

// ScriptStruct AnimGraphRuntime.AnimNode_RefPose
// 0x0008 (0x0038 - 0x0030)
struct FAnimNode_RefPose : public FAnimNode_Base
{
	TEnumAsByte<ERefPoseType>                          RefPoseType;                                              // 0x0030(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0031(0x0007) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_ResetRoot
// 0x0010 (0x0100 - 0x00F0)
struct FAnimNode_ResetRoot : public FAnimNode_SkeletalControlBase
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x00F0(0x0010) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_RigidBody
// 0x0480 (0x0570 - 0x00F0)
struct FAnimNode_RigidBody : public FAnimNode_SkeletalControlBase
{
	class UPhysicsAsset*                               OverridePhysicsAsset;                                     // 0x00F0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     OverrideWorldGravity;                                     // 0x00F8(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ExternalForce;                                            // 0x0104(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ComponentLinearAccScale;                                  // 0x0110(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ComponentLinearVelScale;                                  // 0x011C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ComponentAppliedLinearAccClamp;                           // 0x0128(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ECollisionChannel>                     OverlapChannel;                                           // 0x0134(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableWorldGeometry;                                     // 0x0135(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0136(0x0002) MISSED OFFSET
	ESimulationSpace                                   SimulationSpace;                                          // 0x0138(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0136(0x0003) FIX WRONG TYPE SIZE OF PREVIOUS PROPERTY
	unsigned char                                      UnknownData02[0x4];                                       // 0x013C(0x0004) MISSED OFFSET
	struct FBoneReference                              BaseBoneRef;                                              // 0x0140(0x0018) (Edit)
	bool                                               bOverrideWorldGravity;                                    // 0x0158(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x3];                                       // 0x0159(0x0003) MISSED OFFSET
	float                                              CachedBoundsScale;                                        // 0x015C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bTransferBoneVelocities;                                  // 0x0160(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bFreezeIncomingPoseOnStart;                               // 0x0161(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bComponentSpaceSimulation;                                // 0x0162(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData04[0x40D];                                     // 0x0163(0x040D) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_Root
// 0x0010 (0x0040 - 0x0030)
struct FAnimNode_Root : public FAnimNode_Base
{
	struct FPoseLink                                   Result;                                                   // 0x0030(0x0010) (Edit, BlueprintVisible)
};

// ScriptStruct AnimGraphRuntime.AnimNode_RotateRootBone
// 0x0090 (0x00C0 - 0x0030)
struct FAnimNode_RotateRootBone : public FAnimNode_Base
{
	struct FPoseLink                                   BasePose;                                                 // 0x0030(0x0010) (Edit, BlueprintVisible)
	float                                              Pitch;                                                    // 0x0040(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Yaw;                                                      // 0x0044(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBiasClamp                        PitchScaleBiasClamp;                                      // 0x0048(0x0030) (Edit, BlueprintVisible)
	struct FInputScaleBiasClamp                        YawScaleBiasClamp;                                        // 0x0078(0x0030) (Edit, BlueprintVisible)
	struct FRotator                                    MeshToComponent;                                          // 0x00A8(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ActualPitch;                                              // 0x00B4(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              ActualYaw;                                                // 0x00B8(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x00BC(0x0004) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_RotationMultiplier
// 0x0038 (0x0128 - 0x00F0)
struct FAnimNode_RotationMultiplier : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              TargetBone;                                               // 0x00F0(0x0018) (Edit)
	struct FBoneReference                              SourceBone;                                               // 0x0108(0x0018) (Edit)
	float                                              Multiplier;                                               // 0x0120(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EBoneAxis>                             RotationAxisToRefer;                                      // 0x0124(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bIsAdditive;                                              // 0x0125(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0126(0x0002) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_RotationOffsetBlendSpace
// 0x00B8 (0x01E0 - 0x0128)
struct FAnimNode_RotationOffsetBlendSpace : public FAnimNode_BlendSpacePlayer
{
	struct FPoseLink                                   BasePose;                                                 // 0x0128(0x0010) (Edit, BlueprintVisible)
	int                                                LODThreshold;                                             // 0x0138(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bIsLODEnabled;                                            // 0x013C(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	EAnimAlphaInputType                                AlphaInputType;                                           // 0x013D(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x013E(0x0002) MISSED OFFSET
	float                                              Alpha;                                                    // 0x0140(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBias                             AlphaScaleBias;                                           // 0x0144(0x0008) (Edit, BlueprintVisible)
	float                                              ActualAlpha;                                              // 0x014C(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	bool                                               bAlphaBoolEnabled;                                        // 0x0150(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0151(0x0007) MISSED OFFSET
	struct FInputAlphaBoolBlend                        AlphaBoolBlend;                                           // 0x0158(0x0050) (Edit, BlueprintVisible)
	struct FName                                       AlphaCurveName;                                           // 0x01A8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBiasClamp                        AlphaScaleBiasClamp;                                      // 0x01B0(0x0030) (Edit, BlueprintVisible)
};

// ScriptStruct AnimGraphRuntime.AnimNode_ScaleChainLength
// 0x0080 (0x00B0 - 0x0030)
struct FAnimNode_ScaleChainLength : public FAnimNode_Base
{
	struct FPoseLink                                   InputPose;                                                // 0x0030(0x0010) (Edit)
	float                                              DefaultChainLength;                                       // 0x0040(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0044(0x0004) MISSED OFFSET
	struct FBoneReference                              ChainStartBone;                                           // 0x0048(0x0018) (Edit)
	struct FBoneReference                              ChainEndBone;                                             // 0x0060(0x0018) (Edit)
	EScaleChainInitialLength                           ChainInitialLength;                                       // 0x0078(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0079(0x0003) MISSED OFFSET
	struct FVector                                     TargetLocation;                                           // 0x007C(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Alpha;                                                    // 0x0088(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ActualAlpha;                                              // 0x008C(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	struct FInputScaleBias                             AlphaScaleBias;                                           // 0x0090(0x0008) (Edit)
	bool                                               bBoneIndicesCached;                                       // 0x0098(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData02[0x17];                                      // 0x0099(0x0017) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_SequenceEvaluator
// 0x0018 (0x0070 - 0x0058)
struct FAnimNode_SequenceEvaluator : public FAnimNode_AssetPlayerBase
{
	class UAnimSequenceBase*                           Sequence;                                                 // 0x0058(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              ExplicitTime;                                             // 0x0060(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bShouldLoop;                                              // 0x0064(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bTeleportToExplicitTime;                                  // 0x0065(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0066(0x0002) MISSED OFFSET
	float                                              StartPosition;                                            // 0x0068(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ESequenceEvalReinit>                   ReinitializationBehavior;                                 // 0x006C(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bReinitialized;                                           // 0x006D(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2];                                       // 0x006E(0x0002) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_Slot
// 0x0038 (0x0068 - 0x0030)
struct FAnimNode_Slot : public FAnimNode_Base
{
	struct FPoseLink                                   Source;                                                   // 0x0030(0x0010) (Edit, BlueprintVisible)
	struct FName                                       SlotName;                                                 // 0x0040(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bAlwaysUpdateSourcePose;                                  // 0x0048(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1F];                                      // 0x0049(0x001F) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.SplineIKCachedBoneData
// 0x0020
struct FSplineIKCachedBoneData
{
	struct FBoneReference                              Bone;                                                     // 0x0000(0x0018)
	int                                                RefSkeletonIndex;                                         // 0x0018(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_SplineIK
// 0x01A0 (0x0290 - 0x00F0)
struct FAnimNode_SplineIK : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              StartBone;                                                // 0x00F0(0x0018) (Edit)
	struct FBoneReference                              EndBone;                                                  // 0x0108(0x0018) (Edit)
	ESplineBoneAxis                                    BoneAxis;                                                 // 0x0120(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bAutoCalculateSpline;                                     // 0x0121(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x0122(0x0002) MISSED OFFSET
	int                                                PointCount;                                               // 0x0124(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TArray<struct FTransform>                          ControlPoints;                                            // 0x0128(0x0010) (Edit, BlueprintVisible, EditFixedSize, ZeroConstructor)
	float                                              Roll;                                                     // 0x0138(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              TwistStart;                                               // 0x013C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              TwistEnd;                                                 // 0x0140(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0144(0x0004) MISSED OFFSET
	struct FAlphaBlend                                 TwistBlend;                                               // 0x0148(0x0038) (Edit)
	float                                              Stretch;                                                  // 0x0180(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Offset;                                                   // 0x0184(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x70];                                      // 0x0188(0x0070) MISSED OFFSET
	struct FSplineCurves                               BoneSpline;                                               // 0x01F8(0x0060)
	float                                              OriginalSplineLength;                                     // 0x0258(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x025C(0x0004) MISSED OFFSET
	TArray<struct FSplineIKCachedBoneData>             CachedBoneReferences;                                     // 0x0260(0x0010) (ZeroConstructor)
	TArray<float>                                      CachedBoneLengths;                                        // 0x0270(0x0010) (ZeroConstructor)
	TArray<struct FQuat>                               CachedOffsetRotations;                                    // 0x0280(0x0010) (ZeroConstructor)
};

// ScriptStruct AnimGraphRuntime.AnimNode_SpringBone
// 0x0068 (0x0158 - 0x00F0)
struct FAnimNode_SpringBone : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              SpringBone;                                               // 0x00F0(0x0018) (Edit)
	bool                                               bLimitDisplacement;                                       // 0x0108(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0109(0x0003) MISSED OFFSET
	float                                              MaxDisplacement;                                          // 0x010C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              SpringStiffness;                                          // 0x0110(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              SpringDamping;                                            // 0x0114(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ErrorResetThresh;                                         // 0x0118(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bNoZSpring;                                               // 0x011C(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	bool                                               bTranslateX;                                              // 0x011D(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bTranslateY;                                              // 0x011E(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bTranslateZ;                                              // 0x011F(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bRotateX;                                                 // 0x0120(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bRotateY;                                                 // 0x0121(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bRotateZ;                                                 // 0x0122(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x35];                                      // 0x0123(0x0035) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_StateResult
// 0x0000 (0x0040 - 0x0040)
struct FAnimNode_StateResult : public FAnimNode_Root
{

};

// ScriptStruct AnimGraphRuntime.RotationLimit
// 0x0018
struct FRotationLimit
{
	struct FVector                                     LimitMin;                                                 // 0x0000(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     LimitMax;                                                 // 0x000C(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct AnimGraphRuntime.AnimNode_Trail
// 0x0190 (0x0280 - 0x00F0)
struct FAnimNode_Trail : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              TrailBone;                                                // 0x00F0(0x0018) (Edit)
	int                                                ChainLength;                                              // 0x0108(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAxis>                                 ChainBoneAxis;                                            // 0x010C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bInvertChainBoneAxis : 1;                                 // 0x010D(0x0001) (Edit)
	unsigned char                                      bLimitStretch : 1;                                        // 0x010D(0x0001) (Edit)
	unsigned char                                      bLimitRotation : 1;                                       // 0x010D(0x0001) (Edit)
	unsigned char                                      bUsePlanarLimit : 1;                                      // 0x010D(0x0001) (Edit)
	unsigned char                                      bActorSpaceFakeVel : 1;                                   // 0x010D(0x0001) (Edit)
	unsigned char                                      bReorientParentToChild : 1;                               // 0x010D(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x2];                                       // 0x010E(0x0002) MISSED OFFSET
	uint32_t                                           UnwindingSize;                                            // 0x0110(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              RelaxationSpeedScale;                                     // 0x0114(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FRuntimeFloatCurve                          TrailRelaxationSpeed;                                     // 0x0118(0x0078) (Edit)
	struct FInputScaleBiasClamp                        RelaxationSpeedScaleInputProcessor;                       // 0x0190(0x0030) (Edit, BlueprintVisible)
	TArray<struct FRotationLimit>                      RotationLimits;                                           // 0x01C0(0x0010) (Edit, EditFixedSize, ZeroConstructor)
	TArray<struct FVector>                             RotationOffsets;                                          // 0x01D0(0x0010) (Edit, BlueprintVisible, EditFixedSize, ZeroConstructor)
	TArray<struct FAnimPhysPlanarLimit>                PlanarLimits;                                             // 0x01E0(0x0010) (Edit, ZeroConstructor)
	float                                              StretchLimit;                                             // 0x01F0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     FakeVelocity;                                             // 0x01F4(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	struct FBoneReference                              BaseJoint;                                                // 0x0200(0x0018) (Edit)
	float                                              LastBoneRotationAnimAlphaBlend;                           // 0x0218(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x64];                                      // 0x021C(0x0064) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.ReferenceBoneFrame
// 0x0028
struct FReferenceBoneFrame
{
	struct FBoneReference                              Bone;                                                     // 0x0000(0x0018) (Edit)
	struct FAxis                                       Axis;                                                     // 0x0018(0x0010) (Edit)
};

// ScriptStruct AnimGraphRuntime.AnimNode_TwistCorrectiveNode
// 0x0088 (0x0178 - 0x00F0)
struct FAnimNode_TwistCorrectiveNode : public FAnimNode_SkeletalControlBase
{
	struct FReferenceBoneFrame                         BaseFrame;                                                // 0x00F0(0x0028) (Edit)
	struct FReferenceBoneFrame                         TwistFrame;                                               // 0x0118(0x0028) (Edit)
	struct FAxis                                       TwistPlaneNormalAxis;                                     // 0x0140(0x0010) (Edit)
	float                                              RangeMax;                                                 // 0x0150(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              RemappedMin;                                              // 0x0154(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              RemappedMax;                                              // 0x0158(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x015C(0x0004) MISSED OFFSET
	struct FAnimCurveParam                             Curve;                                                    // 0x0160(0x0010) (Edit)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0170(0x0008) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_TwoBoneIK
// 0x0150 (0x0240 - 0x00F0)
struct FAnimNode_TwoBoneIK : public FAnimNode_SkeletalControlBase
{
	struct FBoneReference                              IKBone;                                                   // 0x00F0(0x0018) (Edit)
	unsigned char                                      bAllowStretching : 1;                                     // 0x0108(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0109(0x0003) MISSED OFFSET
	float                                              StartStretchRatio;                                        // 0x010C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              MaxStretchScale;                                          // 0x0110(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   StretchLimits;                                            // 0x0114(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      bTakeRotationFromEffectorSpace : 1;                       // 0x011C(0x0001) (Edit)
	unsigned char                                      bMaintainEffectorRelRot : 1;                              // 0x011C(0x0001) (Edit)
	unsigned char                                      UnknownData01[0x3];                                       // 0x011D(0x0003) MISSED OFFSET
	TEnumAsByte<EBoneControlSpace>                     EffectorLocationSpace;                                    // 0x0120(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x7];                                       // 0x0121(0x0007) MISSED OFFSET
	struct FName                                       EffectorSpaceBoneName;                                    // 0x0128(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	struct FVector                                     EffectorLocation;                                         // 0x0130(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x4];                                       // 0x013C(0x0004) MISSED OFFSET
	struct FBoneSocketTarget                           EffectorTarget;                                           // 0x0140(0x0060) (Edit)
	TEnumAsByte<EBoneControlSpace>                     JointTargetLocationSpace;                                 // 0x01A0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData04[0x3];                                       // 0x01A1(0x0003) MISSED OFFSET
	struct FVector                                     JointTargetLocation;                                      // 0x01A4(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FName                                       JointTargetSpaceBoneName;                                 // 0x01B0(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData05[0x8];                                       // 0x01B8(0x0008) MISSED OFFSET
	struct FBoneSocketTarget                           JointTarget;                                              // 0x01C0(0x0060) (Edit)
	bool                                               bAllowTwist;                                              // 0x0220(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData06[0x3];                                       // 0x0221(0x0003) MISSED OFFSET
	struct FAxis                                       TwistAxis;                                                // 0x0224(0x0010) (Edit)
	bool                                               bNoTwist;                                                 // 0x0234(0x0001) (ZeroConstructor, Deprecated, IsPlainOldData)
	unsigned char                                      UnknownData07[0xB];                                       // 0x0235(0x000B) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimNode_TwoWayBlend
// 0x00C8 (0x00F8 - 0x0030)
struct FAnimNode_TwoWayBlend : public FAnimNode_Base
{
	struct FPoseLink                                   A;                                                        // 0x0030(0x0010) (Edit, BlueprintVisible)
	struct FPoseLink                                   B;                                                        // 0x0040(0x0010) (Edit, BlueprintVisible)
	EAnimAlphaInputType                                AlphaInputType;                                           // 0x0050(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0051(0x0003) MISSED OFFSET
	float                                              Alpha;                                                    // 0x0054(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBias                             AlphaScaleBias;                                           // 0x0058(0x0008) (Edit, BlueprintVisible)
	bool                                               bAlphaBoolEnabled;                                        // 0x0060(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0061(0x0007) MISSED OFFSET
	struct FInputAlphaBoolBlend                        AlphaBoolBlend;                                           // 0x0068(0x0050) (Edit, BlueprintVisible)
	struct FName                                       AlphaCurveName;                                           // 0x00B8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FInputScaleBiasClamp                        AlphaScaleBiasClamp;                                      // 0x00C0(0x0030) (Edit, BlueprintVisible)
	float                                              InternalBlendAlpha;                                       // 0x00F0(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	bool                                               bAIsRelevant;                                             // 0x00F4(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	bool                                               bBIsRelevant;                                             // 0x00F5(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	bool                                               bResetChildOnActivation;                                  // 0x00F6(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x1];                                       // 0x00F7(0x0001) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.AnimSequencerInstanceProxy
// 0x0220 (0x0800 - 0x05E0)
struct FAnimSequencerInstanceProxy : public FAnimInstanceProxy
{
	unsigned char                                      UnknownData00[0x220];                                     // 0x05E0(0x0220) MISSED OFFSET
};

// ScriptStruct AnimGraphRuntime.RBFEntry
// 0x0010
struct FRBFEntry
{
	TArray<float>                                      Values;                                                   // 0x0000(0x0010) (Edit, ZeroConstructor)
};

// ScriptStruct AnimGraphRuntime.RBFTarget
// 0x0078 (0x0088 - 0x0010)
struct FRBFTarget : public FRBFEntry
{
	float                                              ScaleFactor;                                              // 0x0010(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bApplyCustomCurve;                                        // 0x0014(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0015(0x0003) MISSED OFFSET
	struct FRichCurve                                  CustomCurve;                                              // 0x0018(0x0070) (Edit)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
