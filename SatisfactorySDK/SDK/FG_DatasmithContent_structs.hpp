#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_CinematicCamera_classes.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum DatasmithContent.EDatasmithAreaLightActorShape
enum class EDatasmithAreaLightActorShape : uint8_t
{
	Rectangle                      = 0,
	Disc                           = 1,
	Sphere                         = 2,
	Cylinder                       = 3,
	EDatasmithAreaLightActorShape_MAX = 4
};


// Enum DatasmithContent.EVREDDataTableType
enum class EVREDDataTableType : uint8_t
{
	NotDatatable                   = 0,
	Variants                       = 1,
	AnimClips                      = 2,
	AnimNodes                      = 3,
	EVREDDataTableType_MAX         = 4
};


// Enum DatasmithContent.EDatasmithImportHierarchy
enum class EDatasmithImportHierarchy : uint8_t
{
	UseMultipleActors              = 0,
	UseSingleActor                 = 1,
	UseOneBlueprint                = 2,
	EDatasmithImportHierarchy_MAX  = 3
};


// Enum DatasmithContent.EDatasmithImportScene
enum class EDatasmithImportScene : uint8_t
{
	NewLevel                       = 0,
	CurrentLevel                   = 1,
	AssetsOnly                     = 2,
	EDatasmithImportScene_MAX      = 3
};


// Enum DatasmithContent.EDatasmithImportLightmapMax
enum class EDatasmithImportLightmapMax : uint8_t
{
	LIGHTMAP                       = 0,
	LIGHTMAP01                     = 1,
	LIGHTMAP02                     = 2,
	LIGHTMAP03                     = 3,
	LIGHTMAP04                     = 4,
	LIGHTMAP05                     = 5,
	LIGHTMAP06                     = 6,
	LIGHTMAP_MAX                   = 7
};


// Enum DatasmithContent.EDatasmithImportLightmapMin
enum class EDatasmithImportLightmapMin : uint8_t
{
	LIGHTMAP                       = 0,
	LIGHTMAP01                     = 1,
	LIGHTMAP02                     = 2,
	LIGHTMAP03                     = 3,
	LIGHTMAP04                     = 4,
	LIGHTMAP05                     = 5,
	LIGHTMAP_MAX                   = 6
};


// Enum DatasmithContent.EDatasmithImportMaterialQuality
enum class EDatasmithImportMaterialQuality : uint8_t
{
	UseNoFresnelCurves             = 0,
	UseSimplifierFresnelCurves     = 1,
	UseRealFresnelCurves           = 2,
	EDatasmithImportMaterialQuality_MAX = 3
};


// Enum DatasmithContent.EDatasmithImportActorPolicy
enum class EDatasmithImportActorPolicy : uint8_t
{
	Update                         = 0,
	Full                           = 1,
	Ignore                         = 2,
	EDatasmithImportActorPolicy_MAX = 3
};


// Enum DatasmithContent.EDatasmithImportAssetConflictPolicy
enum class EDatasmithImportAssetConflictPolicy : uint8_t
{
	Replace                        = 0,
	Update                         = 1,
	Use                            = 2,
	Ignore                         = 3,
	EDatasmithImportAssetConflictPolicy_MAX = 4
};


