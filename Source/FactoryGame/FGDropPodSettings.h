// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "ItemDrop.h"
#include "FGSettings.h"
#include "FGDropPodSettings.generated.h"

/** Describes a package of items you can get in a drop. */
USTRUCT( BlueprintType )
struct FDropPackage
{
	GENERATED_BODY()
public:
	static FDropPackage NullDropPackage;

	FDropPackage() :
		DropChance( 0.0f ),
		RequiredSchematic( nullptr )
	{}

public:
	/** Text showing up when finding the drop. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DropPackage" )
	FText DropDisplayText;

	/** Chance in roulette selection to get the package. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DropPackage" )
	float DropChance;

	/** Item contained in the package */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DropPackage" )
	TArray< FItemDrop > Items;

	/** We can not find this package if we haven't purchased this schematic. */
	UPROPERTY( EditAnywhere, Category = "DropPackage" )
	TSubclassOf< class UFGSchematic > RequiredSchematic;
};

/**
 * Settings for the drop pods.
 */
UCLASS( abstract )
class FACTORYGAME_API UFGDropPodSettings : public UFGSettings
{
	GENERATED_BODY()
public:
	/** Get a random drop package */
	UFUNCTION( BlueprintPure, Category = "DropPackage" )
	static const FDropPackage GetRandomDropPackage( class UWorld* world );

protected:
	/** List of all available drop packages */
	UPROPERTY( EditAnywhere, Category = "DropPackage" )
	TArray< FDropPackage > mDropTable;
};
