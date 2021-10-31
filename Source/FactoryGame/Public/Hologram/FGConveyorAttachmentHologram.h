// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGConveyorAttachmentHologram.generated.h"

/**
 * Hologram for conveyor attachments, such as splitters/mergers.
 */
UCLASS()
class FACTORYGAME_API AFGConveyorAttachmentHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	AFGConveyorAttachmentHologram();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual float GetHologramHoverHeight() const override;
	virtual void GetIgnoredClearanceActors( TArray< AActor* >& ignoredActors ) const override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual bool ShouldBuildableBeConsideredForGuidelines( class AFGBuildable* buildable ) const override;
	// End AFGBuildableHologram Interface

protected:
	// Begin AFGHologram interface
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram Interface

	void SnapToConnection( class UFGFactoryConnectionComponent* connectiontoSnapTo, class UFGFactoryConnectionComponent* myConnectionToSnapWith, FVector locationToDetermineSideIfAplicable );

public:
	/** Name of the pass through input connection. */
	static FName mInputConnection1;

	/** Name of the pass through output connection. */
	static FName mOutputConnection1;



private:
	/** Used to limit the placement in turns. What's the maximum offset to check from center to detect the curve. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Attachment" )
	float mMaxValidTurnOffset;
	/** Used to limit the placement in turns. What's the maximum angle. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Attachment" )
	float mMaxValidTurnAngle;

	/** The conveyor we snapped to. */
	UPROPERTY()
	class AFGBuildableConveyorBelt* mSnappedConveyor;

	/** The connection we snapped to. */
	UPROPERTY()
	class UFGFactoryConnectionComponent* mSnappedConection = nullptr;

	TArray<class UFGFactoryConnectionComponent* > mConnections;
	int8 mSnappingConnectionIndex = -1;

	/** The offset we snapped on the conveyor. */
	float mSnappedConveyorOffset;
};
