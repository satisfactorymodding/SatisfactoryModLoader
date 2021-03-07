#pragma once
#include "CoreMinimal.h"
#include "AssetCategory.generated.h"

/** Describes categories asset packages fall into */
UENUM()
enum class EAssetCategory : uint8 {
	/** Unknown asset not falling into any of the categories described */
	EAC_Unknown,
	
	/** Blueprint asset, containing one UBlueprintGeneratedClass and one ClassDefaultObject for it */
	EAC_Blueprint,
	/** User defined widget blueprint asset, similar to EAC_Blueprint, but class type is UWidgetBlueprintGeneratedClass */
	EAC_UserWidget,
	/** Animation blueprint, containing state machines and attached skeleton in addition to normal blueprint logic */
	EAC_AnimationBlueprint,
	/** User defined structure asset, contains a single UUserDefinedStruct object */
	EAC_UserDefinedStruct,
	/** User defined enumeration type asset, contains a single UUserDefinedEnum object */
	EAC_UserDefinedEnum,

	/** Contains a single Texture2D object describing normal texture encoded in one of supported formats */
	EAC_Texture2D,
	/** Specialized Texture2D containing some extra properties and serving as an atlas */
	EAC_CurveLinearColorAtlas,
	/** Contains a single cubemap texture object (UTextureCube), describing a cube map texture used for reflection purposes/sky sphere emulation */
	EAC_TextureCube,
	/**
	 * Describes FactoryGame map area texture. Currently there is only one asset of that type
	 * Apparently it is used for capturing map areas in editor and to define map areas. Ben confirmed that it is a custom asset - Archengius, 12.15.20
	 */
	EAC_FGMapAreaTexture,
	/** Describes UTextureRenderTarget2D texture asset that can be used as a rendering target, or drawn like a normal Texture2D object */
	EAC_TextureRenderTarget2D,
	
	/** Material asset that possibly contains input variables and compiled shader code */
	EAC_Material,
	/** Material instance asset contains a single UMaterialInstanceConstant, which contains Material object with variable overrides applied */
	EAC_MaterialInstance,
	/** Describes UMaterialParameterCollection object which contains set of parameters that multiple materials can reference */
	EAC_MaterialParameterCollection,
	/**
	 * Describes a single material function node that can be embedded into material code
	 * Not worth dumping, function code is not preserved and they only contain basic display information - Archengius, 12.15.20
	 */
	EAC_MaterialFunction,
	/** Contains a single USubsurfaceProfile object, describing Subsurface Scattering profile for given material asset */
	EAC_SubsurfaceProfile,
	
	/** Contains a single particle system with any number of effects */
	EAC_ParticleSystem,

	/** Skeleton asset, containing one USkeleton object describing skeleton */
	EAC_Skeleton,
	/** StaticMesh asset, containing one UStaticMesh object */
	EAC_StaticMesh,
	/** SkeletalMesh asset, containing USkeletalMesh object with set skeleton */
	EAC_SkeletalMesh,

	/** Animation sequence (UAnimSequence) describes a single animation bound to some skeleton that can only be played on meshes using it */
	EAC_AnimSequence,
	/** Animation montage (UAnimMontage) describes composite animation consisting of multiple sequences and blending between them */
	EAC_AnimMontage,
	/** Level sequence (ULevelSequence) is a container for animation scene designed in Sequencer and happening in the world */
	EAC_LevelSequence,
	/** Animation played on player camera, contains a single UCameraAnim object */
	EAC_CameraAnim,
	/**
	 * Generic blend space asset stemming from UBlendSpaceBase class
	 * All of these assets are categorized as a single type because their creation and serialization matches,
	 * and neither of them exposes any special properties except adding few properties and overriding some methods
	 */
	EAC_BlendSpaceBase,

	/** Contains a single UPhysicalMaterial object describing material physical interaction with the world */
	EAC_PhysicalMaterial,
	/** Contains a single UPhysicsAsset object describing physics state of a single skeletal mesh */
	EAC_PhysicsAsset,
	/** Contains PhysX TireConfig object describing wheel configuration for a vehicle */
	EAC_TireConfig,

	/** Individual WWise audio event asset */
	EAC_AkAudioEvent,
	/** Individual WWise audio bank asset */
	EAC_AkAudioBank,

	/** Describes a string table asset mapping localization keys to display strings */
	EAC_StringTable,
	/** Describes a single data table with predefined row type and containing some data in form of rows */
	EAC_DataTable,
	
	/** Describes font asset used for text rendering */
	EAC_Font,
	/** Contains raw font data in cooked UE-specific format */
	EAC_FontFace,
	
	/**
	 * Describes an interpolation curve of generic kind. can be color curve, float curve, or a vector curve
	 * All of them are handled together because internally they all use FRichCurve instances for serialization
	 * and a single UCurveBase parent class + a single asset factory for creation
	 */
	EAC_CurveBase,

	/** Contains prebuilt map-dependent data, mostly lighting and shadows related data */
	EAC_MapBuildDataRegistry,
	/** Contains a level with all the actors inside */
	EAC_World,
	/** Contains static instanced mesh used as a foliage type */
	EAC_FoliageType_InstancedStaticMesh,
	/** Describes grass type used on a landscape, possibly containing multiple grass varieties with their associated parameters */
	EAC_LandscapeGrassType,
	/** Describes ULandscapeLayerInfoObject with predefined physical material and layer name */
	EAC_LandscapeLayerInfo,

	/** Describes a media source obtaining video from file */
	EAC_FileMediaSource,
	/** Describes media texture used for rendering a video obtained from MediaSource through MediaPlayer */
	EAC_MediaTexture,
	/** Describes media player instance used for playing videos */
	EAC_MediaPlayer,

	/** Describes AI blackboard used for storing various information during behavior tree execution */
	EAC_BlackboardData,
	/** Describes AI behavior tree, which is used for scripting behavior of creatures */
	EAC_BehaviorTree,
	/** Describes environment query, used by AI for obtaining information about environment around */
	EAC_EnvQuery,
};

/** Handles asset categorization */
class SML_API FAssetCategoryHelper {
public:
	/** Performs contained objects analysis to determine category this asset package falls into */
    static EAssetCategory DeterminePackageCategory(UPackage* Package);

	/** Converts asset category enumeration value to string */
	static FString AssetCategoryToString(EAssetCategory AssetCategory);
};