// Enum DatasmithContent.EDatasmithImportSearchPackagePolicy
enum class EDatasmithImportSearchPackagePolicy : uint8_t
{
	Current                        = 0,
	All                            = 1,
	EDatasmithImportSearchPackagePolicy_MAX = 2
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct DatasmithContent.DatasmithCameraFilmbackSettingsTemplate
// 0x0008
struct FDatasmithCameraFilmbackSettingsTemplate
{
	float                                              SensorWidth;                                              // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              SensorHeight;                                             // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithCameraLensSettingsTemplate
// 0x0004
struct FDatasmithCameraLensSettingsTemplate
{
	float                                              MaxFStop;                                                 // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithCameraFocusSettingsTemplate
// 0x0008
struct FDatasmithCameraFocusSettingsTemplate
{
	ECameraFocusMethod                                 FocusMethod;                                              // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
	float                                              ManualFocusDistance;                                      // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithPostProcessSettingsTemplate
// 0x0040
struct FDatasmithPostProcessSettingsTemplate
{
	unsigned char                                      bOverride_WhiteTemp : 1;                                  // 0x0000(0x0001)
	unsigned char                                      bOverride_ColorSaturation : 1;                            // 0x0000(0x0001)
	unsigned char                                      bOverride_VignetteIntensity : 1;                          // 0x0000(0x0001)
	unsigned char                                      bOverride_FilmWhitePoint : 1;                             // 0x0000(0x0001)
	unsigned char                                      bOverride_AutoExposureMethod : 1;                         // 0x0000(0x0001)
	unsigned char                                      bOverride_CameraISO : 1;                                  // 0x0000(0x0001)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
	float                                              WhiteTemp;                                                // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              VignetteIntensity;                                        // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                FilmWhitePoint;                                           // 0x000C(0x0010) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
	struct FVector4                                    ColorSaturation;                                          // 0x0020(0x0010) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<EAutoExposureMethod>                   AutoExposureMethod;                                       // 0x0030(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0031(0x0003) MISSED OFFSET
	float                                              CameraISO;                                                // 0x0034(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
};

// ScriptStruct DatasmithContent.DatasmithAssetImportOptions
// 0x0008
struct FDatasmithAssetImportOptions
{
	struct FName                                       PackagePath;                                              // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithStaticMeshImportOptions
// 0x0004
struct FDatasmithStaticMeshImportOptions
{
	EDatasmithImportLightmapMin                        MinLightmapResolution;                                    // 0x0000(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	EDatasmithImportLightmapMax                        MaxLightmapResolution;                                    // 0x0001(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bGenerateLightmapUVs;                                     // 0x0002(0x0001) (BlueprintVisible, ZeroConstructor, Transient, IsPlainOldData)
	bool                                               bRemoveDegenerates;                                       // 0x0003(0x0001) (BlueprintVisible, ZeroConstructor, Transient, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithImportBaseOptions
// 0x0018
struct FDatasmithImportBaseOptions
{
	EDatasmithImportScene                              SceneHandling;                                            // 0x0000(0x0001) (BlueprintVisible, ZeroConstructor, Transient, IsPlainOldData)
	bool                                               bIncludeGeometry;                                         // 0x0001(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bIncludeMaterial;                                         // 0x0002(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bIncludeLight;                                            // 0x0003(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	bool                                               bIncludeCamera;                                           // 0x0004(0x0001) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0005(0x0003) MISSED OFFSET
	struct FDatasmithAssetImportOptions                AssetOptions;                                             // 0x0008(0x0008) (BlueprintVisible)
	struct FDatasmithStaticMeshImportOptions           StaticMeshOptions;                                        // 0x0010(0x0004) (Edit, BlueprintVisible, Config)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0014(0x0004) MISSED OFFSET
};

// ScriptStruct DatasmithContent.DatasmithTessellationOptions
// 0x000C
struct FDatasmithTessellationOptions
{
	float                                              ChordTolerance;                                           // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	float                                              MaxEdgeLength;                                            // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
	float                                              NormalTolerance;                                          // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithReimportOptions
// 0x0002
struct FDatasmithReimportOptions
{
	bool                                               bUpdateActors;                                            // 0x0000(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bRespawnDeletedActors;                                    // 0x0001(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithMeshSectionInfoTemplate
// 0x0004
struct FDatasmithMeshSectionInfoTemplate
{
	int                                                MaterialIndex;                                            // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithMeshSectionInfoMapTemplate
// 0x0050
struct FDatasmithMeshSectionInfoMapTemplate
{
	TMap<uint32_t, struct FDatasmithMeshSectionInfoTemplate> Map;                                                      // 0x0000(0x0050) (ZeroConstructor)
};

// ScriptStruct DatasmithContent.DatasmithMeshBuildSettingsTemplate
// 0x0010
struct FDatasmithMeshBuildSettingsTemplate
{
	unsigned char                                      bUseMikkTSpace : 1;                                       // 0x0000(0x0001)
	unsigned char                                      bRecomputeNormals : 1;                                    // 0x0000(0x0001)
	unsigned char                                      bRecomputeTangents : 1;                                   // 0x0000(0x0001)
	unsigned char                                      bRemoveDegenerates : 1;                                   // 0x0000(0x0001)
	unsigned char                                      bBuildAdjacencyBuffer : 1;                                // 0x0000(0x0001)
	unsigned char                                      bUseHighPrecisionTangentBasis : 1;                        // 0x0000(0x0001)
	unsigned char                                      bUseFullPrecisionUVs : 1;                                 // 0x0000(0x0001)
	unsigned char                                      bGenerateLightmapUVs : 1;                                 // 0x0000(0x0001)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
	int                                                MinLightmapResolution;                                    // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                SrcLightmapIndex;                                         // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                DstLightmapIndex;                                         // 0x000C(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct DatasmithContent.DatasmithStaticMaterialTemplate
// 0x0010
struct FDatasmithStaticMaterialTemplate
{
	struct FName                                       MaterialSlotName;                                         // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	class UMaterialInterface*                          MaterialInterface;                                        // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
