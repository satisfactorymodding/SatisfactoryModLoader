// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGItemPickup.h"
#include "FGSubsystem.h"
#include "FGWorldScannableData.h"
#include "FGScannableSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogScannableSubsystem, Log, All );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGScannableSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

public:
	/** Get the representation manager, this should always return something unless you call it really early. */
	static AFGScannableSubsystem* Get( UWorld* world );

	/** Get the representation manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Scanner", DisplayName = "GetScannableSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGScannableSubsystem* Get( UObject* worldContext );

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

	const TArray< class AFGDropPod* >& GetUnlootedDropPods() const { return mUnlootedDropPods; }

private:
	void CacheDestroyedActors();
	void CacheDropPods();

	friend class AFGBuildableRadarTower;

	UPROPERTY( Transient )
	TArray< class AFGBuildableRadarTower* > mRadarTowers;
	
	UPROPERTY( Transient )
	TArray<FWorldScannableData> mAvailableItemPickups;

	/* For now since these are net culled we replicate which ones arent looted so we can filter out the looted ones in object scanner */
	UPROPERTY( Transient, Replicated )
	TArray< class AFGDropPod* > mUnlootedDropPods;

	UPROPERTY( Transient )
	TArray< class AFGCreatureSpawner* > mScannableCreatureSpawners;
	
};
