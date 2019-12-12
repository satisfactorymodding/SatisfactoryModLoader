// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Resources/FGItemDescriptor.h"
#include "FGMaterialEffect_Build.h"
#include "FGSettings.h"
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

	/** Material on hologram for power connections. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Material" )
	class UMaterialInstance* mDefaultPowerConnectionMaterial;

	/** Mesh used to visualize input or output connections location. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultConveyorConnectionFrameMesh;

	/** Mesh used to visualize input or output connections direction. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultConveyorConnectionArrowMesh;

	/** Mesh used to visualize power connections. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Connections" )
	class UStaticMesh* mDefaultPowerConnectionMesh;

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

	/** Material applied to build guides to visualize alignment in build mode. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGuides|Alignment" )
	class UMaterialInstance* mBuildGuideMaterial;

	/** Material applied to build guides specifically for conveyor belts to visualize alignment in build mode. @note Do not set in code! */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGuides|Alignment" )
	class UMaterialInstance* mConveyorBuildGuideMaterial;

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

	/** The mesh to be used as legs on factories */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	class UStaticMesh* mLegMesh;

	/** The mesh to be used as foots on factories */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	class UStaticMesh* mFootMesh;

	/** Maximum length when we want to spawn the legs */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	float mMaxFeetLength;

	/** The class we want to spawn for dismantle shortcuts */
	UPROPERTY( EditDefaultsOnly, Category= "Shortcuts" )
	TSubclassOf<class UFGDismantleShortcut> mDismantleShortcutClass;

	/** The class we want to spawn for recipe shortcuts */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TSubclassOf<class UFGRecipeShortcut> mRecipeShortcutClass;

	/** Names if the input actions that defines the shortcuts. This maps directly to their index (so first entry here should mean that it should call ExecuteShortcut 0) */
	UPROPERTY( EditDefaultsOnly, Category = "Shortcuts" )
	TArray< FName > mShortcutMap;
};
