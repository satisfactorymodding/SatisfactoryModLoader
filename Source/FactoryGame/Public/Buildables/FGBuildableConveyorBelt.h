// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/SplineComponent.h"
#include "FGBuildableConveyorBase.h"
#include "FGSplineBuildableInterface.h"
#include "FGUseableInterface.h"
#include "Components/SplineMeshComponent.h"
#include "FGBuildableConveyorBelt.generated.h"




/**
 * Base for conveyor belts.
 * Assumption: Conveyors are never rotated, rotation is always 0,0,0.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableConveyorBelt : public AFGBuildableConveyorBase, public IFGSplineBuildableInterface
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorBelt();

	friend class AFGConveyorItemSubsystem;
	
	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override;
	virtual	void SetupForSignificance() override;					// TODO deprecate
	virtual void UpdateMeshLodLevels(int32 newLodLevel) override;	// TODO deprecate
	// End IFGSignificanceInterface

	// Begin abstract instance interface.
	virtual TArray<FInstanceData> GetActorLightweightInstanceData_Implementation() override;
	virtual bool DoesContainLightweightInstances_Native() const override { return true; }
	// End abstract instance interface
	
	// Begin Buildable interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	virtual void OnBuildEffectFinished() override;
	// End Buildable interface

	// Begin AFGBuildableConveyorBase interface
	virtual float FindOffsetClosestToLocation( const FVector& location ) const override;
	virtual void GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const override;
	// End AFGBuildableConveyorBase interface

	/** Get the velocity of the conveyor where the based actor is. */
	FVector GetVelocityForBase( class AActor* basedActor, class UPrimitiveComponent* baseComponent ) const;

	//~ Begin IFGDismantleInterface
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	//~ End IFGDismantleInterface

	static void CreateClearanceData( class USplineComponent* splineComponent, const TArray< FSplinePointData >& splineData, const FTransform& conveyorTransform, TArray< FFGClearanceData >& out_clearanceData, float maxDistance = -1.0f );


	virtual float GetLastRenderTime() const override;
	
	/*Update bounds of the vis mesh.*/
	void UpdateVisibilityMesh();
	
	/**
	 * Split this conveyor in two.
	 * First part [0,offset] and second part [offset,length].
	 * @note Callee is responsible for not creating snakes or 'zero belts'.
	 *       I.e. Do not split to close to the beginning or end.
	 *		 Will dismantle the current conveyor belt on successful split
	 * @param connectNewConveyors - Should the new conveyors be connected to each other after the split
	 * @return The second part of the splitted conveyor; nullptr on failure to split.
	 */
	static TArray< AFGBuildableConveyorBelt* > Split( AFGBuildableConveyorBelt* conveyor, float offset, bool connectNewConveyors );

	/**
	 * Merge two conveyors.
	 * @return The merged conveyor; nullptr on failure to split.
	 */
	static AFGBuildableConveyorBelt* Merge( TArray< AFGBuildableConveyorBelt* > conveyors );

	/**
	 * Respline a conveyor with the given spline.
	 */
	static AFGBuildableConveyorBelt* Respline( AFGBuildableConveyorBelt* conveyor, const TArray< FSplinePointData >& newSplineData );

	// Begin IFGSplineBuildableInterface
	virtual UFGConnectionComponent* GetSplineConnection0() const override;
	virtual UFGConnectionComponent* GetSplineConnection1() const override;
	virtual const TArray< FSplinePointData >& GetSplinePointData() const override { return mSplineData; };
	virtual TArray<FSplinePointData>* GetMutableSplinePointData() override { return &mSplineData; }
	virtual float GetMeshLength() const override { return mMeshLength; }
	virtual UStaticMesh* GetSplineMesh() const override { return mMesh; }
	virtual USplineComponent* GetSplineComponent() const override { return mSplineComponent; }

	// End IFGSplineBuildableInterface

	// Temp function will be removed.
	void DestroyVisualItems();

	virtual void PostSerializedFromBlueprint( bool isBlueprintWorld = false ) override;
	void ClearLUT();
	

	
protected:
	// Begin AFGBuildableFactory interface
	virtual bool VerifyDefaults( FString& out_message ) override;
	// End AFGBuildableFactory interface

	// Begin AFGBuildableConveyorBase interface
	virtual void TickItemTransforms( float dt ) override;
	virtual void TickRadioactivity() override;
	virtual void Factory_UpdateRadioactivity( class AFGRadioactivitySubsystem* subsystem ) override;
	virtual void GenerateCachedClearanceData( TArray< FFGClearanceData >& out_clearanceData ) override;
	// End AFGBuildableConveyorBase interface

	void SetupConnections();
private:
	/**
	 * Updates the transform of a single item only.
	 * We need to do this separately as all items are not in the same items array.
	 */
	void TickSingleItemTransform( const FConveyorBeltItem& item, TMap< FName, int32 >& instanceCounts, class AFGRadioactivitySubsystem* radioactiveSubsystem );

	/** Populates spline component from spline points data on the buildable */
	void PopulateSplineComponentFromSplinePointsData();
protected:
	/** Mesh to use for his conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	class UStaticMesh* mMesh;

	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	class UStaticMesh* mCollisionProxyMesh;
	
	/** Length of the mesh to use for this conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	float mMeshLength;

private:
	friend class AFGConveyorBeltHologram;
	friend class AFGBlueprintHologram;
	
	/** Meshes for items. */
	UPROPERTY( Meta = ( NoAutoJson ) )
	TMap< FName, class UInstancedStaticMeshComponent* > mItemMeshMap;

	/** Compact representation of mSplineComponent, used for replication and save game */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson ) )
	TArray< FSplinePointData > mSplineData;

	/** The spline component for this conveyor. Note that this is only the spline. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;

	/** Wwise multiple position playback for the conveyor spline. */
	UPROPERTY( VisibleDefaultsOnly, Category = "Audio" )
	class UFGSoundSplineComponent* mSoundSplineComponent;

	/** The ak event to post for the sound spline */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mSplineAudioEvent;

	/* Mesh used to determine visibility of the belt, since we moved to HISM's we have no clue if they are visible or not without this.*/
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> mVisibilityMeshComponent;

	/* Material assigned to the collision box proxies. */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicalMaterial* PhysicalMaterial;
	
	// Collision Constants. These used to be magic numbers in the .cpp but were moved here so they could be accessed via the SplineBuildableInterface
	static inline const FVector COLLISION_EXTENT = FVector( 80.f, 80.f, 15.f );
	static inline const float COLLISION_SPACING =  160.f;
	static inline const FVector COLLISION_OFFSET = FVector( 0.f, 0.f, 0.f );
};
