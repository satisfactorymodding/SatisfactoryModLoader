// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGWorldGridSubsystem.h"
#include "GameFramework/Actor.h"
#include "FGWorldGridGeneratorActor.generated.h"

UCLASS()
class FACTORYGAME_API AFGWorldGridGeneratorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGWorldGridGeneratorActor();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	/** Gets the number of divisions this world grid is split up into. */
	UFUNCTION( BlueprintPure, Category = "World Grid" )
	FORCEINLINE int32 GetNumGridDivisions() const { return mNumGridDivisions; }

	/** Gets the world grid cells that belong to this actor. */
	UFUNCTION( BlueprintPure, Category = "World Grid" )
	FORCEINLINE TArray< FFGWorldGridCellData > const& GetWorldGridCells() const { return mWorldCells;}

	/** Gets the min value of the world grid bounds. */
	UFUNCTION( BlueprintPure, Category = "World Grid" )
	FORCEINLINE FVector2D const& GetWorldGridMin() const { return mWorldGridMin; }

	/** Gets the max value of the world grid bounds. */
	UFUNCTION( BlueprintPure, Category = "World Grid" )
	FORCEINLINE FVector2D const& GetWorldGridMax() const { return mWorldGridMax; }
	
private:
#if WITH_EDITOR
	/** Used to generate a new cached world grid on this actor in editor. */
	UFUNCTION( BlueprintCallable, Category = "World Grid", meta = ( CallInEditor = "true" ) )
	void UpdateWorldGrid();
#endif

	/** Generates a world grid and fills CellData, GridMin and GridMax with the result. */
	void GenerateWorldGrid( TArray< FFGWorldGridCellData >& CellData, FVector2D& GridMin, FVector2D& GridMax ) const;

private:
	UPROPERTY( EditDefaultsOnly, Category = "World Grid" )
	int32 mNumGridDivisions;

	UPROPERTY( VisibleAnywhere, Category = "World Grid" )
	FVector2D mWorldGridMin;

	UPROPERTY( VisibleAnywhere, Category = "World Grid" )
	FVector2D mWorldGridMax;
	
	UPROPERTY( VisibleAnywhere, Category = "World Grid" )
	TArray< FFGWorldGridCellData > mWorldCells;
};
