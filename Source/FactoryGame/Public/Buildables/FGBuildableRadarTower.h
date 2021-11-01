// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGActorRepresentationInterface.h"
#include "FGBuildableRadarTower.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FRadarTowerRadiusUpdated );
DECLARE_LOG_CATEGORY_EXTERN( LogRadarTower, Log, All );

/**
 * Radar Tower reveals nearby fog of war on the Map. Expanding over time until it reaches its max limit.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRadarTower : public AFGBuildableFactory, public IFGActorRepresentationInterface
{
	GENERATED_BODY()

	AFGBuildableRadarTower();
	
public:
	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual class UTexture2D* GetActorRepresentationTexture() override;
	virtual FText GetActorRepresentationText() override;
	virtual void SetActorRepresentationText( const FText& newText ) override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	virtual float GetActorFogOfWarRevealRadius() override;
	virtual ECompassViewDistance GetActorCompassViewDistance() override;
	virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	// End IFGActorRepresentationInterface
	
	// Begin Actor Interface
#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif
	// End Actor Interface

	// Begin Save Interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface

	// Begin Factory Interface
	virtual void Factory_StartProducing() override;
	virtual void Factory_StopProducing() override;
	virtual void Factory_TickProducing( float dt ) override;
	// End Factory Interface

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	float GetCurrentRevealRadius();

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE float GetTimeToNextExpansion(){ return mTimeToNextExpansion; };
	
	/** Returns a which step we are currently on, will never return higher than mNumRadarExpansionSteps */
	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE int32 GetCurrentExpansionStep(){ return FMath::Min(mCurrentExpansionStep, mNumRadarExpansionSteps-1); }

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE int32 GetNumRadarExpansionSteps(){ return mNumRadarExpansionSteps; }

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE float GetMinRevealRadius(){ return mMinRevealRadius; }

	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	FORCEINLINE float GetMaxRevealRadius(){ return mMaxRevealRadius; }

	/** Returns a normalized value for how much we will have revealed of the max reveal radius on a certain step */
	UFUNCTION( BlueprintPure, Category = "Radar Tower" )
	float GetNormalizedProgressValueForStep( int32 step );

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	void SetRepresentationText( const FText& text );

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FText GetRepresentationText();

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	float GetTowerHeight();

private:

	/** 
	* Broadcast that the radius of the radar tower have been updated. 
	* If this is called from non game thread we schedule a call to be made on game thread.
	*/
	UFUNCTION()
	void OnRep_OnRadiusUpdated();

	/** Returns how much we will have revealed on a certain step */
	float GetRevealRadiusOnStep( int32 step );

	/** returns true if this radar tower is expanded to it's maximum range */
	bool IsRadarExpandedToMax();

public:
	UPROPERTY( BlueprintAssignable, Category = "Radar Tower" )
	FRadarTowerRadiusUpdated OnRadarTowerRadiusUpdated;

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
	
	/** The step we are on right now between 0 and mNumRadarExpansionSteps-1  */
	UPROPERTY( ReplicatedUsing=OnRep_OnRadiusUpdated, SaveGame )
	int32 mCurrentExpansionStep;

	/** Time left until we expand the reveal area  */
	UPROPERTY( Replicated, SaveGame )
	float mTimeToNextExpansion;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

};
