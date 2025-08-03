// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGPipeConnectionComponent.h"
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

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AFGHologram interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void CheckValidFloor( ) override;
	virtual void GetIgnoredClearanceActors( TSet< AActor* >& ignoredActors ) const override;
	virtual bool CanNudgeHologram() const override;
	// End AFGHologram interface

	/** Get the connections the pipeline snaps to */
	FORCEINLINE UFGPipeConnectionComponentBase* GetSnapConnection() const { return mSnapConnection; }

	/** Snap this supports's snap connection to to the given connection. */
	void SnapToConnection( UFGPipeConnectionComponentBase* connection, FVector preSnapLocation );

protected:
	
	// Begin AFGBuildableHologram interface
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram interface

private:
	/** The connection conveyors snap to, used when placing a support automatically. */
	UPROPERTY()
	UFGPipeConnectionComponentBase* mSnapConnection;

	/* Component snapped to on another actor during placement */
	UPROPERTY( CustomSerialization, Replicated )
	class UFGPipeConnectionComponentBase* mSnappedConnectionComponent;

};
