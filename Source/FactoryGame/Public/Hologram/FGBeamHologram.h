// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf<UFGBuildGunModeDescriptor> >& out_buildmodes ) const override;
	virtual void ConfigureActor( AFGBuildable* inBuildable ) const override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual bool CanBeZooped() const override;
	virtual bool CanIntersectWithDesigner( AFGBuildableBlueprintDesigner* designer ) const override;
	// End AFGHologram interface
protected:
	UFUNCTION()
	void OnRep_CurrentLength();

	// Begin AFGBuildableHologram Interface
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FVector& hologramLocationOffset ) const override;
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

	UPROPERTY( EditDefaultsOnly, Category = "Beam" )
	float mCostMultiplier;
	
private:
	UPROPERTY()
	UStaticMeshComponent* mBeamMesh;
	
	float mSize;

	float mDefaultLength;
	float mMaxLength;

	UPROPERTY( ReplicatedUsing = OnRep_CurrentLength, CustomSerialization )
	float mCurrentLength;

	FVector mSnappedLocation;

	FRotator mSnappedRotation;

	UPROPERTY( Replicated )
	EBeamHologramBuildStep mBuildStep;
};
