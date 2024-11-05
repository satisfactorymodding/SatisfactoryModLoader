// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGItemDescriptor.h"
#include "FGMaterialEffect_Build.h"
#include "FGSettings.h"
#include "Curves/CurveFloat.h"
#include "Styling/SlateBrush.h"
#include "FGFactorySettings.generated.h"

USTRUCT(BlueprintType)
struct FCategory
{
	GENERATED_BODY()

	FCategory()
	{
	}

	FCategory( FText defaultName ) :
		Name( defaultName )
	{
	}

	/** Localized name of a category */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FText Name;

	/** Icon for the category */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FSlateBrush Icon;
};

USTRUCT( BlueprintType )
struct FViscosityToPuddlePair
{
	GENERATED_BODY()
	
	FViscosityToPuddlePair() :
		Viscosity( 0.f ),
		Puddle( 0.f )
	{}

	/** Viscosity for this entry */
	UPROPERTY( EditDefaultsOnly, meta=(ClampMin="0.0", ClampMax="100.0" ) )
	float Viscosity;

	/** Required puddle amount before this fluid viscosity can be moved from a fluid box [ 0 , 1 ] normalized fill amount */
	UPROPERTY( EditDefaultsOnly, meta = ( ClampMin = "0.0", ClampMax = "1.0" ) )
	float Puddle;
};

/**
 * Common settings for the factory buildings and their holograms.
 */
UCLASS( abstract )
class FACTORYGAME_API UFGFactorySettings : public UFGSettings
{
	GENERATED_BODY()
public:
	UFGFactorySettings();

	/** Get a random construction sound to play. */
	UFUNCTION( BlueprintPure, Category = "Buildable" )
	static class UAkAudioEvent* GetRandomConstructionSound();

	/** Get a random dismantle sound to play. */
	UFUNCTION( BlueprintPure, Category = "Buildable" )
	static class UAkAudioEvent* GetRandomDismantleSound();

	/** Get the puddle requirement for the given viscosity, see where it is used for more info about the puddeling. */
	static float GetPuddleRequirementForViscosity( float viscosity );

	/** Quick accessor to get the singleton instance */
	static class UFGFactorySettings* Get();

public:
	/** Material on hologram for valid placement. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Material" )
	class UMaterialInstance* mDefaultValidPlacementMaterial;

	/** Material on hologram for valid placement. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Material" )
	class UMaterialInstance* mDefaultValidPlacementMaterialSimplified;

	/** Material on hologram for invalid placement. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Material" )
	class UMaterialInstance* mDefaultInvalidPlacementMaterial;

	/** Material on hologram for input connections. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Material" )
	class UMaterialInstance* mDefaultInputConnectionMaterial;

	/** Material on hologram for output connections. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Material" )
	class UMaterialInstance* mDefaultOutputConnectionMaterial;

	/** Material on hologram for directionally neutral connections. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Material" )
	class UMaterialInstance* mDefaultNeutralConnectionMaterial;

	/** Material on hologram for power connections. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Material" )
	class UMaterialInstance* mDefaultPowerConnectionMaterial;

	/** Default Factory Primary - Unchanging color regardless of slot */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryColor" )
	FLinearColor mDefaultFactoryColor_Primary;

	/** Default Factory Secondary - Unchanging color regardless of slot */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryColor" )
	FLinearColor mDefaultFactoryColor_Secondary;

	/** Mesh used to visualize attachment points for connection. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultAttachmentPointConnectionMesh;

	/** Mesh used to visualize input or output connections location. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultConveyorConnectionFrameMesh;

	/** Mesh used to visualize input or output connections direction. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultConveyorConnectionArrowMesh;

	/** Mesh used to visualize pipeline connections location  @note Do not set in Code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultPipeConnectionFrameMesh;

	/** Mesh used to visualize pipeline connections direction (Consumer / Producer) @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultPipeConnectionArrowMesh;

	/** Mesh used to visualize power connections. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultPowerConnectionMesh;

	/** Mesh used to visualize forward direction of blueprints. @note Do not set in code! */
    UPROPERTY( EditDefaultsOnly, Category = "Hologram|Blueprints" )
    class UStaticMesh* mBlueprintDirectionIndicatorMesh;

	/** Material for blueprint direction indicator. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Blueprints" )
	class UMaterialInstance* mBlueprintDirectionIndicatorMaterial;

	/** Minimum scale of the blueprint direction indicator mesh. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Blueprints" )
	float mBlueprintDirectionMeshScale;

	/** How much forward offset to add to the blueprint direction indicator. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Blueprints" )
	float mBlueprintDirectionMeshForwardOffset;
	
	/** How much vertical offset to add to the blueprint direction indicator. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Blueprints" )
	float mBlueprintDirectionMeshHeightOffset;

	/** How much to rotate the blueprint direction indicator (degrees). */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Blueprints" )
	float mBlueprintDirectionMeshRotation;

	/** Whether or not to put the direction mesh indicator on the ground. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Blueprints" )
	bool mBlueprintDirectionMeshPlaceOnGround;

	/** Material for blueprint proxies. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Blueprints" )
	class UMaterialInstance* mBlueprintProxyMaterial;

	/** Mesh used to visualize the clearance mesh on factories @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Clearance" )
	class UStaticMesh* mClearanceMesh;

	/** Material on hologram for clearance. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Clearance" )
	class UMaterialInstance* mClearanceMaterial;

	/** Default sound loop placed on holograms. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Sound" )
	class UAkAudioEvent* mHologramLoopSound;

	/** Snapping sound for holograms, e.g. when a conveyor snaps to an output. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Sound" )
	class UAkAudioEvent* mHologramSnapSound;

	/** Mesh used to visualize alignment in build mode. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGuides|Alignment" )
	class UStaticMesh* mBuildGuideMesh;

	/** Width of buildguide visualization lines. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGuides|Alignment" )
	float mBuildGuideWidth;
	
	/** Default color of building buidelines for input connections */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGuides|Alignment" )
	FColor mGuidelineColorInput;

