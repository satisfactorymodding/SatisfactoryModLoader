// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGPipeConnectionComponent.h"
#include "FGPoleHologram.h"
#include "FGPipelinePoleHologram.generated.h"

/**
 * Hologram for constructing supports that pipelines can snap to.
 */
UCLASS()
class FACTORYGAME_API AFGPipelinePoleHologram : public AFGPoleHologram
{
	GENERATED_BODY()
	
public:
	AFGPipelinePoleHologram();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void Scroll( int32 delta ) override;
	virtual void ReplaceHologram( AFGHologram* hologram, bool snapTransform ) override;
	// End AFGHologram interface

	/** Get the connections the pipeline snaps to */
	FORCEINLINE UFGPipeConnectionComponentBase* GetSnapConnection() const { return mSnapConnection; }

	/** Snap this supports's snap connection to to the given connection. */
	void SnapToConnection( UFGPipeConnectionComponentBase* connection, class AFGPipelineHologram* parentPipeline );

	virtual bool CanAdjustHeight() const override;

	void SetVerticalAngle( float newValue );
	FORCEINLINE float GetVerticalAngle() const { return mVerticalAngle; }

	virtual void UpdatePoleMesh() override;
	
protected:
	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

private:
	UFUNCTION()
	void OnRep_VerticalAngle();
	
protected:	
	/** if you should be able to adjust the vertical direction of the connection and top part of the pole*/
	UPROPERTY( EditDefaultsOnly )
	bool mCanAdjustVerticalAngle = true;
	
private:
	/** The connection conveyors snap to, used when placing a support automatically. */
	UPROPERTY()
	UFGPipeConnectionComponentBase* mSnapConnection;

	//Used to rotate the connection and top part vetically
	UPROPERTY( ReplicatedUsing = OnRep_VerticalAngle, CustomSerialization )
	float mVerticalAngle = 0.0f;

	/** The support mesh. */
	UPROPERTY()
	class UStaticMeshComponent* mSupportTopPartMeshComponent;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	FVector mClearanceExtent;

	bool mOnlySetPoleRotationWhileHoldingSnap;
};
