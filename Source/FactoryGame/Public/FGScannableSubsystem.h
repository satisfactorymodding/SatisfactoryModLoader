// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

	const TArray< class AFGDropPod* >& GetUnlootedDropPods() const { return mUnlootedDropPods; }

	/** Whether or not the specified item pickup exists. */
	bool DoesPickupExist( const FGuid& PickupGuid ) const;

private:
	void CacheDropPods();

	// Called by AFGWorldScannableDataGenerator
	void AssignAvailableItemPickups( const TArray< FWorldScannableData >& ItemPickups );

	friend class AFGBuildableRadarTower;

	UPROPERTY( Transient )
	TArray< class AFGBuildableRadarTower* > mRadarTowers;
	
	UPROPERTY( Transient )
	TArray<FWorldScannableData> mAvailableItemPickups;

	/** List of destroyed pickups. */
	UPROPERTY( SaveGame )
	TSet< FGuid > mDestroyedPickups;

	/* For now since these are net culled we replicate which ones arent looted so we can filter out the looted ones in object scanner */
	UPROPERTY( Transient, Replicated )
	TArray< class AFGDropPod* > mUnlootedDropPods;

	UPROPERTY( Transient )
	TArray< class AFGCreatureSpawner* > mScannableCreatureSpawners;
	
};
