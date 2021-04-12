// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGLadderHologram.generated.h"

UENUM()
enum class ELadderHologramBuildStep : uint8
{
	LHBS_SnapToActor,
	LHBS_AdjustHeight
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGLadderHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGLadderHologram();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetMaterial( class UMaterialInterface* material ) override;
	virtual int32 GetBaseCostMultiplier() const override;
	// End AFGHologram interface

	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	//virtual void ClientPreConstructMessageSerialization() override;

	virtual void OnPendingConstructionHologramCreated_Implementation( AFGHologram* fromHologram ) override;

protected:
	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidFloor() override;
	// End AFGBuildableHologram Interface

	UFUNCTION()
	void OnRep_TargetSegmentHeight();

	void UpdateClearance();

private:
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	float mLadderBottomSnapThreshold;

	UPROPERTY( VisibleAnywhere, Category = "Ladder" )
	float mWidth;

	UPROPERTY( VisibleAnywhere, Category = "Ladder" )
	float mMeshHeight;

	UPROPERTY( VisibleAnywhere, Category = "Ladder" )
	FVector mPlacementPosition;

	UPROPERTY( VisibleAnywhere, Category = "Ladder" )
	int32 mMaxSegmentCount;

	UPROPERTY( VisibleAnywhere, ReplicatedUsing = OnRep_TargetSegmentHeight, Category = "Ladder" )
	int32 mTargetSegmentHeight;

	UPROPERTY( VisibleAnywhere, Category = "Ladder" )
	bool mCanDragDown;

	UPROPERTY( VisibleAnywhere, Category = "Ladder" )
	bool mCanDragUp;

	/** Instanced Mesh Component. */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	class UInstancedStaticMeshComponent* mInstancedMeshComponent;

	UPROPERTY( Replicated )
	ELadderHologramBuildStep mBuildStep = ELadderHologramBuildStep::LHBS_SnapToActor;
};
