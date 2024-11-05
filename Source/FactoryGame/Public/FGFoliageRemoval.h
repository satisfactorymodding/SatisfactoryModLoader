// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGFoliageTypes.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGFoliageRemovalSubsystem.h"
#include "FGFoliageRemoval.generated.h"


/** Legacy removals. Kept for save compatibility. */
USTRUCT()
struct FRemovedInstance
{
	GENERATED_BODY()

	/** Stored in world space */
	UPROPERTY( SaveGame, NotReplicated ) 
	FTransform Transform;
};

/** Legacy removals. Kept for save compatibility. */
USTRUCT()
struct FRemovedInstanceArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( SaveGame, NotReplicated )
	TArray< FRemovedInstance >	Items;
};

/**
 * Contains all removals into one foliage type/level component. The 
 */
UCLASS(notplaceable)
class FACTORYGAME_API AFGFoliageRemoval : public AFGStaticReplicatedActor, public IFGSaveInterface
{
	GENERATED_BODY()
	friend class UFGFoliageEditorSubsystem;
public:	
	/** Ctor */
	AFGFoliageRemoval();

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

protected:
	/** Deprecated in favor of mRemovalLocations and mRemovalIndices */
	UPROPERTY( SaveGame )
	FRemovedInstanceArray mRemovedInstances;

	/**
	 * Contains the saved locations of all removals of a foliage type/level
	 */
	UPROPERTY( SaveGame )
	TSet< FVector > mRemovalLocations;

	/** The name of the level that this actor removes foliage from, so that the foliage system can find it */
	UPROPERTY( SaveGame )
	FName mLevelName;

	/** The name of mesh component to use the level */
	UPROPERTY( VisibleAnywhere, SaveGame )
	FName mFoliageTypeName;
	
	/** ServerOnly: The bounds of the level we have foliage in (@todo: Can we remove this savegame tag?)*/
	UPROPERTY( SaveGame )
	FBox mLevelBounds;
};
