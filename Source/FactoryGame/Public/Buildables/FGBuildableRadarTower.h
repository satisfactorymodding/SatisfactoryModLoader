// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGActorRepresentationInterface.h"
#include "FGRadarTowerRepresentation.h"
#include "FGScannableDetails.h"
#include "FGBuildableRadarTower.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnObjectScanned, AActor*, newRepresentation );
DECLARE_STATS_GROUP( TEXT( "RadarTower" ), STATGROUP_RadarTower, STATCAT_Advanced );
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
	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor interface
	
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

	// Begin Save Interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface

	// Begin Factory Interface
	virtual void Factory_StartProducing() override;
	virtual void Factory_StopProducing() override;
	virtual void Factory_TickProducing( float dt ) override;
	// End Factory Interface
	
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

	/** Gets the representation for this radar tower */
	UFUNCTION( BlueprintPure, Category = "Representation" )
	FORCEINLINE UFGRadarTowerRepresentation* GetRadarTowerRepresentation() const { return mRadarTowerRepresentation; } 

	void ScanForResources();
	void AddResourceNodes( const TArray< class AFGResourceNodeBase* >& resourceNodes );
	void ClearScannedResources();
	
	void InitScanForObjects();
	void TryRemovePickup( AActor* removedActor );
	void TryAddCreatureSpawner( class AFGCreatureSpawner* creatureSpawner );
	void TryRemoveCreatureSpawner( class AFGCreatureSpawner* creatureSpawner );
	void TryRemoveDropPod( class AFGDropPod* dropPod );

private:
	bool IsInRadarTowerRange( const FVector& location ) const;
	void UpdateRepresentationValues();


protected:	
	/** The reveal radius of this radar tower */
	UPROPERTY( EditDefaultsOnly, Category = "Radar Tower" )
	float mRevealRadius;

	/** The descriptors we would like to scan for */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	TArray< TSubclassOf< class UFGItemDescriptor > > mScannableDescriptors;

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( Transient )
	TArray< class AFGResourceNodeBase* > mScannedResourceNodes;

	UPROPERTY( Transient, Replicated ) // replicated for now can probably be moved to not be replicated after we get client simulation
	UFGRadarTowerRepresentation* mRadarTowerRepresentation;

	TMap<TSubclassOf<UFGItemDescriptor>, int32> mFoundDescriptors;
	TMap< TSubclassOf<AActor>, TSubclassOf<UFGItemDescriptor> > mActorToDescriptorMapping;
	TArray< TSubclassOf<AActor> > mDescriptorActorClasses;
};
