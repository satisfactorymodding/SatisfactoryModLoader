// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSignificanceInterface.h"
#include "WheeledVehicles/FGVehiclePathNode.h"
#include "FGStandaloneVehiclePathNode.generated.h"

/** Standalone vehicle path nodes are not automatically cleaned up when they have no connections and have visual representation in the world */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGStandaloneVehiclePathNode : public AFGVehiclePathNode, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGStandaloneVehiclePathNode();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin IFGSignificanceInterface
	virtual float GetSignificanceRange_Implementation() const override;
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	// End IFGSignificanceInterface

	/** Returns true if the node is significant to the local player */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	FORCEINLINE bool GetIsSignificantToLocalPlayer() const { return mIsSignificantForLocalPlayer; }

	FORCEINLINE UStaticMeshComponent* GetVisualizationMeshComponent() const { return mVisualizationMeshComponent; }

	void SetVisualizationEnabled( bool newVisualizationEnabled );
	FORCEINLINE bool IsVisualizationEnabled() const { return mIsVisualizationEnabled; }
protected:
	// Begin AFGVehiclePathNode interface
	virtual bool IsPersistentNode() const override { return true; }
	virtual void OnNodeConnectionsChanged() override;
	// End AFGVehiclePathNode interface

	void UpdateVisualizationOrientation() const;
	void UpdateCollisionResponse() const;
	
	UPROPERTY( EditAnywhere, Category = "Vehicle Path Node" )
	TObjectPtr<USphereComponent> mCollisionComponent;

	UPROPERTY( EditAnywhere, Category = "Vehicle Path Node" )
	TObjectPtr<UStaticMeshComponent> mVisualizationMeshComponent;

	/** The range in which path segments are considered significant to the player */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mSignificanceRange{15000.0f};

	/** True if this object is currently significant to the local player */
	bool mIsSignificantForLocalPlayer{false};

	bool mIsVisualizationEnabled{false};
};
