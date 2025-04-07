// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGBuildableWallPassthrough.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableWallPassthrough : public AFGBuildable
{
	GENERATED_BODY()

	friend class AFGWallPassthroughHologram;
public:
	AFGBuildableWallPassthrough();

	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin IAbstractInstanceInterface
	virtual bool DoesContainLightweightInstances_Native() const override;
	virtual TArray<FInstanceData> GetActorLightweightInstanceData_Implementation() const override;
	// End IAbstractInstanceInterface

	virtual void GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const override;

	void InitializeConnectionMeshClearanceData( FFGClearanceData& data ) const;

	void SetConnection( int32 connectionIndex, class UFGConnectionComponent* connection );
	
	class UFGConnectionComponent* GetConnection( int32 index ) const;

	FORCEINLINE TSubclassOf< UFGConnectionComponent > GetConnectionClass() const { return mConnectionClass; }
	
	FORCEINLINE float GetPassthroughDepth() const { return mPassthroughDepth; }
	FORCEINLINE float GetConnectionDepthOffset() const { return mConnectionDepthOffset; }

	/** Attempts to snap to the passthrough. Will return what connection index to snap to. 0 being front connection, and 1 being back connection. */
	bool TrySnap( const FHitResult& hitResult, int32& out_SnapIndex );

protected:
	/** Disconnects the connections from eachother. Function is called from EndPlay. */
	void DisconnectConnections();

private:
	/** The connection class of this passthrough. */
	UPROPERTY( EditDefaultsOnly, Category = "WallPassthrough" )
	TSubclassOf< UFGConnectionComponent > mConnectionClass;

	/** The mesh that will be used for the connections of the passthrough. */
	UPROPERTY( EditDefaultsOnly, Category = "WallPassthrough" )
	class UStaticMesh* mPassthroughConnectionMesh;

	/** How much to offset the connection locations, positive value will move the connections further out. */
	UPROPERTY( EditDefaultsOnly, Category = "WallPassthrough" )
	float mConnectionDepthOffset;
	
	UPROPERTY( Replicated )
	UFGConnectionComponent* mConnections[2];

	FFGClearanceData mConnectionMeshClearanceData[ 2 ];

	/** The depth of this passthrough, depends on whatever it was snapped to. */
	UPROPERTY( SaveGame, Replicated )
	float mPassthroughDepth;
};
