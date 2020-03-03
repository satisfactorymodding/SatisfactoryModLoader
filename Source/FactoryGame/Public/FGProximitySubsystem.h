// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGSubsystem.h"
#include "FGProximitySubsystem.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FMapAreaParticleCollection
{
	GENERATED_BODY()

	/* Array of map areas that all use the same particle */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Proximity" )
	TArray< TSubclassOf< class UFGMapArea > > Areas;

	/* Particle associated with map areas */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Proximity" )
	class UParticleSystem* Particle;

public:
	FORCEINLINE ~FMapAreaParticleCollection() = default;
};

UCLASS( Blueprintable )
class FACTORYGAME_API AFGProximitySubsystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGProximitySubsystem();

	/** Player entered a new map area */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Proximity" )
	void OnEnteredMapArea( TSubclassOf< class UFGMapArea > newArea );

	/** Owning controller got a new pawn */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Proximity" )
	void OnPawnChanged( class APawn* newPawn );

	/** Gets particle system mapped to provided map area. Can return null if no mapping exist */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Proximity" )
	class UParticleSystem* GetParticleSystemFromMapArea( TSubclassOf< class UFGMapArea > inArea );

	/** Spawns a decal at the given location and rotation, fire and forget. Does not replicate.
		If we reached max amount of decals an old one will be replaced

	 * @param DecalMaterial - decal's material
	 * @param DecalSize - size of decal
	 * @param Location - location to place the decal in world space
	 * @param Rotation - rotation to place the decal in world space
	 * @param LifeSpan - destroy decal component after time runs out (0 = infinite)
	 */
	void SpawnPooledDecal( const UObject* WorldContextObject, class UMaterialInterface* DecalMaterial, FVector DecalSize, FVector Location, FRotator Rotation = FRotator( 0, 0, 0 ), float LifeSpan = 0 );
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;
private:
	UPROPERTY()
	class AFGPlayerController* mOwningController;

	UPROPERTY(  )
	USceneComponent* mRootComponent;

	/** Contains mappings of particle system that should play when entering a given map area */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Proximity" )
	TArray< FMapAreaParticleCollection > mMapAreaParticleCollection;

	/** Pool of decals */
	UPROPERTY()
	TArray< UDecalComponent* > mPooledDecals;

	/** How many decals we want to show */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Proximity" )
	int32 mMaxNumDecals;

public:
	FORCEINLINE ~AFGProximitySubsystem() = default;
};
