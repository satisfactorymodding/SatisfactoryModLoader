// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGPillarHologram.generated.h"

UENUM()
enum class EPillarHologramBuildStep : uint8
{
	PHBS_Placement,
	PHBS_Zoop
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPillarHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGPillarHologram();

	// Begin Actor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End Actor interface

	// Begin AFGHologram interface
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual AActor* Construct( TArray<AActor*>& out_children, FNetConstructionID constructionID ) override;
	virtual void SetMaterial( class UMaterialInterface* material ) override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual void GetSupportedBuildModes_Implementation( TArray<TSubclassOf<UFGHologramBuildModeDescriptor>>& out_buildmodes ) const override;
	virtual void OnBuildModeChanged() override;
	virtual bool CanBeZooped() const override;
	// End AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void FilterAttachmentPoints( TArray< const FFGAttachmentPoint* >& Points, AFGBuildable* pBuildable, const FHitResult& HitResult ) const override;
	virtual void CreateAttachmentPointTransform( FTransform& out_transformResult, const FHitResult& HitResult, AFGBuildable* pBuildable, const FFGAttachmentPoint& BuildablePoint, const FFGAttachmentPoint& LocalPoint ) override;
	// End AFGBuildableHologram interface

	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	// End FGConstructionMessageInterface

	virtual void OnPendingConstructionHologramCreated_Implementation( AFGHologram* fromHologram ) override;
	
protected:
	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface
	
	// Begin AFGBuildableHologram interface
	virtual bool IsHologramIdenticalToBuildable( class AFGBuildable* buildable, const FVector& hologramLocationOffset ) const override;
	// End AFGBuildableHologram interface
	
	UFUNCTION()
	void OnRep_CurrentZoop();
	
private:
	UPROPERTY()
	UStaticMeshComponent* mMeshComponent;

	/** Instanced Mesh Component. Used for zooping. */
	UPROPERTY()
	class UInstancedStaticMeshComponent* mInstancedMeshComponent;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	float mForceVerticalSnapThreshold;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	int32 mMaxZoop;

	UPROPERTY( ReplicatedUsing = OnRep_CurrentZoop )
	int32 mCurrentZoop;
	
	FVector mSize;

	FVector mSnappedLocation;

	bool mDownZoopDirectionBlocked;
	bool mUpZoopDirectionBlocked;

	UPROPERTY( Replicated )
	EPillarHologramBuildStep mBuildStep;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf<class UFGHologramBuildModeDescriptor > mBuildModeZoop;
};
