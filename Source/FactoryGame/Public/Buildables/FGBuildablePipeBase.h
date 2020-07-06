#pragma once
#include "FGInstancedSplineMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Components/SplineComponent.h"
#include "../FGSignificanceInterface.h"
#include "FGBuildablePipeBase.generated.h"


/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipeBase : public AFGBuildable, public IFGSignificanceInterface
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
	// End Buildable interface

	// Begin IFGSignificance Interface
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual	void SetupForSignificance() override;
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|PipeBase" )
	FORCEINLINE bool GetIsSignificant() { return mIsSignificant; }
	// End IFGSignificance Interface

	/** @return The connections, safe to assume its always valid. */
	FORCEINLINE UFGPipeConnectionComponentBase* GetConnection0() const { return mConnection0; }
	FORCEINLINE UFGPipeConnectionComponentBase* GetConnection1() const { return mConnection1; }

	/** Get the mesh used for this conveyor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|PipeBase" )
	FORCEINLINE UStaticMesh* GetSplineMesh() const { return mMesh; }

	/** Returns the spline component */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|PipeBase" )
	FORCEINLINE class USplineComponent* GetSplineComponent() { return mSplineComponent; }
	FORCEINLINE const class USplineComponent* GetSplineComponent() const { return mSplineComponent; }

	/* Get the length of the spline in world space */
	FORCEINLINE float GetLength() const { return mLength; }

	/* Helpers for finding locations on the pathing spline */
	virtual float FindOffsetClosestToLocation( const FVector& location ) const;
	virtual void GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const;

protected:
	/**
	 * @return The UClass for the connection type for this pipe. All pipe types should have their own function here, or their connection can snap to the wrong type of pipes.
	 * [DavalliusA:Tue/22-10-2019] this is med with a function, so we don't have to store a variable in all the instances of this class
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Pipes|PipeBase" )
	TSubclassOf< UFGPipeConnectionComponentBase > GetConnectionType();

public:
	/** Default height above ground level for pipes */
	static constexpr float DEFAULT_PIPE_HEIGHT = 175.f;

	const static float PIPE_COST_LENGTH_MULTIPLIER;
protected:
	/** Mesh to use for his conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipes" )
	class UStaticMesh* mMesh;

	/** Length of the mesh to use for this conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipes" )
	float mMeshLength;

	/** Length of the pipe in centimeters. */
	float mLength;

	/**
	 * First connection on the pipe (can be an input and an output, because, again, pipes)
	 * MUST BE SET FROM CONSTRUCTION SCRIPT OR IT WILL BE NULL!
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Pipes" )
	UFGPipeConnectionComponentBase* mConnection0;

	/**
	 * Second connection on the pipe (can be an input and an output, because, again, pipes)
	 * MUST BE SET FROM CONSTRUCTION SCRIPT OR IT WILL BE NULL!
	 */
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = "Pipes" )
	UFGPipeConnectionComponentBase* mConnection1;

	/** Compact representation of mSplineComponent, used for replication and save game */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson ) )
	TArray< FSplinePointData > mSplineData;

	/** The spline component for this splined factory. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;

	/** The spline meshes for this train track. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class UFGInstancedSplineMeshComponent* mInstancedSplineComponent;

private:
	friend class AFGPipelineHologram;

	/** Is this buildable significant, i.e. is within significance range */
	bool mIsSignificant;

public:
	FORCEINLINE ~AFGBuildablePipeBase() = default;
};


