// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGItemPickup.h"
#include "FGSubsystem.h"
#include "FGWorldScannableData.h"
#include "FGScannableSubsystem.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogScannableSubsystem, Log, All );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGScannableSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

	friend class AFGWorldScannableDataGenerator;

public:
	/** Get the representation manager, this should always return something unless you call it really early. */
	static AFGScannableSubsystem* Get( UWorld* world );

	/** Get the representation manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Scanner", DisplayName = "GetScannableSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGScannableSubsystem* Get( UObject* worldContext );

	// Begin IFGSaveInterface
    virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
    virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
    virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
    virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
    virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
    virtual bool NeedTransform_Implementation() override { return false; }
    virtual bool ShouldSave_Implementation() const override { return true; }
    // End IFSaveInterface

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	void RegisterRadarTower( class AFGBuildableRadarTower* radarTower );
	void UnRegisterRadarTower( class AFGBuildableRadarTower* radarTower );

	UFUNCTION()
	void OnLevelPlacedActorDestroyed(AActor* destroyedActor);

	void OnDropPodLooted( class AFGDropPod* dropPod );
	
	void OnCreatureSpawnerUpdated( class AFGCreatureSpawner* creatureSpawner, bool scannable );
	void OnCreatureSpawnerAdded( class AFGCreatureSpawner* creatureSpawner );
	void OnCreatureSpawnerRemoved( class AFGCreatureSpawner* creatureSpawner );

	FORCEINLINE const TArray<FWorldScannableData>& GetAvailableItemPickups() const { return mAvailableItemPickups; }
	FORCEINLINE const TArray<FWorldScannableData>& GetAvailableDropPods() const { return mAvailableDropPods; }
	FORCEINLINE const TArray<class AFGCreatureSpawner*>& GetScannableCreatureSpawners() const { return mScannableCreatureSpawners; }

	/** Whether or not the specified item pickup exists. */
	bool DoesPickupExist( const FGuid& PickupGuid ) const;
	/** Returns whenever the given drop pod GUID has already been looted */
	bool HasDropPodBeenLooted( const FGuid& dropPodGuid ) const;
private:
	// Called by AFGWorldScannableDataGenerator to populate the subsystem with the data cached during cooking
	void AssignScannableData( const TArray<FWorldScannableData>& itemPickups, const TArray<FWorldScannableData>& dropPods );

	UPROPERTY( Transient )
	TArray< class AFGBuildableRadarTower* > mRadarTowers;
	
	UPROPERTY( Transient )
	TArray<FWorldScannableData> mAvailableItemPickups;

	/** All crash site actors available for this level, cached in the editor time */
	UPROPERTY( Transient )
	TArray<FWorldScannableData> mAvailableDropPods;

	/** List of destroyed pickups. */
	UPROPERTY( SaveGame )
	TSet<FGuid> mDestroyedPickups;

	/** List of looted crash sites */
	UPROPERTY( SaveGame )
	TSet<FGuid> mLootedDropPods;

	UPROPERTY( Transient )
	TArray< class AFGCreatureSpawner* > mScannableCreatureSpawners;
	
};