	/** Default color of building buidelines for output connections */
    UPROPERTY( EditDefaultsOnly, Category = "BuildGuides|Alignment" )
    FColor mGuidelineColorOutput;
	
	/** Material applied to build guides to visualize alignment in build mode. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGuides|Alignment" )
	class UMaterialInstance* mBuildGuideMaterial;

	/** Crate spawned when we dismantle an actor or when we die. It will be filled with the refund if it doesn't fit in the players inventory. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	TSubclassOf< class AFGCrate > mInventoryDropCrate;

	/** Default sound played when constructing a building, a random from the list is played. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable|Build Effect" )
	TArray< class UAkAudioEvent* > mConstructionSounds;
		
	/** Default sound played when dismantling a building, a random from the list is played. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable|Build Effect" )
	TArray< class UAkAudioEvent* > mDismantleSounds;

	/** Effect to play when a building is built */ //[DavalliusA:Mon/01-04-2019] seems to only be used for replays? //@TODO: see if we can't store this in a way more suitable for replays... a waste to have it in a global class like this
	UPROPERTY( EditDefaultsOnly, Category = "Buildable|Build Effect" )
	TSubclassOf< class UFGMaterialEffect_Build > mBuildEffect;

	/** Effect to play when a building is dismantled */ //[DavalliusA:Mon/01-04-2019] seems to never ba used? //@TODO: see if we can't remove this
	UPROPERTY( EditDefaultsOnly, Category = "Buildable|Build Effect" )
	TSubclassOf< class UFGMaterialEffect_Build > mDismantleEffect;

	/** Material used when looking at buildings for dismantle */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable|Dismantle" )
	class UMaterialInterface* mDismantlePendingMaterial;

	/** The default buildgun class to spawn */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class AFGBuildGun > mBuildGunClass;

	/** The default resource scanner class to spawn */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class AFGResourceScanner > mResourceScannerClass;

	/** The default resource miner class to spawn */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class AFGResourceMiner > mResourceMinerClass;
	
	/** The class to be used as a boom box player */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class AFGBoomBoxPlayer > mBoomBoxPlayerClass;

	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class UFGItemDescriptor > mBoomBoxEquipmentDesc;

	/** The mesh to be used as legs on factories */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	class UStaticMesh* mLegMesh;

	/** The mesh to be used as foots on factories */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	class UStaticMesh* mFootMesh;

	/** Maximum length when we want to spawn the legs */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	float mMaxFeetLength;

	/** The class we want to spawn for recipe shortcuts */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TSubclassOf<class UFGRecipeShortcut> mRecipeShortcutClass;

	/** The class we want to spawn for customization shortcuts */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TSubclassOf< class UFGFactoryCustomizationShortcut > mCustomizationShortcutClass;

	/** The class we want to spawn for emote shortcuts */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TSubclassOf< class UFGEmoteShortcut > mEmoteShortcutClass;

	/** The class we want to spawn for blueprint shortcuts */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TSubclassOf< class UFGBlueprintShortcut > mBlueprintShortcutClass;

	/** Names if the input actions that defines the shortcuts. This maps directly to their index (so first entry here should mean that it should call ExecuteShortcut 0) */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TArray< FName > mShortcutMap;

	/** The number of hotbars */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	int32 mNumHotbars;
	
	/** The number of slots per hot bar */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	int32 mNumSlotsPerHotbar;

	/** The number of slots per hot bar on consoles */
	UPROPERTY(EditDefaultsOnly, Category = "Shortcuts")
	int32 mNumSlotsPerHotbarOnConsoles;

	// Default rate of converting FluidBox content into inventory stacks. Measured in Liters / Second
	UPROPERTY( EditDefaultsOnly, Category = "Pipes" )
	int32 mFluidToInventoryStackRate;

	// Default rate of converting Inventory stacks in to Fluid for FluidBox content. Measured in Liters / Second
	UPROPERTY( EditDefaultsOnly, Category = "Pipes" )
	int32 mInventoryStackToFluidRate;

	/**	Pressure to add to all buildables with a PipeConnection output Fluid Box. This acts as a default pressure as if there was a pump inside every producing buildable.
	*	This can be disabled per connection on the PipeConnectionFactory component
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Pipes" )
	float mAddedPipeProductionPressure;

	/** Float to float pairing the required normalized fill amount [ 0 , 1 ] a pipe must be before it can transfer liquid out for a given viscosity
	*	Higher viscosities should require more significant puddling to get the feel of sluggishness through pipe segments. Intermediate values will be lerped to.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Pipes" )
	TArray< FViscosityToPuddlePair > mViscosityToPuddlePairs;

	/** Material Param Collection containing the panini settings so scaling can be exposed to the Settings Menu */
	UPROPERTY( EditDefaultsOnly, Category = "Rendering" )
	class UMaterialParameterCollection* mPaniniProjectionCollection;

	/** How the snapping threshold is affected over distance between a hologram and a snapping target. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Hologram|Alignment" )
	FRuntimeFloatCurve mGuidelineSnappingDistanceThresholdCurve;

	/** How misaligned a guideline is allowed to be in order to be displayed. In CM. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Hologram|Alignment" )
	float mGuidelineDisplayDistanceThreshold;

	/** How misaligned a guideline is allowed to be between two connections. In degress. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Hologram|Alignment" )
	float mGuidelineConnectionAngleThreshold;

};
