// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGProximitySubsystem.generated.h"

USTRUCT( BlueprintType )
struct FMapAreaParticleCollection
{
	GENERATED_BODY()

	/* Array of map areas that all use the same particle */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Proximity" )
	TArray< TSubclassOf< class UFGMapArea > > Areas;

	/* Particle associated with map areas */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Proximity" )
	class UParticleSystem* Particle;
};

/*Struct for future extend~ability.*/
USTRUCT()
struct FProximityEntry
{
	GENERATED_BODY()
	
	/* floating point for memory sake */
	FVector3f Location;
	
	/* Weight */
	float Weight;
};

UCLASS( Blueprintable )
class FACTORYGAME_API AFGProximitySubsystem : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFGProximitySubsystem();

	void SetupPlayerBinds(class AFGPlayerController* Player);

	UFUNCTION( BlueprintCallable, Category = "ProximitySubsystem" )
	static AFGProximitySubsystem* GetProximitySubsystem(UObject* World);

	/*Note this function has precision loss due to optimizations (double to float) .*/
	UFUNCTION( BlueprintCallable, Category = "ProximitySubsystem" )
	bool IsNearBase(const FVector& Location, float Range, int32 MinimumRequiredBuildables, bool bIgnoreWeight = false ) const;

	UFUNCTION( BlueprintCallable, Category = "ProximitySubsystem" )
	static void StaticRegisterFactoryBuildingToProximitySystem( AActor* Actor, float Weight = 1.f );
	
	UFUNCTION( BlueprintCallable, Category = "ProximitySubsystem" )
	void RegisterFactoryBuildingToProximitySystem( FVector Location, float Weight ); 

	UFUNCTION( BlueprintCallable, Category = "ProximitySubsystem" )
	static void StaticRemoveFactoryBuildingToProximitySystem( AActor* Actor, float Weight = 1.f);

	UFUNCTION( BlueprintCallable, Category = "ProximitySubsystem" )
	void RemoveFactoryBuildingToProximitySystem( FVector Location, float Weight); 

	/** Player entered a new map area */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Proximity" )
	void OnEnteredMapArea( class AFGPlayerControllerBase* playerController, TSubclassOf< class UFGMapArea > newArea );

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
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface
public:	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;
	
private:
	FORCEINLINE FIntVector LocationToGrid( FVector Location ) const
	{
		Location = Location.GridSnap(mRegionSize);
		return FIntVector(Location.X,Location.Y,Location.Z);
	}

	FORCEINLINE TArray<FIntVector> FindRelevantCells( FVector Location, float Range ) const
	{
		TArray<FIntVector> Out;
		
		const int32 SearchLength = FMath::DivideAndRoundUp(Range / 2,mRegionSize);
		
		for (int32 y = -SearchLength; y < SearchLength; y++ )
		{
			for (int32 x = -SearchLength; x < SearchLength; x++ )
			{
				for (int32 z = -SearchLength; z < SearchLength; z++ )
				{
					const FVector TestLocation = FVector(
						Location.X + (x * mRegionSize),
						Location.Y + (y * mRegionSize), 
						Location.Z + (z * mRegionSize) );

					FIntVector IntVector = FIntVector(TestLocation.GridSnap(mRegionSize));
					
					if (mFactoryRegions.Contains(IntVector))
					{
						Out.Add(IntVector);
					}
				}
			}
		}
		
		return Out;
	}
	
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

	UPROPERTY(EditDefaultsOnly)
	float mRegionSize = 25000;
	
	/* Locations of factory buildings that are considered for base. */
	TMap<FIntVector,TArray<FProximityEntry>> mFactoryRegions;


#if WITH_EDITOR
	static TMap<UObject*, AFGProximitySubsystem*> mPIESubsystemMap;
#else
	static AFGProximitySubsystem* SubsystemPtr;
#endif
};
