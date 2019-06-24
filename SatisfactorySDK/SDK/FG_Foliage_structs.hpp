#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum Foliage.EFoliageScaling
enum class EFoliageScaling : uint8_t
{
	Uniform                        = 0,
	Free                           = 1,
	LockXY                         = 2,
	LockXZ                         = 3,
	LockYZ                         = 4,
	EFoliageScaling_MAX            = 5
};


// Enum Foliage.EVertexColorMaskChannel
enum class EVertexColorMaskChannel : uint8_t
{
	Red                            = 0,
	Green                          = 1,
	Blue                           = 2,
	Alpha                          = 3,
	MAX_None                       = 4,
	EVertexColorMaskChannel_MAX    = 5
};


// Enum Foliage.FoliageVertexColorMask
enum class EFoliageVertexColorMask : uint8_t
{
	FOLIAGEVERTEXCOLORMASK_Disabled = 0,
	FOLIAGEVERTEXCOLORMASK_Red     = 1,
	FOLIAGEVERTEXCOLORMASK_Green   = 2,
	FOLIAGEVERTEXCOLORMASK_Blue    = 3,
	FOLIAGEVERTEXCOLORMASK_Alpha   = 4,
	FOLIAGEVERTEXCOLORMASK_MAX     = 5
};


// Enum Foliage.ESimulationQuery
enum class ESimulationQuery : uint8_t
{
	CollisionOverlap               = 0,
	ShadeOverlap                   = 1,
	AnyOverlap                     = 2,
	ESimulationQuery_MAX           = 3
};


// Enum Foliage.ESimulationOverlap
enum class ESimulationOverlap : uint8_t
{
	CollisionOverlap               = 0,
	ShadeOverlap                   = 1,
	None                           = 2,
	ESimulationOverlap_MAX         = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct Foliage.FoliageVertexColorChannelMask
// 0x000C
struct FFoliageVertexColorChannelMask
{
	unsigned char                                      UseMask : 1;                                              // 0x0000(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
	float                                              MaskThreshold;                                            // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      InvertMask : 1;                                           // 0x0008(0x0001) (Edit)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
};

// ScriptStruct Foliage.FoliageTypeObject
// 0x0020
struct FFoliageTypeObject
{
	class UObject*                                     FoliageTypeObject;                                        // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UFoliageType_InstancedStaticMesh*            TypeInstance;                                             // 0x0008(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	bool                                               bIsAsset;                                                 // 0x0010(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0011(0x0007) MISSED OFFSET
	class UClass*                                      Type;                                                     // 0x0018(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData)
};

// ScriptStruct Foliage.ProceduralFoliageInstance
// 0x0060
struct FProceduralFoliageInstance
{
	struct FVector                                     Location;                                                 // 0x0000(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
	struct FQuat                                       Rotation;                                                 // 0x0010(0x0010) (IsPlainOldData)
	struct FVector                                     Normal;                                                   // 0x0020(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Age;                                                      // 0x002C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Scale;                                                    // 0x0030(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0034(0x0004) MISSED OFFSET
	class UFoliageType_InstancedStaticMesh*            Type;                                                     // 0x0038(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x20];                                      // 0x0040(0x0020) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
