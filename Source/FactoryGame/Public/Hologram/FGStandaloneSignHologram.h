// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGGenericBuildableHologram.h"
#include "FGStandaloneSignHologram.generated.h"


UENUM()
enum class ESignHologramBuildStep : uint8
{
	ESHBS_SnapToActor,
	ESHBS_AdjustHeight
};

/**
 * Hologram for placing signs. Handles snapping to walls as well as spawning a child pole hologram
 */
UCLASS()
class FACTORYGAME_API AFGStandaloneSignHologram : public AFGGenericBuildableHologram
{
	GENERATED_BODY()
	
public:
	AFGStandaloneSignHologram();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface


	// Begin AFGHologram Interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual void Scroll( int32 delta ) override;
	virtual void OnInvalidHitResult() override;
	// End AFGHologram Interface
	
	// Begin AFGBuildableHologram Interface
	virtual void CheckValidFloor() override;
	// End AFGBuildableHologram Interface

	const FVector2D& GetSignHologramWorldDimensions() const { return mSignDimensions; }

protected:

	// The build step of this hologram. Are we placing? Changing height? Rotating?
	ESignHologramBuildStep mBuildStep;

private:
	/** The Support Hologram to use with this sign hologram when placed on the ground */
	UPROPERTY( EditDefaultsOnly, Category = "Sign" )
	TSubclassOf< class UFGRecipe > mDefaultSignSupportRecipe;

	/** The child pole hologram active while the sign is placed under certain circumstances */
	UPROPERTY( Replicated )
	class AFGSignPoleHologram* mChildSignPoleHologram = nullptr;

	/* The world size sign dimensions of the sign being constructed */
	FVector2D mSignDimensions;

	/* The offset of this hologram when it is being placed at the end of a sign pole */
	FVector mPoleOffset;

	/** The scale size for the poles pulled from the buildable class */
	FVector2D mPoleScale;

	/** Optional value for aligning holograms on the Y axis for variable sizes */
	float mSignToSignOffset;
};
