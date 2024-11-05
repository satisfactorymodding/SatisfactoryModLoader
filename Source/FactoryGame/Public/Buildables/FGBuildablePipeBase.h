// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/SplineComponent.h"
#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "FGSignificanceInterface.h"
#include "FGSplineBuildableInterface.h"
#include "Templates/SubclassOf.h"
#include "FGBuildablePipeBase.generated.h"

class UFGPipeConnectionComponentBase;
/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipeBase : public AFGBuildable, public IFGSignificanceInterface, public IFGSplineBuildableInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePipeBase();

	// Begin Actor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End Actor Interface 

	// Begin Buildable interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	virtual bool ShouldBeConsideredForBase_Implementation() override;
	virtual void GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const override;
	virtual bool ShouldBlockGuidelinePathForHologram( const class AFGHologram* hologram ) const override;
	// End Buildable interface

	// Begin IFGDismantleInterface
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	virtual void Dismantle_Implementation() override;
	// End IFGDismantleInterface

	// Begin abstract instance interface.
	virtual TArray<FInstanceData> GetActorLightweightInstanceData_Implementation() override;
	virtual bool DoesContainLightweightInstances_Native() const override { return true; }
	// End
	
	// Begin IFGSignificance Interface
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;				// TODO deprecate
	virtual void LostSignificance_Native() override;				// TODO deprecate				
	virtual	void SetupForSignificance() override;					// TODO deprecate		

	virtual float GetSignificanceRange() override;

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|PipeBase" )
	FORCEINLINE bool GetIsSignificant() { return mIsSignificant; }
	// End IFGSignificance Interface

	/** @return The connections, safe to assume its always valid. */
	FORCEINLINE UFGPipeConnectionComponentBase* GetConnection0() const { return mConnection0; }
	FORCEINLINE UFGPipeConnectionComponentBase* GetConnection1() const { return mConnection1; }

	/* Get the length of the spline in world space */
	FORCEINLINE float GetLength() const { return mLength; }

	/* Helpers for finding locations on the pathing spline */
	virtual float FindOffsetClosestToLocation( const FVector& location ) const;
	virtual void GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const;

	// Begin IFGSplineBuildableInterface
	virtual UFGConnectionComponent* GetSplineConnection0() const override;
	virtual UFGConnectionComponent* GetSplineConnection1() const override;
	virtual const TArray< FSplinePointData >& GetSplinePointData() const override { return mSplineData; };
	virtual TArray<FSplinePointData>* GetMutableSplinePointData() override { return &mSplineData; }
	virtual float GetMeshLength() const override { return mMeshLength; }
	virtual UStaticMesh* GetSplineMesh() const override { return mMesh; }
	virtual USplineComponent* GetSplineComponent() const override { return mSplineComponent; }
	// End IFGSplineBuildableInterface
	
	FORCEINLINE TArray< class AFGBuildablePassthrough* > GetSnappedPassthroughs() { return mSnappedPassthroughs; }

	static void CreateClearanceData( class USplineComponent* splineComponent, const TArray< FSplinePointData >& splineData, const FTransform& pipeTransform, TArray< FFGClearanceData >& out_clearanceData, float maxDistance = -1.0f );

	UPROPERTY(EditDefaultsOnly,Category="Visuals")
	UMaterialInterface* mSplineMeshMaterial = nullptr;
	/**
	 * Splices the provided pipeline into two pieces.
	 * Unlike splitting, splicing does decrease the size of the pipeline and leads an empty area in the middle,
	 * suitable for an insertion of the new piece in that area.
	 * That means it will void the resources, unless you manually account for that before the splice.
	 *
	 * The resulting splices will be of length [0, offset - splice_length / 2], [offset + splice_length / 2, length]
	 * And will be automatically reconnected with the original connections of the previous pipelineon the ends
	 * On success, the original pipeline will be dismantled
	 * The returned pieces will always come in the order specified above, so you can make a safe assumption
	 * on the fact that Connection1 of the first piece will be spliced, and Connection0 of the second one as well.
	 */
	static TArray<AFGBuildablePipeBase*> Splice(AFGBuildablePipeBase* Pipe, float SpliceOffset, float SpliceLength, AActor* BuildEffectInstigator = nullptr);

	virtual void PostSerializedFromBlueprint(bool isBlueprintWorld) override;
	
protected:
	/**
	 * @return The UClass for the connection type for this pipe. All pipe types should have their own function here, or their connection can snap to the wrong type of pipes.
	 * [DavalliusA:Tue/22-10-2019] this is med with a function, so we don't have to store a variable in all the instances of this class
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Pipes|PipeBase" )
	TSubclassOf< class UFGPipeConnectionComponentBase > GetConnectionType();

	void UnrotateForBlueprintPlaced();
	void SetupConnections();

	/** Function used to generate cached clearance data for this pipe. */
	virtual void GenerateCachedClearanceData( TArray< FFGClearanceData >& out_clearanceData );

	/** Populates spline component from spline points data on the buildable */
	void PopulateSplineComponentFromSplinePointsData();
public:
	/** Default height above ground level for pipes */
	static constexpr float DEFAULT_PIPE_HEIGHT = 175.f;

	const static float PIPE_COST_LENGTH_MULTIPLIER;
protected:
	/** Mesh to use for his pipe. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipes" )
	class UStaticMesh* mMesh;

	/** Length of the mesh to use for this pipe. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipes" )
	float mMeshLength;

	/** Length of the pipe in centimeters. */
	float mLength;

	/** Should we use per segment or should we try to scale the mesh to fit. **/
	bool mUsePerSegmentSplining;

	/**
	 * First connection on the pipe (can be an input and an output, because, again, pipes)
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Pipes" )
	UFGPipeConnectionComponentBase* mConnection0;

	/**
	 * Second connection on the pipe (can be an input and an output, because, again, pipes)
	 */
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Pipes" )
	UFGPipeConnectionComponentBase* mConnection1;

	/** Compact representation of mSplineComponent, used for replication and save game */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson ) )
	TArray< FSplinePointData > mSplineData;

	/** The spline component for this splined factory. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;
	
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class UInstancedSplineMeshComponent* mInstancedSplineMeshComponent;
	
	/** Saved passthroughs this pipeline is connected to. Used to notify passthrough when dismantled. */
	UPROPERTY( SaveGame, Replicated )
	TArray< class AFGBuildablePassthrough* > mSnappedPassthroughs;

	/* Material assigned to the collision box proxies. */
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	UPhysicalMaterial* PhysicalMaterial;

private:
	friend class AFGPipelineHologram;
	
	/** Clearance data generated upon request for this conveyor. */
	TArray< FFGClearanceData > mCachedClearanceData;

	/** Is this buildable significant, i.e. is within significance range */
	bool mIsSignificant;

	// Collision Constants. These used to be magic numbers in the .cpp but were moved here so they could be accessed via the SplineBuildableInterface
	static inline const FVector COLLISION_EXTENT = FVector( 40.0f, 80.f , 80.f );
	static inline const float COLLISION_SPACING =  80.f;
	static inline const FVector COLLISION_OFFSET = FVector( 0.f, 0.f, 0.f );
};


