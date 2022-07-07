// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGActorRepresentation.h"
#include "FGMapMarker.h"
#include "FGMapMarkerRepresentation.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGMapMarkerRepresentation : public UFGActorRepresentation
{
	GENERATED_BODY()
public:
	UFGMapMarkerRepresentation();

	UFUNCTION( BlueprintPure, Category=Map )
	FMapMarker GetMapMarker() const {return mMapMarker;}

	/* We don't want to replicate this. The information is replicated somewhere else and then the representation is added locally */
	virtual bool IsSupportedForNetworking() const override { return false; }
	
	// Begin UFGActorRepresentation interface
	virtual FVector GetActorLocation() const override;
	bool GetShouldShowInCompass() const override;
	ECompassViewDistance GetCompassViewDistance() const override;
	// End UFGActorRepresentation interface

	virtual float GetScaleOnMap() const override;
	virtual bool CanBeHighlighted() const override;
	virtual UFGHighlightedMarker* CreateHighlightedMarker( UObject* owner ) override;

	void Init( const FMapMarker& mapMarker );
	
	FMapMarker mMapMarker;
};
