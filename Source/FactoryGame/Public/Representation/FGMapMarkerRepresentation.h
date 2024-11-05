// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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

	// Begin UFGActorRepresentation interface
	virtual FVector GetActorLocation() const override;
	virtual bool GetShouldShowInCompass() const override;
	virtual ECompassViewDistance GetCompassViewDistance() const override;
	// End UFGActorRepresentation interface

	virtual float GetScaleOnMap() const override;
	virtual bool CanBeHighlighted() const override;
	virtual UFGHighlightedMarker* CreateHighlightedMarker( UObject* owner ) override;

	void Init( const FMapMarker& mapMarker );
	
	FMapMarker mMapMarker;
};
