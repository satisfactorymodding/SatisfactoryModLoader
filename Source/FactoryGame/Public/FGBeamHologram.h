// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGBeamHologram.generated.h"

UENUM()
enum class EBeamHologramBuildStep : uint8
{
	BHBS_Placement,
	BHBS_Zoop
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBeamHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGBeamHologram();

	// Begin Actor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End Actor interface

	// Begin AFGHologram interface
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual int32 GetRotationStep() const override;
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf<UFGHologramBuildModeDescriptor> >& out_buildmodes ) const override;
	virtual void ConfigureActor( AFGBuildable* inBuildable ) const override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual bool CanBeZooped() const override;
	// End AFGHologram interface

	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	// End FGConstructionMessageInterface

	virtual void OnPendingConstructionHologramCreated_Implementation( AFGHologram* fromHologram ) override;

protected:
	UFUNCTION()
	void OnRep_CurrentLength();

	// Begin AFGBuildableHologram Interface
	virtual bool IsHologramIdenticalToBuildable( class AFGBuildable* buildable, const FVector& hologramLocationOffset ) const override;
	virtual void CreateAttachmentPointTransform( FTransform& out_transformResult, const FHitResult& HitResult, AFGBuildable* pBuildable, const FFGAttachmentPoint& BuildablePoint, const FFGAttachmentPoint& LocalPoint ) override;
	// End AFGBuildableHologram Interface

private:
	void CreateVerticalBeam( const FHitResult& hitResult, bool allowDiagonal );
	void CreateFreeformBeam( const FHitResult& hitResult );

	void SetCurrentLength( float newLength );
	
protected:
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeDiagonal;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeFreeForm;
	
private:
	UPROPERTY()
	UStaticMeshComponent* mBeamMesh;
	
	float mSize;

	float mDefaultLength;
	float mMaxLength;

	UPROPERTY( ReplicatedUsing = OnRep_CurrentLength )
	float mCurrentLength;

	FVector mSnappedLocation;

	FRotator mSnappedRotation;

	UPROPERTY( Replicated )
	EBeamHologramBuildStep mBuildStep;
};
