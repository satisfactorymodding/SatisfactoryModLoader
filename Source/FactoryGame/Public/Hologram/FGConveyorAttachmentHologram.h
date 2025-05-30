// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
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
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual void PreHologramPlacement( const FHitResult& hitResult, bool callForChildren ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual float GetHologramHoverHeight() const override;
	virtual void GetIgnoredClearanceActors( TSet< AActor* >& ignoredActors ) const override;
	virtual bool CanNudgeHologram() const override;
	virtual TOptional<TSubclassOf<UFGRecipe>> ProcessHologramOverride( const FHitResult& hitResult ) const override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual bool ShouldActorBeConsideredForGuidelines( class AActor* actor ) const override;
	virtual void CheckValidFloor() override;
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
	
	/** Name of the pass through top lift connection. */
	static FName mLiftConnection_Top;

	/** Name of the pass through bottom lift connection. */
	static FName mLiftConnection_Bottom;

	inline class UFGFactoryConnectionComponent* GetSnappedConnection() const { return mSnappedConnection; }

protected:
	/** Used to limit the placement in turns. What's the maximum offset to check from center to detect the curve. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Attachment" )
	float mMaxValidTurnOffset;
	/** Used to limit the placement in turns. What's the maximum angle. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Attachment" )
	float mMaxValidTurnAngle;

	/** The conveyor we snapped to. */
	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildableConveyorBase* mSnappedConveyor;

	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildableConveyorAttachment* mUpgradedConveyorAttachment;

	/** The connection we snapped to. */
	UPROPERTY( CustomSerialization )
	class UFGFactoryConnectionComponent* mSnappedConnection = nullptr;

	TArray<class UFGFactoryConnectionComponent* > mConnections;

	/** The connection we are snapped by */
	UPROPERTY( Replicated, CustomSerialization )
	int8 mSnappingConnectionIndex = -1;

	/** The offset we snapped on the conveyor. */
	UPROPERTY( Replicated, CustomSerialization )
	float mSnappedConveyorOffset;
	
	// The set of names of components that act as input/output connectors on our attachment. See static declarations for "mInputConnection1" etc.
	TSet<FName> mBuildablePropertyNames;
};
