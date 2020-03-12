// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGFoundationSubsystem.generated.h"

USTRUCT()
struct FACTORYGAME_API FBuilding
{
	GENERATED_BODY();
public:
	/** Which buildables belong to this building. */
	UPROPERTY( SaveGame )
	TArray< class AFGBuildable* > Buildables;

public:
	FORCEINLINE ~FBuilding() = default;
};

/**
 * Class keeping track of which buildables that for a building.
 */
UCLASS()
class FACTORYGAME_API AFGFoundationSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	// Begin AActor interface
	virtual void Serialize( FArchive& ar ) override;
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Get the foundation subsystem, this should always return something unless you call it really early. */
	static AFGFoundationSubsystem* Get( UWorld* world );

	/**
	 * Add a buildable to a building.
	 * @param buildable - A valid buildable, this is where we get the foundation id from.
	 * @param isNewBuilding - Set this to allow the subsystem to generate and set a building ID.
	 */
	void AddBuildable( class AFGBuildable* buildable, bool isNewBuilding = false );

	/**
	 * Remove the buildable from a building, i.e. dismantled.
	 * @param buildable - A valid buildable, this is where we get the foundation id from.
	 */
	void RemoveBuildable( class AFGBuildable* buildable );

	/**
	 * Get all buildables of the type in the given building.
	 */
	template< typename T >
	void GetTypedBuildable( int32 buildingID, TArray< T* >& out_buildables ) const;

private:
	/** Generates a new UID. */
	int32 GenerateUniqueBuildingID();

private:
	/** Counter for generating new UIDs. */
	int32 mIDCounter;

	/** All the buildings in the game, map with foundation ID and the building struct. */
	UPROPERTY( SaveGame )
	TMap< int32, FBuilding > mBuildings;

public:
	FORCEINLINE ~AFGFoundationSubsystem() = default;
};

template< typename T >
void AFGFoundationSubsystem::GetTypedBuildable( int32 buildingID, TArray< T* >& out_buildables ) const
{
	if( auto building = mBuildings.Find( buildingID ) )
	{
		for( auto buildable : building->Buildables )
		{
			if( T* specificBuildable = Cast< T >( buildable ) )
			{
				out_buildables.Add( specificBuildable );
			}
		}
	}
}
