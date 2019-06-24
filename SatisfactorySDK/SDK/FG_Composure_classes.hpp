#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Composure_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class Composure.ComposureBlueprintLibrary
// 0x0000 (0x0028 - 0x0028)
class UComposureBlueprintLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.ComposureBlueprintLibrary");
		return ptr;
	}


	void SetUVMapSettingsToMaterialParameters(const struct FComposureUVMapSettings& UVMapSettings, class UMaterialInstanceDynamic* Material);
	void InvertUVDisplacementMapEncodingParameters(const struct FVector2D& In, struct FVector2D* Out);
	void GetRedGreenUVFactorsFromChromaticAberration(float ChromaticAberrationAmount, struct FVector2D* RedGreenUVFactors);
	void GetProjectionMatrixFromPostMoveSettings(const struct FComposurePostMoveSettings& PostMoveSettings, float HorizontalFOVAngle, float AspectRatio, struct FMatrix* ProjectionMatrix);
	void GetPlayerDisplayGamma(class APlayerCameraManager* PlayerCameraManager, float* DisplayGamma);
	void GetCroppingUVTransformationMatrixFromPostMoveSettings(const struct FComposurePostMoveSettings& PostMoveSettings, float AspectRatio, struct FMatrix* CropingUVTransformationMatrix, struct FMatrix* UncropingUVTransformationMatrix);
	class UComposurePlayerCompositingTarget* CreatePlayerCompositingTarget(class UObject* WorldContextObject);
};


// Class Composure.ComposurePostProcessPass
// 0x0020 (0x0260 - 0x0240)
class UComposurePostProcessPass : public USceneComponent
{
public:
	class UComposurePostProcessBlendable*              BlendableInterface;                                       // 0x0240(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UMaterialInterface*                          SetupMaterial;                                            // 0x0248(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UMaterialInstanceDynamic*                    TonemapperReplacingMID;                                   // 0x0250(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0258(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.ComposurePostProcessPass");
		return ptr;
	}


	void SetSetupMaterial(class UMaterialInterface* Material);
	void SetOutputRenderTarget(class UTextureRenderTarget2D* RenderTarget);
	class UMaterialInterface* GetSetupMaterial();
	class UTextureRenderTarget2D* GetOutputRenderTarget();
};


// Class Composure.ComposureLensBloomPass
// 0x00B0 (0x0310 - 0x0260)
class UComposureLensBloomPass : public UComposurePostProcessPass
{
public:
	unsigned char                                      UnknownData00[0xB0];                                      // 0x0260(0x00B0) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.ComposureLensBloomPass");
		return ptr;
	}


	void SetTonemapperReplacingMaterial(class UMaterialInstanceDynamic* Material);
	void BloomToRenderTarget();
};


// Class Composure.ComposurePipelineBaseActor
// 0x0000 (0x0328 - 0x0328)
class AComposurePipelineBaseActor : public AActor
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.ComposurePipelineBaseActor");
		return ptr;
	}

};


// Class Composure.ComposurePlayerCompositingCameraModifier
// 0x0010 (0x0058 - 0x0048)
class UComposurePlayerCompositingCameraModifier : public UCameraModifier
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0048(0x0008) MISSED OFFSET
	class UComposurePlayerCompositingTarget*           Target;                                                   // 0x0050(0x0008) (ZeroConstructor, Transient, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.ComposurePlayerCompositingCameraModifier");
		return ptr;
	}

};


// Class Composure.ComposurePlayerCompositingTarget
// 0x0020 (0x0048 - 0x0028)
class UComposurePlayerCompositingTarget : public UObject
{
public:
	class APlayerCameraManager*                        PlayerCameraManager;                                      // 0x0028(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UComposurePlayerCompositingCameraModifier*   PlayerCameraModifier;                                     // 0x0030(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class UMaterialInstanceDynamic*                    ReplaceTonemapperMID;                                     // 0x0038(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0040(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.ComposurePlayerCompositingTarget");
		return ptr;
	}


	void SetRenderTarget(class UTextureRenderTarget2D* RenderTarget);
	class APlayerCameraManager* SetPlayerCameraManager(class APlayerCameraManager* PlayerCameraManager);
	class APlayerCameraManager* GetPlayerCameraManager();
};


// Class Composure.ComposurePostProcessBlendable
// 0x0010 (0x0038 - 0x0028)
class UComposurePostProcessBlendable : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	class UComposurePostProcessPass*                   Target;                                                   // 0x0030(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.ComposurePostProcessBlendable");
		return ptr;
	}

};


// Class Composure.ComposureTonemapperPass
// 0x0170 (0x03D0 - 0x0260)
class UComposureTonemapperPass : public UComposurePostProcessPass
{
public:
	struct FColorGradingSettings                       ColorGradingSettings;                                     // 0x0260(0x0150) (Edit, BlueprintVisible)
	struct FFilmStockSettings                          FilmStockSettings;                                        // 0x03B0(0x0014) (Edit, BlueprintVisible)
	float                                              ChromaticAberration;                                      // 0x03C4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x03C8(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.ComposureTonemapperPass");
		return ptr;
	}


	void TonemapToRenderTarget();
};


// Class Composure.MovieSceneComposurePostMoveSettingsSection
// 0x03C0 (0x04A0 - 0x00E0)
class UMovieSceneComposurePostMoveSettingsSection : public UMovieSceneSection
{
public:
	struct FMovieSceneFloatChannel                     Pivot[0x2];                                               // 0x00E0(0x00A0)
	struct FMovieSceneFloatChannel                     Translation[0x2];                                         // 0x0220(0x00A0)
	struct FMovieSceneFloatChannel                     RotationAngle;                                            // 0x0360(0x00A0)
	struct FMovieSceneFloatChannel                     Scale;                                                    // 0x0400(0x00A0)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.MovieSceneComposurePostMoveSettingsSection");
		return ptr;
	}

};


// Class Composure.MovieSceneComposurePostMoveSettingsTrack
// 0x0000 (0x0080 - 0x0080)
class UMovieSceneComposurePostMoveSettingsTrack : public UMovieScenePropertyTrack
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Composure.MovieSceneComposurePostMoveSettingsTrack");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
