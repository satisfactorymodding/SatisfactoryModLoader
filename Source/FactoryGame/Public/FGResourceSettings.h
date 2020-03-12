// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSettings.h"
#include "Resources/FGItemDescriptor.h"
#include "FGResourceSettings.generated.h"

USTRUCT()
struct FACTORYGAME_API FItemSettings
{
	GENERATED_BODY()

	FItemSettings() :
		ResourceClass( nullptr ),
		Resolution( INDEX_NONE ),
		MasterMaterial( nullptr )
	{
	}

	FItemSettings( TSubclassOf< class UFGItemDescriptor > resource, int32 resolution ) :
		ResourceClass( resource ),
		Resolution( resolution )
	{
	}

	/** The class (and it's subclasses) that we want to specify the resolution for */
	UPROPERTY( EditDefaultsOnly, Category="Icon", meta = ( AllowAbstract = true ) )
	TSubclassOf< class UFGItemDescriptor > ResourceClass;

	/** The x and y resolution of the icon (must be power of 2), -1 means no icon */
	UPROPERTY( EditDefaultsOnly, Category="Icon")
	int32 Resolution;

	/** Material that should be used for each icon, need to have a parameter named Texture */
	UPROPERTY( EditDefaultsOnly, Category="Icon")
	class UMaterial* MasterMaterial;

	// Might be a idea to put the stage class here if we want some really special icons...

public:
	FORCEINLINE ~FItemSettings() = default;
};

/**  */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FResourceDepositPackage
{
	GENERATED_BODY()

	/** Chance in roulette selection to get the package */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ResourceDepositPackage" )
	float DropChance;

	/** What resource class to use */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ResourceDepositPackage" )
	TSubclassOf< class UFGResourceDescriptor > ResourceClass;

	/** Amount of resources in deposit as minimum */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ResourceDepositPackage" )
	int32 MinAmount;

	/** Amount of resources in deposit as max */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ResourceDepositPackage" )
	int32 MaxAmount;

	/** How much to get per "mine cycle" */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "ResourceDepositPackage" )
	int32 MiningAmount;

public:
	FORCEINLINE ~FResourceDepositPackage() = default;
};

/**
*
*/
UCLASS(abstract)
class FACTORYGAME_API UFGResourceSettings : public UFGSettings
{
	GENERATED_BODY()
public:
	UFGResourceSettings();

	/** Helper to directly get the resource setting without going through UFGGlobalSettings */
	static UFGResourceSettings* Get();

#if WITH_EDITORONLY_DATA && WITH_EDITOR
	/** Get the size of the icon for this resource class */
	static const FItemSettings& GetResourceSettings( TSubclassOf< class UFGItemDescriptor > resourceClass );
#endif

	/** Get a random resource deposit package */
	UFUNCTION( BlueprintPure, Category = "ResourceDepositPackage" )
	static const FResourceDepositPackage& GetRandomResourceDepositData( int32& out_resourceDepositPackageIdx, AActor* worldContext );

	/** Gets deposit data with a specified resource class
	 * returns false if no deposit data existed with that resource class */
	UFUNCTION( BlueprintPure, Category = "ResourceDepositPackage" )
	static const FResourceDepositPackage& GetResourceDepositDataFromClass( TSubclassOf< class UFGResourceDescriptor > desiredResourceClass, int32& out_resourceDepositPackageIdx, AActor* worldContext );

	/** Gets the size of a Given Stack Size enum from the stack size TMap */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	int32 GetStackSizeFromEnum( EStackSize stackSize ) const;

	/** List of all available resource deposit packages */
	UPROPERTY( EditAnywhere, Category = "ResourceDepositPackage" )
	TArray< FResourceDepositPackage > mResourceDepositTable;
	
	/** Index 0 is poor amount, 1 is normal and 2 is rich */
	UPROPERTY( EditDefaultsOnly, EditFixedSize, Category = "Resources" )
	TArray< FInt32Interval > mResourceAmount;

	/** Index 0 is poor amount, 1 is normal and 2 is rich */
	UPROPERTY( EditDefaultsOnly, EditFixedSize, Category = "Resources" )
	TArray< float > mPurityMultiplier;

	UPROPERTY( EditDefaultsOnly, Category = "Resources" )
	TSubclassOf< class UFGResourceDescriptor > mWaterResourceDescriptor; 

	/** Mesh used on items that do not have their own specified. */
	UPROPERTY( EditDefaultsOnly, Category = "Buildable" )
	class UStaticMesh* mDefaultItemMesh;

	/** How many of diffrent items can be in the same stack */
	UPROPERTY( EditDefaultsOnly, Category = "Items" )
	TMap< int32, EStackSize > mStackSizes;

	/** The class of item we want to drop when we drop something */
	UPROPERTY( EditDefaultsOnly, Category = "Drops" )
	TSubclassOf< class AFGItemPickup_Spawnable > mItemDropClass;

#if WITH_EDITORONLY_DATA
	/** The stage that should be used to make icons */
	UPROPERTY( EditDefaultsOnly, Category = "Icon" )
	TSubclassOf<class AFGRenderTargetStage> mStageClass;

	/** Resolutions of different item classes */
	UPROPERTY( EditDefaultsOnly, Category="Icon")
	TArray< FItemSettings > mIconSettings;
#endif

public:
	FORCEINLINE ~UFGResourceSettings() = default;
};
