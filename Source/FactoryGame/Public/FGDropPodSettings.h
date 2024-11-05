// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "ItemAmount.h"
#include "Engine/DeveloperSettings.h"
#include "Templates/SubclassOf.h"
#include "FGDropPodSettings.generated.h"

class UFGItemDescriptor;

/** Describes possible item rarities for the drop pod package */
UENUM()
enum class EFGDropPodDebrisRarity
{
	None,
	Common,
	Uncommon,
	Rare
};

/** A single item in the drop pod item randomization pool */
USTRUCT()
struct FACTORYGAME_API FFGDropPodDebrisItemEntry
{
	GENERATED_BODY()

	/** Item that this entry contains */
	UPROPERTY( EditAnywhere, Category = "Item Entry" )
	TSoftClassPtr<UFGItemDescriptor> ItemClass;

	/** Minimum normalized (0-1.0) stack size this item can spawn */
	UPROPERTY( EditAnywhere, Category = "Item Entry", meta = ( ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.001", UIMax = "1.0" ) )
	float MinStackSize;

	/** Maximum normalized (0-1.0) stack size this item can spawn */
	UPROPERTY( EditAnywhere, Category = "Item Entry", meta = ( ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.001", UIMax = "1.0" ) )
	float MaxStackSize;
};

/** Rarity group describes a configuration of a single rarity tier inside of the drop pod package */
USTRUCT()
struct FACTORYGAME_API FFGDropPodDebrisGroup
{
	GENERATED_BODY()

	/** Rarity that this group describes */
	UPROPERTY( EditAnywhere, Category = "Item Group" )
	EFGDropPodDebrisRarity Rarity{};

	/** Number of items around the drop pod that this group can spawn at least */
	UPROPERTY( EditAnywhere, Category = "Item Group" )
	int32 MinItems{0};

	/** Number of items around the drop pod that this group can spawn at most */
	UPROPERTY( EditAnywhere, Category = "Item Group" )
	int32 MaxItems{0};

	/** Pool of the items this item group can spawn */
	UPROPERTY( EditAnywhere, Category = "Item Group" )
	TArray<FFGDropPodDebrisItemEntry> ItemPool;
};

/** Describes a single tier of the crash site debris that is randomized each game */
USTRUCT()
struct FACTORYGAME_API FFGDropPodDebrisPackage
{
	GENERATED_BODY()
	
	/** Describes each group that is used to generate the items around the drop pod */
	UPROPERTY( EditAnywhere, Category = "Drop Pod" )
	TArray<FFGDropPodDebrisGroup> ItemGroups;
};

/**
 * Settings for the drop pod generation.
 */
UCLASS( Config = Game, DefaultConfig, meta = ( DisplayName = "Drop Pod Settings" ) )
class FACTORYGAME_API UFGDropPodSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** Definitions of the possible debris that can spawn around the drop pods */
	UPROPERTY( EditAnywhere, Config, Category = "Drop Pod" )
	TArray<FFGDropPodDebrisPackage> mDebrisPackageTiers;

	static UFGDropPodSettings* Get();
};
