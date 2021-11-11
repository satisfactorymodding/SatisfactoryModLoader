// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGFactoryHologram.h"
#include "Resources/FGPoleDescriptor.h"
#include "FGPoleHologram.generated.h"


UENUM()
enum class EPoleHologramBuildStep : uint8
{
	PHBS_PlacementAndRotation,
	PHBS_AdjustHeight
};

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
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual AActor* Construct( TArray<AActor*>& out_children, FNetConstructionID constructionID ) override;
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf< UFGHologramBuildModeDescriptor > >& out_buildmodes ) const override;
	virtual void OnBuildModeChanged() override;
	virtual int32 GetBaseCostMultiplier() const override;

	virtual void ResetBuildSteps();
	// End AFGHologram interface

	/** Set the height of the pole, useful for parent holograms. */
	void SetPoleHeight( float height );

	// Begin IFGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual void ServerPostConstructMessageDeserialization() override;
	virtual void OnConstructMessagedDeserialized_Implementation() override;
	// End IFGConstructionMessageInterface

	virtual void OnPendingConstructionHologramCreated_Implementation( class AFGHologram* fromHologram ) override;

	// Returns the desired height (not clamped to the mesh sizes available)
	FORCEINLINE float GetPoleHeight() const { return mPoleHeight; }
	
	// Returns the Height for the currently active mesh
	float GetActiveMeshHeight() const;

protected:
	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface

private:
	UFUNCTION()
	void OnRep_PoleMesh();

	/** Updates the relative offset for mPoleHeightComponent based on mPoleMesh */
	void UpdatePoleHeightRelativeLoc();

protected:
	/** The most fitting mesh for our aim height. */
	UPROPERTY( ReplicatedUsing = OnRep_PoleMesh )
	FPoleHeightMesh mPoleMesh;

	bool mCanAdjustHeight;

	EPoleHologramBuildStep mBuildStep;
private:

	/** Can this pole be stacked. */
	bool mCanStack = false;
	float mStackHeight = 200;

	/** Used to determine whether the relative offset needs to be updated for the pole mesh */
	bool mPoleHeightMarkedDirty : 1;

	/** The pole mesh. */
	UPROPERTY()
	class UStaticMeshComponent* mPoleMeshComponent;

	/** The scene component for adjusting the height of the pole. */
	UPROPERTY()
	class USceneComponent* mPoleHeightComponent;

	/** Instanced Mesh Component. */
	UPROPERTY()
	class UInstancedStaticMeshComponent* mInstancedMeshComponent;

	UPROPERTY( CustomSerialization )
	float mPoleHeight;

	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	int32 mMaxZoopAmount;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeZoop;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	FVector mClearanceExtent;
};
