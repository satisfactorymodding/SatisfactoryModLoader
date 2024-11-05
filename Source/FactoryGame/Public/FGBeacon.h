// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGActorRepresentationInterface.h"
#include "FGBeacon.generated.h"

// Deprecated class. We only keep it to migrate beacons to map markers
UCLASS()
class FACTORYGAME_API AFGBeacon : public AFGStaticReplicatedActor
{
	GENERATED_BODY()
public:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface
	
	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetRepresentationColor();
	
	/** Fetches the text to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FText GetRepresentationText();
	
	/** Fetches the compass view distance to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	ECompassViewDistance GetCompassViewDistance();

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;
	
};
