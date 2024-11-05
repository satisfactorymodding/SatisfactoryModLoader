// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGPipeConnectionComponent.h"
#include "Resources/FGPoleDescriptor.h"
#include "FGPipelineSupportHologram.generated.h"

UENUM()
enum class EPipelineSuppoortHologramBuildStep : uint8
{
	PSHBS_PlacementAndRotation,
	PSHBS_AdjustHeight
};

/**
 * Hologram for constructing supports that pipelines can snap to.
 */
UCLASS()
class FACTORYGAME_API AFGPipelineSupportHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
	
public:
	AFGPipelineSupportHologram();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AFGHologram interface
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FVector& hologramLocationOffset ) const override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease )  override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;

	virtual AActor* Construct( TArray<AActor*>& out_children, FNetConstructionID constructionID ) override;
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf< UFGBuildGunModeDescriptor > >& out_buildmodes ) const override;
	virtual void OnBuildModeChanged( TSubclassOf<UFGHologramBuildModeDescriptor> buildMode ) override;
	virtual bool CanNudgeHologram() const override;

	virtual void GetClearanceData( TArray< const FFGClearanceData* >& out_ClearanceData ) const override;

	virtual void ReplaceHologram( AFGHologram* hologram, bool snapTransform ) override;

	virtual int32 GetBaseCostMultiplier() const override;
	// End AFGHologram interface
	
	/** Set the height of the support */
	void SetSupportLength( float height );
	FORCEINLINE float GetSupportLength() const { return mSupportLength; }

	/** Get the connections the pipeline snaps to */
	FORCEINLINE UFGPipeConnectionComponentBase* GetSnapConnection() const { return mSnapConnection; }

	/** Snap this supports's snap connection to to the given connection. */
	void SnapToConnection( UFGPipeConnectionComponentBase* connection, class AFGPipelineHologram* parentPipeline );

	void ResetBuildSteps();

	void ResetVerticalRotation();

	void SetVerticalAngle( float newValue ) { mVerticalAngle = newValue; }
	FORCEINLINE float GetVerticalAngle() const { return mVerticalAngle; }
		
	/** Updates the relative offset for mSupportHeightComponent based on mSupportMesh */
	void UpdateSupportLengthRelativeLoc();
	void UpdateSupportMesh();
	
	void Scroll( int32 delta ) override;
	
protected:
	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface

private:
	UFUNCTION()
	void OnRep_VerticalAngle();

	UFUNCTION()
	void OnRep_SupportLength();
	
protected:
	FFGClearanceData mClearance;
	
	/** The most fitting mesh for our aim height. */
	UPROPERTY()
	FPoleHeightMesh mSupportMesh;

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

	UPROPERTY( ReplicatedUsing = OnRep_SupportLength, CustomSerialization )
	float mSupportLength = 0.0f;

	bool mCanAdjustLength;

	EPipelineSuppoortHologramBuildStep mBuildStep;

	/** Can this pole be stacked. */
	bool mCanStack = false;
	float mStackHeight = 200;

	/** Used to determine whether the relative offset needs to be updated for the support mesh */
	bool mSupportLengthMarkedDirty : 1;

	/** The support mesh. */
	UPROPERTY()
	class UStaticMeshComponent* mSupportMeshComponent;

	/** The support mesh. */
	UPROPERTY()
	class UStaticMeshComponent* mSupportTopPartMeshComponent;

	/** The scene component for adjusting the length of the support. */
	UPROPERTY()
	class USceneComponent* mSupportLengthComponent;

	/**Used to store the initial offset of the support length component, so we can compensate for it during placement*/
	float mSupportLengthOffset;

	/** Instanced Mesh Component. */
	UPROPERTY()
	class UInstancedStaticMeshComponent* mInstancedMeshComponent;

	UPROPERTY( EditDefaultsOnly, Category = "Pole" )
	int32 mMaxZoopAmount;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeZoop;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	FVector mClearanceExtent;
};
