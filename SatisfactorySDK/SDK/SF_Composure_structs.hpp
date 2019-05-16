#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Basic.hpp"
#include "SF_Engine_classes.hpp"
#include "SF_CoreUObject_classes.hpp"
#include "SF_MovieScene_classes.hpp"
#include "SF_MovieSceneTracks_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct Composure.ComposureUVMapSettings
// 0x00A0
struct FComposureUVMapSettings
{
	struct FMatrix                                     PreUVDisplacementMatrix;                                  // 0x0000(0x0040) (Edit, BlueprintVisible, IsPlainOldData)
	struct FMatrix                                     PostUVDisplacementMatrix;                                 // 0x0040(0x0040) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   DisplacementDecodeParameters;                             // 0x0080(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	class UTexture*                                    DisplacementTexture;                                      // 0x0088(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bUseDisplacementBlueAndAlphaChannels : 1;                 // 0x0090(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      UnknownData00[0xF];                                       // 0x0091(0x000F) MISSED OFFSET
};

// ScriptStruct Composure.ComposurePostMoveSettings
// 0x0018
struct FComposurePostMoveSettings
{
	struct FVector2D                                   Pivot;                                                    // 0x0000(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   Translation;                                              // 0x0008(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	float                                              RotationAngle;                                            // 0x0010(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Scale;                                                    // 0x0014(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct Composure.MovieSceneComposurePostMoveSettingsSectionTemplate
// 0x03C8 (0x0410 - 0x0048)
struct FMovieSceneComposurePostMoveSettingsSectionTemplate : public FMovieScenePropertySectionTemplate
{
	struct FMovieSceneFloatChannel                     Pivot[0x2];                                               // 0x0048(0x00A0)
	struct FMovieSceneFloatChannel                     Translation[0x2];                                         // 0x0188(0x00A0)
	struct FMovieSceneFloatChannel                     RotationAngle;                                            // 0x02C8(0x00A0)
	struct FMovieSceneFloatChannel                     Scale;                                                    // 0x0368(0x00A0)
	EMovieSceneBlendType                               BlendType;                                                // 0x0408(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0409(0x0007) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
