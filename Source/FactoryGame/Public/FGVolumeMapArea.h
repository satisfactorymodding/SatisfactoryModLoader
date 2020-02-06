// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "FGVolumeMapArea.generated.h"



/**
 * This is a volume that will define the physical location of a map area.
 */
UCLASS()
class FACTORYGAME_API AFGVolumeMapArea : public AVolume
{
	GENERATED_BODY()
	
public:

	AFGVolumeMapArea();

#if WITH_EDITOR
	virtual void CheckForErrors() override;
#endif

protected:

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AACtor interface

	/** Called whenever a primitive component enters this volume */
	UFUNCTION()
	virtual void OnPrimitiveComponentEntered( UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult );

	UFUNCTION( BlueprintCallable, Category = "Map Area" )
	FORCEINLINE TSubclassOf< class UFGMapArea > GetMapArea() const { return mMapArea; }

	/** Called when a pawn enters the volume*/
	void OnPawnEntered( APawn* pawn, const FHitResult& enterInfo );
		
private:
	/** This is the area this map defines. */
	UPROPERTY( EditInstanceOnly, Category = "Map Area" )
	TSubclassOf< UFGMapArea > mMapArea;

	/** A cached game state */
	class AFGGameState* mCachedGameState;
	
};
