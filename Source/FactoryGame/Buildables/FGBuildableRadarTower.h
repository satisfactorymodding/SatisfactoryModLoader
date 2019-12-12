// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableFactory.h"
#include "FGBuildableRadarTower.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE( FRadarTowerRadiusExpanded );

/**
 * Radar Tower reveals nearby fog of war on the Map. Expanding over time until it reaches its max limit.
 */
UCLASS( Meta = (AutoJson = false) )
class FACTORYGAME_API AFGBuildableRadarTower : public AFGBuildableFactory
{
	GENERATED_BODY()

	AFGBuildableRadarTower();
	
public:
	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin Factory_ Interface
	virtual void Factory_StartProducing() override;
	virtual void Factory_StopProducing() override;
	virtual void Factory_TickProducing( float dt ) override;
	// End Factory_ Interface

	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	
	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	float GetCurrentRevealRadius();

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE float GetTimeToNextExpansion(){ return mTimeToNextExpansion; };
	
	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE int32 GetCurrentExpansionStep(){ return mCurrentExpansionStep; }

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE int32 GetNumRadarExpansionSteps(){ return mNumRadarExpansionSteps; }

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE float GetMinRevealRadius(){ return mMinRevealRadius; }

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE float GetMaxRevealRadius(){ return mMaxRevealRadius; }


protected:
	// Begin AActor interface
	virtual void Destroyed() override;
	//End AActor interface

private:
	UFUNCTION( Reliable, NetMulticast )
	void Multicast_ExpandRadarRadius();

public:
	UPROPERTY( BlueprintAssignable, Category = "Radar Tower" )
	FRadarTowerRadiusExpanded OnRadarTowerRadiusExpanded;

protected:	
	/** The initial reveal radius */
	UPROPERTY( EditDefaultsOnly, Category = "Radar Tower" )
	float mMinRevealRadius;

	/** The reveal radius when tower have fully expanded its range */
	UPROPERTY( EditDefaultsOnly, Category = "Radar Tower" )
	float mMaxRevealRadius;

	/** Total amount of steps the radar tower have between Min Reveal Radius to Max Reveal Radius */
	UPROPERTY( EditDefaultsOnly, Category = "Radar Tower" )
	int32 mNumRadarExpansionSteps;

	/** The time between radar expansions  */
	UPROPERTY( EditDefaultsOnly, Category = "Radar Tower" )
	float mRadarExpansionInterval;

private:
	
	/** The current expansion step  */
	UPROPERTY( SaveGame )
	int32 mCurrentExpansionStep;

	/** The timer handle for when we expand the radar towers area of effect  */
	FTimerHandle mExpansionTimerHandle;

	UPROPERTY( Replicated, SaveGame )
	float mTimeToNextExpansion;
};
