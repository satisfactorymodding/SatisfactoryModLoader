// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGPipelineIndicatorData.h"
#include "Components/ActorComponent.h"
#include "FGPlayerPipelineDataReplicationComponent.generated.h"

class AFGCharacterPlayer;
class AFGBuildablePipeline;

USTRUCT(Atomic)
struct FACTORYGAME_API FFGPipelinePlayerReplicationData
{
	GENERATED_BODY()

	UPROPERTY()
	AFGBuildablePipeline* OwningPipeline{};

	UPROPERTY()
	FPipelineIndicatorData ReplicationData;
};

/**
 * Component that handles the replication of the pipeline data for the Pipe UI
 */
UCLASS(NotBlueprintable, Within = Pawn)
class FACTORYGAME_API UFGPlayerPipelineDataReplicationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGPlayerPipelineDataReplicationComponent();

	// Begin UActorComponent interface
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// End UActorComponent interface

	/** Retrieves the component instance for the player character */
	static UFGPlayerPipelineDataReplicationComponent* Get( const AFGCharacterPlayer* PlayerCharacter);

	void RegisterInteractedPipeline(AFGBuildablePipeline* Pipeline);
	void UnregisterInteractedPipeline( const AFGBuildablePipeline* Pipeline);
protected:
	/** Called to flush the replication data into the pipeline buildables */
	UFUNCTION()
	void OnRep_ReplicationData(const TArray<FFGPipelinePlayerReplicationData>& OldReplicationData);
	
	/** Currently replicated pipeline data */
	UPROPERTY(ReplicatedUsing = OnRep_ReplicationData)
	TArray<FFGPipelinePlayerReplicationData> mReplicationData;
};
