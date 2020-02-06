// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGFactoryHologram.h"
#include "../Resources/FGPoleDescriptor.h"
#include "FGPoleHologram.generated.h"


/**
 * Base for holograms that can be raised/lowered, e.g. conveyor poles.
 */
UCLASS()
class FACTORYGAME_API AFGPoleHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	AFGPoleHologram();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	void BeginPlay();
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool MultiStepPlacement() override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;

	virtual void CheckClearance() override;

	/** Helper */
	bool CheckClearanceForBuildingMesh( UStaticMeshComponent* mesh, const FComponentQueryParams& params = FComponentQueryParams::DefaultComponentQueryParams );
	// End AFGHologram interface

	/** Set the height of the pole, useful for parent holograms. */
	void SetPoleHeight( float height );

protected:
	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

private:
	UFUNCTION()
	void OnRep_PoleMesh();

	/** Updates the relative offset for mPoleHeightComponent based on mPoleMesh */
	void UpdatePoleHeightRelativeLoc();

protected:
	/** The most fitting mesh for our aim height. */
	UPROPERTY( ReplicatedUsing = OnRep_PoleMesh )
	FPoleHeightMesh mPoleMesh;

private:
	/** True if we've placed it on the ground and is working with the height */
	bool mIsAdjustingHeight;
	bool mCanAdjustHeight;

	/** Can this pole be stacked. */
	bool mCanStack;
	float mStackHeight;

	/** Used to determine whether the relative offset needs to be updated for the pole mesh */
	bool mPoleHeightMarkedDirty : 1;

	/** The pole mesh. */
	UPROPERTY()
	class UStaticMeshComponent* mPoleMeshComponent;

	/** The scene component for adjusting the height of the pole. */
	UPROPERTY()
	class USceneComponent* mPoleHeightComponent;
};
