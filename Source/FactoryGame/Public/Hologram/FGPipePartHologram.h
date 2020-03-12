// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.
#pragma once
#include "Array.h"
#include "Engine/StaticMesh.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "../FGPipeConnectionComponent.h"
#include "../Resources/FGPoleDescriptor.h"
#include "FGPipePartHologram.generated.h"


/**
 * Hologram for constructing supports that pipelines can snap to.
 */
UCLASS()
class FACTORYGAME_API AFGPipePartHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
	
public:
	AFGPipePartHologram();
    
	virtual void GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty, class FDefaultAllocator> & OutReplicatedProps) const override; // MODDING EDIT: Needed for the implementer to detect it

	virtual void BeginPlay() override;

	// Begin AFGHologram interface
	virtual bool DoMultiStepPlacement( bool isInputFromARelease )  override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void CheckValidFloor( ) override;
	// End AFGHologram interface



	/** Set the height of the support */
	void SetSupportLength( float height );

	/** Get the connections the pipeline snaps to */
	FORCEINLINE UFGPipeConnectionComponentBase* GetSnapConnection() const { return mSnapConnection; }

	/** Snap this supports's snap connection to to the given connection. */
	void SnapToConnection( UFGPipeConnectionComponentBase* connection, FVector preSnapLocation );

protected:
	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual void CheckClearance() override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram interface

private:
	UFUNCTION()
	void OnRep_SupportMesh();

	/** Updates the relative offset for mSupportHeightComponent based on mSupportMesh */
	void UpdateSupportLengthRelativeLoc();

protected:
	/** The most fitting mesh for our aim height. */
	UPROPERTY( ReplicatedUsing = OnRep_SupportMesh )
	FPoleHeightMesh mSupportMesh;

private:
	/** The connection conveyors snap to, used when placing a support automatically. */
	UPROPERTY()
	UFGPipeConnectionComponentBase* mSnapConnection;

	/** True if we've placed it on the ground and is working with the height */
	bool mIsAdjustingLength;
	bool mCanAdjustLength;

	/*Compoent stapped to on another actor during placement*/
	class UFGPipeConnectionComponentBase* mSnappedConnectionComponent = nullptr;

	/** Can this support be stacked. */
	bool mCanStack;
	float mStackLength;

	/** Used to determine whether the relative offset needs to be updated for the support mesh */
	bool mSupportLengthMarkedDirty : 1;

	/** The support mesh. */
	UPROPERTY()
	class UStaticMeshComponent* mSupportMeshComponent;

	/** The scene component for adjusting the length of the support. */
	UPROPERTY()
	class USceneComponent* mSupportLengthComponent;


public:
	FORCEINLINE ~AFGPipePartHologram() = default;
};
